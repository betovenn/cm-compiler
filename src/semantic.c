#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semantic.h"

typedef struct ParamSymbol {
    char *name;
    char *type;
    struct ParamSymbol *next;
} ParamSymbol;

typedef struct Symbol {
    char *name;
    char *type;
    int isFunction;
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

static void semanticError(TreeNode *node, const char *message) {
    int line = node != NULL ? node->lineno : 0;

    if (line > 0) {
        fprintf(semanticOut, "[Linea %-4d] %s\n", line, message);
    } else {
        fprintf(semanticOut, "[Linea ?   ] %s\n", message);
    }

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

static Symbol *insertSymbol(TreeNode *node, const char *name, const char *type, int isFunction) {
    Scope *scope = scopeStack;
    Symbol *symbol;

    if (scope == NULL) {
        scope = enterScope();
    }

    if (findInScope(scope, name) != NULL) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "identificador '%s' ya declarado en este alcance", name);
        semanticError(node, buffer);
        return NULL;
    }

    symbol = (Symbol *)calloc(1, sizeof(Symbol));
    symbol->name = (char *)name;
    symbol->type = (char *)type;
    symbol->isFunction = isFunction;
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

static const char *analyzeExpression(TreeNode *node);
static void analyzeStatement(TreeNode *node);

static void addLocalDeclarations(TreeNode *node) {
    while (node != NULL) {
        if (node->nodekind == DeclK && node->kind.decl == VarDeclK) {
            if (sameType(node->type, "void")) {
                semanticError(node, "una variable no puede declararse con tipo void");
            }
            insertSymbol(node, node->attr, node->type, 0);
        }
        node = node->sibling;
    }
}

static void analyzeCompound(TreeNode *node) {
    enterScope();
    addLocalDeclarations(node->child[0]);
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
        snprintf(buffer, sizeof(buffer), "llamada a funcion '%s' no declarada", node->attr);
        semanticError(node, buffer);
        return NULL;
    }

    if (!symbol->isFunction) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "'%s' no es una funcion", node->attr);
        semanticError(node, buffer);
        return NULL;
    }

    if (countParams(symbol->params) != countArgs(node->child[0])) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "numero incorrecto de argumentos en llamada a '%s'", node->attr);
        semanticError(node, buffer);
    }

    param = symbol->params;
    arg = node->child[0];
    while (param != NULL && arg != NULL) {
        const char *argType = analyzeExpression(arg);
        if (argType != NULL && !sameType(param->type, argType)) {
            char buffer[256];
            snprintf(
                buffer,
                sizeof(buffer),
                "el argumento %d de '%s' debe ser %s y se recibio %s",
                position,
                node->attr,
                param->type,
                argType
            );
            semanticError(arg, buffer);
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
            semanticError(node, "la asignacion usa tipos incompatibles");
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
                snprintf(buffer, sizeof(buffer), "identificador '%s' no declarado", node->attr);
                semanticError(node, buffer);
                return NULL;
            }
            if (symbol->isFunction) {
                char buffer[256];
                snprintf(buffer, sizeof(buffer), "la funcion '%s' debe llamarse con parentesis", node->attr);
                semanticError(node, buffer);
                return NULL;
            }
            return symbol->type;
        }

        case CallK:
            return analyzeCall(node);

        case OpK: {
            const char *leftType = analyzeExpression(node->child[0]);
            const char *rightType = analyzeExpression(node->child[1]);

            if (leftType != NULL && !sameType(leftType, "int")) {
                semanticError(node->child[0], "el operando izquierdo debe ser int");
            }
            if (rightType != NULL && !sameType(rightType, "int")) {
                semanticError(node->child[1], "el operando derecho debe ser int");
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

                case ReturnK: {
                    const char *returnType = analyzeExpression(node->child[0]);
                    if (sameType(currentFunctionType, "void") && node->child[0] != NULL) {
                        semanticError(node, "una funcion void no debe regresar una expresion");
                    } else if (sameType(currentFunctionType, "int") && node->child[0] == NULL) {
                        semanticError(node, "una funcion int debe regresar una expresion");
                    } else if (node->child[0] != NULL && returnType != NULL && !sameType(currentFunctionType, returnType)) {
                        semanticError(node, "el tipo de retorno no coincide con la funcion");
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
        } else if (node->nodekind == ExpK) {
            analyzeExpression(node);
        }

        node = node->sibling;
    }
}

static void collectGlobalDeclarations(TreeNode *node) {
    while (node != NULL) {
        if (node->nodekind == DeclK) {
            if (node->kind.decl == VarDeclK) {
                if (sameType(node->type, "void")) {
                    semanticError(node, "una variable global no puede declararse con tipo void");
                }
                insertSymbol(node, node->attr, node->type, 0);
            } else if (node->kind.decl == FunDeclK) {
                Symbol *symbol = insertSymbol(node, node->attr, node->type, 1);
                if (symbol != NULL) {
                    symbol->params = buildParamList(node->child[0]);
                }
            }
        }
        node = node->sibling;
    }
}

static void analyzeFunctions(TreeNode *node) {
    while (node != NULL) {
        if (node->nodekind == DeclK && node->kind.decl == FunDeclK) {
            TreeNode *param = node->child[0];
            currentFunctionType = node->type;

            enterScope();
            while (param != NULL) {
                insertSymbol(param, param->attr, param->type, 0);
                param = param->sibling;
            }
            analyzeStatement(node->child[1]);
            leaveScope();

            currentFunctionType = NULL;
        }
        node = node->sibling;
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
        strncat(buffer, " ", bufferSize - strlen(buffer) - 1);
        strncat(buffer, param->name, bufferSize - strlen(buffer) - 1);
        first = 0;
        param = param->next;
    }
}

static void printSymbolTable(void) {
    Symbol *symbol = allSymbols;

    fprintf(semanticOut, "\nTabla de simbolos:\n");
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
            symbol->type,
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
    collectGlobalDeclarations(tree);
    analyzeFunctions(tree);
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
