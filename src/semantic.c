#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semantic.h"

typedef struct ParamSymbol {
    char *name;
    char *type;
    int isArray;
    struct ParamSymbol *next;
} ParamSymbol;

typedef struct Symbol {
    char *name;
    char *type;
    int isFunction;
    int isArray;
    int scopeLevel;
    ParamSymbol *params;
    struct Symbol *next;
    struct Symbol *allNext;
} Symbol;

typedef struct Scope {
    int level;
    Symbol *symbols;
    struct Scope *next;
} Scope;

static Scope *scopeStack = NULL;
static Symbol *allSymbols = NULL;
static Symbol *allSymbolsTail = NULL;
static int semanticErrors = 0;
static FILE *semanticOut = NULL;
static char *currentFunctionType = NULL;

static void semanticError(TreeNode *node, const char *message, const char *suggestion) {
    int line = node != NULL ? node->lineno : 0;

    if (line > 0) {
        fprintf(semanticOut, "[Semantico][Linea %-4d] %s\n", line, message);
    } else {
        fprintf(semanticOut, "[Semantico][Linea ?   ] %s\n", message);
    }
    if (node != NULL && node->attr != NULL && strlen(node->attr) > 0) {
        fprintf(semanticOut, "Cerca de: '%s'\n", node->attr);
    }
    if (suggestion != NULL && strlen(suggestion) > 0) {
        fprintf(semanticOut, "Sugerencia: %s\n", suggestion);
    }
    fprintf(semanticOut, "\n");

    semanticErrors++;
}

static Scope *enterScope(void) {
    Scope *scope = (Scope *)calloc(1, sizeof(Scope));
    scope->level = scopeStack == NULL ? 0 : scopeStack->level + 1;
    scope->next = scopeStack;
    scopeStack = scope;

    return scope;
}

static void leaveScope(void) {
    if (scopeStack != NULL) {
        scopeStack = scopeStack->next;
    }
}

static Symbol *findInScope(Scope *scope, const char *name) {
    Symbol *symbol = scope != NULL ? scope->symbols : NULL;

    while (symbol != NULL) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }

    return NULL;
}

static Symbol *lookup(const char *name) {
    Scope *scope = scopeStack;

    while (scope != NULL) {
        Symbol *symbol = findInScope(scope, name);
        if (symbol != NULL) {
            return symbol;
        }
        scope = scope->next;
    }

    return NULL;
}

static Symbol *insertSymbol(TreeNode *node, const char *name, const char *type, int isFunction, int isArray) {
    Scope *scope = scopeStack;
    Symbol *symbol;

    if (scope == NULL) {
        scope = enterScope();
    }

    if (findInScope(scope, name) != NULL) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "El identificador '%s' ya fue declarado en este alcance.", name);
        semanticError(node, buffer, "Use otro nombre o elimine la declaracion duplicada.");
        return NULL;
    }

    symbol = (Symbol *)calloc(1, sizeof(Symbol));
    symbol->name = (char *)name;
    symbol->type = (char *)type;
    symbol->isFunction = isFunction;
    symbol->isArray = isArray;
    symbol->scopeLevel = scope->level;
    symbol->next = scope->symbols;
    scope->symbols = symbol;

    if (allSymbols == NULL) {
        allSymbols = symbol;
        allSymbolsTail = symbol;
    } else {
        allSymbolsTail->allNext = symbol;
        allSymbolsTail = symbol;
    }

    return symbol;
}

static ParamSymbol *buildParamList(TreeNode *paramNode) {
    ParamSymbol *head = NULL;
    ParamSymbol *tail = NULL;

    while (paramNode != NULL) {
        ParamSymbol *param = (ParamSymbol *)calloc(1, sizeof(ParamSymbol));
        param->name = paramNode->attr;
        param->type = paramNode->type != NULL ? paramNode->type : "int";
        param->isArray = paramNode->isArray;

        if (head == NULL) {
            head = param;
        } else {
            tail->next = param;
        }
        tail = param;

        paramNode = paramNode->sibling;
    }

    return head;
}

static int countParams(ParamSymbol *param) {
    int count = 0;

    while (param != NULL) {
        count++;
        param = param->next;
    }

    return count;
}

static int countArgs(TreeNode *arg) {
    int count = 0;

    while (arg != NULL) {
        count++;
        arg = arg->sibling;
    }

    return count;
}

static int sameType(const char *left, const char *right) {
    return left != NULL && right != NULL && strcmp(left, right) == 0;
}

static const char *symbolTypeName(Symbol *symbol) {
    if (symbol != NULL && symbol->isArray) {
        return "int[]";
    }

    return symbol != NULL ? symbol->type : NULL;
}

