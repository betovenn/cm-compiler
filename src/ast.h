#ifndef AST_H
#define AST_H

#include <stdio.h>

#define MAXCHILDREN 3

typedef enum {
    StmtK,
    ExpK,
    DeclK
} NodeKind;

typedef enum {
    IfK,
    WhileK,
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

} TreeNode;

TreeNode* newStmtNode(StmtKind kind);
TreeNode* newExpNode(ExpKind kind);
TreeNode* newDeclNode(DeclKind kind);

void printTree(TreeNode *tree, int indent, FILE *out);

#endif