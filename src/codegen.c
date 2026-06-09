#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen.h"

static FILE *codeOut = NULL;
static int tempCount = 0;
static int labelCount = 0;
static int instructionCount = 0;
static int functionCount = 0;

static char *copyString(const char *text) {
    size_t length;
    char *copy;

    if (text == NULL) {
        text = "";
    }

    length = strlen(text) + 1;
    copy = (char *)malloc(length);

    if (copy == NULL) {
        fprintf(stderr, "codegen: no se pudo reservar memoria\n");
        exit(1);
    }

    memcpy(copy, text, length);
    return copy;
}

static char *newName(const char *prefix, int number) {
    char buffer[32];

    snprintf(buffer, sizeof(buffer), "%s%d", prefix, number);
    return copyString(buffer);
}

static char *newTemp(void) {
    tempCount++;
    return newName("t", tempCount);
}

static char *newLabel(void) {
    labelCount++;
    return newName("L", labelCount);
}

static char *formatArrayAccess(const char *name, const char *index) {
    size_t length = strlen(name) + strlen(index) + 4;
    char *text = (char *)malloc(length);

    if (text == NULL) {
        fprintf(stderr, "codegen: no se pudo reservar memoria\n");
        exit(1);
    }

    snprintf(text, length, "%s[%s]", name, index);
    return text;
}

static void emit(const char *format, ...) {
    va_list args;

    va_start(args, format);
    vfprintf(codeOut, format, args);
    va_end(args);

    fprintf(codeOut, "\n");
    instructionCount++;
}

static void emitBlank(void) {
    fprintf(codeOut, "\n");
}

static void genNodeList(TreeNode *node);
static void genDecl(TreeNode *node);
static void genStmt(TreeNode *node);
static char *genExp(TreeNode *node);
static void genLocalDecl(TreeNode *node);

static void appendText(char **target, const char *text) {
    size_t oldLength = *target != NULL ? strlen(*target) : 0;
    size_t textLength = text != NULL ? strlen(text) : 0;
    char *next = (char *)realloc(*target, oldLength + textLength + 1);

    if (next == NULL) {
        fprintf(stderr, "codegen: no se pudo reservar memoria\n");
        exit(1);
    }

    memcpy(next + oldLength, text != NULL ? text : "", textLength + 1);
    *target = next;
}

static char *formatArguments(TreeNode *arg) {
    char *args = copyString("");
    int first = 1;

    while (arg != NULL) {
        char *place = NULL;

        if (!first) {
            appendText(&args, ", ");
        }

        place = genExp(arg);
        appendText(&args, place);
        free(place);

        first = 0;
        arg = arg->sibling;
    }

    return args;
}

static char *genCall(TreeNode *node, int keepResult) {
    char *args = formatArguments(node->child[0]);
    char *temp = NULL;

    if (keepResult) {
        temp = newTemp();
        emit("%s = call %s(%s)", temp, node->attr, args);
    } else {
        emit("call %s(%s)", node->attr, args);
    }

    free(args);
    return temp;
}

static void genAssign(TreeNode *node) {
    char *target;
    char *value;

    if (node == NULL || node->child[0] == NULL || node->child[1] == NULL) {
        return;
    }

    target = genExp(node->child[0]);
    value = genExp(node->child[1]);

    emit("%s = %s", target, value);

    free(target);
    free(value);
}

static void genIf(TreeNode *node) {
    char *condition = genExp(node->child[0]);
    char *falseLabel = newLabel();

    if (node->child[2] == NULL) {
        emit("fjump %s %s", condition, falseLabel);
        genStmt(node->child[1]);
        emit("label %s", falseLabel);

        free(condition);
        free(falseLabel);
        return;
    }

    {
        char *endLabel = newLabel();

        emit("fjump %s %s", condition, falseLabel);
        genStmt(node->child[1]);
        emit("jump %s", endLabel);
        emit("label %s", falseLabel);
        genStmt(node->child[2]);
        emit("label %s", endLabel);

        free(endLabel);
    }

    free(condition);
    free(falseLabel);
}

static void genWhile(TreeNode *node) {
    char *testLabel = newLabel();
    char *endLabel = newLabel();
    char *condition;

    emit("label %s", testLabel);
    condition = genExp(node->child[0]);
    emit("fjump %s %s", condition, endLabel);
    genStmt(node->child[1]);
    emit("jump %s", testLabel);
    emit("label %s", endLabel);

    free(condition);
    free(testLabel);
    free(endLabel);
}