static void installPredefinedFunctions(void) {
    Symbol *inputSymbol;
    Symbol *outputSymbol;
    ParamSymbol *outputParam;

    inputSymbol = insertSymbol(NULL, "input", "int", 1, 0);

    outputSymbol = insertSymbol(NULL, "output", "void", 1, 0);
    if (outputSymbol != NULL) {
        outputParam = (ParamSymbol *)calloc(1, sizeof(ParamSymbol));
        outputParam->name = "x";
        outputParam->type = "int";
        outputParam->isArray = 0;
        outputSymbol->params = outputParam;
    }

    (void)inputSymbol;
}

static const char *analyzeExpression(TreeNode *node);
static void analyzeStatement(TreeNode *node);

static void analyzeLocalDeclaration(TreeNode *node) {
    const char *initType;

    if (node == NULL || node->nodekind != DeclK || node->kind.decl != VarDeclK) {
        return;
    }

    if (sameType(node->type, "void")) {
        semanticError(node,
                      "Una variable local no puede declararse con tipo void.",
                      "Declare la variable como int o conviertala en una funcion void si no devuelve valor.");
    }

    insertSymbol(node, node->attr, node->type, 0, node->isArray);

    if (node->child[0] != NULL) {
        initType = analyzeExpression(node->child[0]);
        if (initType != NULL && !sameType(node->type, initType)) {
            semanticError(node,
                          "La inicializacion usa tipos incompatibles.",
                          "El tipo de la variable debe coincidir con la expresion inicial.");
        }
    }
}

static void addLocalDeclarations(TreeNode *node) {
    while (node != NULL) {
        if (node->nodekind == DeclK && node->kind.decl == VarDeclK) {
            if (sameType(node->type, "void")) {
                semanticError(node,
                              "Una variable local no puede declararse con tipo void.",
                              "Declare la variable como int o conviertala en una funcion void si no devuelve valor.");
            }
            insertSymbol(node, node->attr, node->type, 0, node->isArray);
        }
        node = node->sibling;
    }
}

static void analyzeCompound(TreeNode *node) {
    enterScope();
    analyzeStatement(node->child[1]);
    leaveScope();
}

static const char *analyzeCall(TreeNode *node) {
    Symbol *symbol = lookup(node->attr);
    ParamSymbol *param;
    TreeNode *arg;
    int position = 1;

    if (symbol == NULL) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "Funcion '%s' llamada antes de declararse.", node->attr);
        semanticError(node, buffer, "Declare la funcion antes de la llamada. C- no tiene prototipos.");
        return NULL;
    }

    if (!symbol->isFunction) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "'%s' no es una funcion.", node->attr);
        semanticError(node, buffer, "Use el identificador sin parentesis si es una variable, o declare una funcion con ese nombre.");
        return NULL;
    }

    if (countParams(symbol->params) != countArgs(node->child[0])) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "Numero incorrecto de argumentos en llamada a '%s'.", node->attr);
        semanticError(node, buffer, "Ajuste la llamada para que coincida con la cantidad de parametros declarados.");
    }

    param = symbol->params;
    arg = node->child[0];
    while (param != NULL && arg != NULL) {
        const char *argType = analyzeExpression(arg);

        if (param->isArray) {
            if (arg->nodekind != ExpK || arg->kind.exp != IdK || arg->isArray || !sameType(argType, "int[]")) {
                char buffer[256];
                snprintf(buffer, sizeof(buffer), "El argumento %d de '%s' debe ser un arreglo int.", position, node->attr);
                semanticError(arg, buffer, "Pase el nombre del arreglo sin indice, por ejemplo datos.");
            }
        } else if (argType != NULL && !sameType(param->type, argType)) {
            char buffer[256];
            snprintf(
                buffer,
                sizeof(buffer),
                "El argumento %d de '%s' debe ser %s y se recibio %s.",
                position,
                node->attr,
                param->type,
                argType
            );
            semanticError(arg, buffer, "Revise el tipo del argumento o la declaracion de la funcion.");
        }
        param = param->next;
        arg = arg->sibling;
        position++;
    }

    while (arg != NULL) {
        analyzeExpression(arg);
        arg = arg->sibling;
    }

    return symbol->type;
}

