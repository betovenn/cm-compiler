#ifndef AST_H
#define AST_H

#include <stdio.h>

#define MAXCHILDREN 4

typedef enum {
    StmtK,
    ExpK,
    DeclK
} NodeKind;

typedef enum {
    IfK,
    WhileK,
    ForK,
    ReturnK,
    CompoundK,
    AssignK
} StmtKind;

typedef enum {
    OpK,
    ConstK,
    IdK,
    CallK
} ExpKind;

typedef enum {
    VarDeclK,
    FunDeclK,
    ParamK
} DeclKind;

typedef struct treeNode {

    struct treeNode *child[MAXCHILDREN];
    struct treeNode *sibling;

    int lineno;

    NodeKind nodekind;

    union {

        StmtKind stmt;
        ExpKind exp;
        DeclKind decl;

    } kind;

    char *attr;
    char *type;
    char *arraySize;
    int isArray;

} TreeNode;

TreeNode* newStmtNode(StmtKind kind);
TreeNode* newExpNode(ExpKind kind);
TreeNode* newDeclNode(DeclKind kind);

void printTree(TreeNode *tree, int indent, FILE *out);

#endif