static void genFor(TreeNode *node) {
    char *testLabel = newLabel();
    char *endLabel = newLabel();

    if (node->child[0] != NULL) {
        if (node->child[0]->nodekind == DeclK) {
            genLocalDecl(node->child[0]);
        } else {
            char *unused = genExp(node->child[0]);
            free(unused);
        }
    }

    emit("label %s", testLabel);

    if (node->child[1] != NULL) {
        char *condition = genExp(node->child[1]);
        emit("fjump %s %s", condition, endLabel);
        free(condition);
    }

    genStmt(node->child[3]);

    if (node->child[2] != NULL) {
        char *unused = genExp(node->child[2]);
        free(unused);
    }

    emit("jump %s", testLabel);
    emit("label %s", endLabel);

    free(testLabel);
    free(endLabel);
}

static void genReturn(TreeNode *node) {
    if (node->child[0] == NULL) {
        emit("return");
    } else {
        char *value = genExp(node->child[0]);
        emit("return %s", value);
        free(value);
    }
}

static void genCompound(TreeNode *node) {
    if (node == NULL) {
        return;
    }

    genStmt(node->child[1]);
}

static void genStmt(TreeNode *node) {
    while (node != NULL) {
        if (node->nodekind == StmtK) {
            switch (node->kind.stmt) {
                case IfK:
                    genIf(node);
                    break;

                case WhileK:
                    genWhile(node);
                    break;

                case ForK:
                    genFor(node);
                    break;

                case ReturnK:
                    genReturn(node);
                    break;

                case CompoundK:
                    genCompound(node);
                    break;

                case AssignK:
                    genAssign(node);
                    break;
            }
        } else if (node->nodekind == DeclK) {
            genLocalDecl(node);
        } else if (node->nodekind == ExpK) {
            if (node->kind.exp == CallK) {
                genCall(node, 0);
            } else {
                char *unused = genExp(node);
                free(unused);
            }
        }

        node = node->sibling;
    }
}

static void genLocalDecl(TreeNode *node) {
    char *value;

    if (node == NULL || node->nodekind != DeclK || node->kind.decl != VarDeclK || node->child[0] == NULL) {
        return;
    }

    value = genExp(node->child[0]);
    emit("%s = %s", node->attr, value);
    free(value);
}

static char *genExp(TreeNode *node) {
    if (node == NULL) {
        return copyString("");
    }

    if (node->nodekind == StmtK && node->kind.stmt == AssignK) {
        char *target = genExp(node->child[0]);
        char *value = genExp(node->child[1]);

        emit("%s = %s", target, value);
        free(value);

        return target;
    }

    if (node->nodekind != ExpK) {
        return copyString("");
    }

    switch (node->kind.exp) {
        case ConstK:
            return copyString(node->attr);

        case IdK:
            if (node->isArray) {
                char *index = genExp(node->child[0]);
                char *access = formatArrayAccess(node->attr, index);

                free(index);
                return access;
            }
            return copyString(node->attr);

        case CallK:
            return genCall(node, 1);

        case OpK: {
            char *left = genExp(node->child[0]);
            char *right = genExp(node->child[1]);
            char *temp = newTemp();
            const char *op = node->attr != NULL ? node->attr : "";

            /* Relacionales y aritmeticas producen valores enteros temporales. */
            emit("%s = %s %s %s", temp, left, op, right);

            free(left);
            free(right);

            return temp;
        }
    }

    return copyString("");
}

static void genDecl(TreeNode *node) {
    if (node == NULL || node->nodekind != DeclK) {
        return;
    }

    if (node->kind.decl == FunDeclK) {
        if (functionCount > 0) {
            emitBlank();
        }

        functionCount++;
        emit("label %s", node->attr);
        genStmt(node->child[1]);
    }
}

static void genNodeList(TreeNode *node) {
    while (node != NULL) {
        if (node->nodekind == DeclK) {
            genDecl(node);
        } else {
            genStmt(node);
            break;
        }

        node = node->sibling;
    }
}

int generateIntermediateCode(TreeNode *tree, FILE *out) {
    codeOut = out;
    tempCount = 0;
    labelCount = 0;
    instructionCount = 0;
    functionCount = 0;

    fprintf(codeOut, "=== CODIGO INTERMEDIO ===\n\n");

    genNodeList(tree);

    return instructionCount;
}