static const char *analyzeExpression(TreeNode *node) {
    if (node == NULL) {
        return NULL;
    }

    if (node->nodekind == StmtK && node->kind.stmt == AssignK) {
        const char *leftType = analyzeExpression(node->child[0]);
        const char *rightType = analyzeExpression(node->child[1]);

        if (leftType != NULL && rightType != NULL && !sameType(leftType, rightType)) {
            semanticError(node,
                          "La asignacion usa tipos incompatibles.",
                          "El tipo del lado izquierdo debe coincidir con el valor asignado.");
        }

        return leftType;
    }

    if (node->nodekind != ExpK) {
        analyzeStatement(node);
        return NULL;
    }

    switch (node->kind.exp) {
        case ConstK:
            return "int";

        case IdK: {
            Symbol *symbol = lookup(node->attr);
            if (symbol == NULL) {
                char buffer[256];
                snprintf(buffer, sizeof(buffer), "Variable '%s' usada antes de declararse.", node->attr);
                semanticError(node, buffer, "Declare la variable antes de usarla en este alcance.");
                return NULL;
            }
            if (symbol->isFunction) {
                char buffer[256];
                snprintf(buffer, sizeof(buffer), "La funcion '%s' debe llamarse con parentesis.", node->attr);
                semanticError(node, buffer, "Use una llamada como f(...) o asigne el resultado de esa llamada.");
                return NULL;
            }

            if (node->isArray) {
                const char *indexType = analyzeExpression(node->child[0]);

                if (!symbol->isArray) {
                    char buffer[256];
                    snprintf(buffer, sizeof(buffer), "'%s' no es un arreglo.", node->attr);
                    semanticError(node, buffer, "Quite el indice o declare el identificador como arreglo.");
                    return NULL;
                }
                if (indexType != NULL && !sameType(indexType, "int")) {
                    semanticError(node->child[0],
                                  "El indice del arreglo debe ser int.",
                                  "Use una expresion entera dentro de los corchetes.");
                }

                return symbol->type;
            }

            return symbolTypeName(symbol);
        }

        case CallK:
            return analyzeCall(node);

        case OpK: {
            const char *leftType = analyzeExpression(node->child[0]);
            const char *rightType = analyzeExpression(node->child[1]);

            if (leftType != NULL && !sameType(leftType, "int")) {
                semanticError(node->child[0],
                              "El operando izquierdo debe ser int.",
                              "Las operaciones aritmeticas y relacionales de C- solo operan con enteros.");
            }
            if (rightType != NULL && !sameType(rightType, "int")) {
                semanticError(node->child[1],
                              "El operando derecho debe ser int.",
                              "Las operaciones aritmeticas y relacionales de C- solo operan con enteros.");
            }
            return "int";
        }
    }

    return NULL;
}

static void analyzeStatement(TreeNode *node) {
    while (node != NULL) {
        if (node->nodekind == StmtK) {
            switch (node->kind.stmt) {
                case IfK:
                case WhileK:
                    analyzeExpression(node->child[0]);
                    analyzeStatement(node->child[1]);
                    analyzeStatement(node->child[2]);
                    break;

                case ForK:
                    enterScope();
                    if (node->child[0] != NULL && node->child[0]->nodekind == DeclK) {
                        analyzeLocalDeclaration(node->child[0]);
                    } else {
                        analyzeExpression(node->child[0]);
                    }
                    analyzeExpression(node->child[1]);
                    analyzeExpression(node->child[2]);
                    analyzeStatement(node->child[3]);
                    leaveScope();
                    break;

                case ReturnK: {
                    const char *returnType = analyzeExpression(node->child[0]);
                    if (sameType(currentFunctionType, "void") && node->child[0] != NULL) {
                        semanticError(node,
                                      "Una funcion void no debe regresar una expresion.",
                                      "Use 'return;' o cambie el tipo de retorno de la funcion.");
                    } else if (sameType(currentFunctionType, "int") && node->child[0] == NULL) {
                        semanticError(node,
                                      "Una funcion int debe regresar una expresion.",
                                      "Use 'return expresion;' con una expresion de tipo int.");
                    } else if (node->child[0] != NULL && returnType != NULL && !sameType(currentFunctionType, returnType)) {
                        semanticError(node,
                                      "El tipo de retorno no coincide con la funcion.",
                                      "Revise que la expresion retornada tenga el mismo tipo que la funcion.");
                    }
                    break;
                }

                case CompoundK:
                    analyzeCompound(node);
                    break;

                case AssignK:
                    analyzeExpression(node);
                    break;
            }
        } else if (node->nodekind == DeclK) {
            analyzeLocalDeclaration(node);
        } else if (node->nodekind == ExpK) {
            analyzeExpression(node);
        }

        node = node->sibling;
    }
}

static void validateParams(TreeNode *param) {
    while (param != NULL) {
        if (sameType(param->type, "void")) {
            semanticError(param,
                          "Un parametro no puede declararse con tipo void.",
                          "Use 'void' solo para indicar que la funcion no tiene parametros.");
        }
        param = param->sibling;
    }
}

static void analyzeFunction(TreeNode *node) {
    TreeNode *param = node->child[0];

    currentFunctionType = node->type;

    enterScope();
    while (param != NULL) {
        insertSymbol(param, param->attr, param->type, 0, param->isArray);
        param = param->sibling;
    }
    analyzeStatement(node->child[1]);
    leaveScope();

    currentFunctionType = NULL;
}

static void analyzeDeclarationsInOrder(TreeNode *node) {
    while (node != NULL) {
        if (node->nodekind == DeclK) {
            if (node->kind.decl == VarDeclK) {
                if (sameType(node->type, "void")) {
                    semanticError(node,
                                  "Una variable global no puede declararse con tipo void.",
                                  "Declare variables globales como int o arreglos int.");
                }
                insertSymbol(node, node->attr, node->type, 0, node->isArray);
            } else if (node->kind.decl == FunDeclK) {
                Symbol *symbol;

                validateParams(node->child[0]);
                symbol = insertSymbol(node, node->attr, node->type, 1, 0);
                if (symbol != NULL) {
                    symbol->params = buildParamList(node->child[0]);
                }
                analyzeFunction(node);
            }
        }
        node = node->sibling;
    }
}

static void checkMainDeclaration(TreeNode *tree) {
    TreeNode *last = tree;
    TreeNode *mainNode = NULL;
    TreeNode *node = tree;

    while (last != NULL && last->sibling != NULL) {
        last = last->sibling;
    }

    while (node != NULL) {
        if (node->nodekind == DeclK && node->kind.decl == FunDeclK &&
            node->attr != NULL && strcmp(node->attr, "main") == 0) {
            mainNode = node;
        }
        node = node->sibling;
    }

    if (mainNode == NULL) {
        semanticError(last,
                      "No se encontro la funcion obligatoria main.",
                      "Agregue int main() o void main(void) como ultima declaracion del programa.");
        return;
    }

    if ((!sameType(mainNode->type, "void") && !sameType(mainNode->type, "int")) || mainNode->child[0] != NULL) {
        semanticError(mainNode,
                      "La funcion main existe, pero su firma no es valida.",
                      "Declare main sin parametros como int main() o void main(void).");
    }

    if (last != mainNode) {
        semanticError(mainNode,
                      "La funcion main existe, pero no es la ultima declaracion.",
                      "Mueva main al final del archivo.");
    }
}

static void formatParams(ParamSymbol *param, char *buffer, size_t bufferSize) {
    int first = 1;

    buffer[0] = '\0';

    while (param != NULL) {
        if (!first) {
            strncat(buffer, ", ", bufferSize - strlen(buffer) - 1);
        }
        strncat(buffer, param->type, bufferSize - strlen(buffer) - 1);
        if (param->isArray) {
            strncat(buffer, "[]", bufferSize - strlen(buffer) - 1);
        }
        strncat(buffer, " ", bufferSize - strlen(buffer) - 1);
        strncat(buffer, param->name, bufferSize - strlen(buffer) - 1);
        first = 0;
        param = param->next;
    }
}

static void printSymbolTable(void) {
    Symbol *symbol = allSymbols;

    fprintf(semanticOut, "\nInformacion auxiliar: tabla de simbolos\n");
    fprintf(semanticOut, "+---------+----------+------+--------------------+------------------------------+\n");
    fprintf(semanticOut, "| Alcance | Clase    | Tipo | Nombre             | Parametros                   |\n");
    fprintf(semanticOut, "+---------+----------+------+--------------------+------------------------------+\n");

    while (symbol != NULL) {
        char params[256];
        formatParams(symbol->params, params, sizeof(params));

        fprintf(
            semanticOut,
            "| %-7d | %-8s | %-4s | %-18s | %-28s |\n",
            symbol->scopeLevel,
            symbol->isFunction ? "funcion" : "variable",
            symbol->isArray ? "int[]" : symbol->type,
            symbol->name,
            params
        );
        symbol = symbol->allNext;
    }

    fprintf(semanticOut, "+---------+----------+------+--------------------+------------------------------+\n");
}

int semanticAnalyze(TreeNode *tree, FILE *out) {
    semanticOut = out;
    semanticErrors = 0;
    scopeStack = NULL;
    allSymbols = NULL;
    allSymbolsTail = NULL;
    currentFunctionType = NULL;

    fprintf(semanticOut, "=== ANALISIS SEMANTICO ===\n\n");

    enterScope();
    installPredefinedFunctions();
    analyzeDeclarationsInOrder(tree);
    checkMainDeclaration(tree);
    printSymbolTable();

    if (semanticErrors == 0) {
        fprintf(semanticOut, "\nEstado: correcto\n");
        fprintf(semanticOut, "Errores semanticos: 0\n");
    } else {
        fprintf(semanticOut, "\nEstado: con errores\n");
        fprintf(semanticOut, "Errores semanticos: %d\n", semanticErrors);
    }

    return semanticErrors;
}
