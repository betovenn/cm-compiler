#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

static int indentno = 0;
extern int lineno;

static void printSpaces(FILE *out) {

    for(int i=0;i<indentno;i++)
        fprintf(out," ");
}

TreeNode* newStmtNode(StmtKind kind) {

    TreeNode *t = (TreeNode*)malloc(sizeof(TreeNode));

    for(int i=0;i<MAXCHILDREN;i++)
        t->child[i] = NULL;

    t->sibling = NULL;
    t->lineno = lineno;

    t->nodekind = StmtK;
    t->kind.stmt = kind;

    t->attr = NULL;
    t->type = NULL;
    t->arraySize = NULL;
    t->isArray = 0;

    return t;
}

TreeNode* newExpNode(ExpKind kind) {

    TreeNode *t = (TreeNode*)malloc(sizeof(TreeNode));

    for(int i=0;i<MAXCHILDREN;i++)
        t->child[i] = NULL;

    t->sibling = NULL;
    t->lineno = lineno;

    t->nodekind = ExpK;
    t->kind.exp = kind;

    t->attr = NULL;
    t->type = NULL;
    t->arraySize = NULL;
    t->isArray = 0;

    return t;
}

TreeNode* newDeclNode(DeclKind kind) {

    TreeNode *t = (TreeNode*)malloc(sizeof(TreeNode));

    for(int i=0;i<MAXCHILDREN;i++)
        t->child[i] = NULL;

    t->sibling = NULL;
    t->lineno = lineno;

    t->nodekind = DeclK;
    t->kind.decl = kind;

    t->attr = NULL;
    t->type = NULL;
    t->arraySize = NULL;
    t->isArray = 0;

    return t;
}

void printTree(TreeNode *tree, int indent, FILE *out) {

    indentno = indent;

    while(tree != NULL) {

        printSpaces(out);

        switch(tree->nodekind) {

            case StmtK:

                switch(tree->kind.stmt) {

                    case IfK:
                        fprintf(out,"If\n");
                        break;

                    case WhileK:
                        fprintf(out,"While\n");
                        break;

                    case ReturnK:
                        fprintf(out,"Return\n");
                        break;

                    case CompoundK:
                        fprintf(out,"Compound\n");
                        break;

                    case AssignK:
                        fprintf(out,"Assign\n");
                        break;
                }

                break;

            case ExpK:

                switch(tree->kind.exp) {

                    case OpK:
                        fprintf(out,"Op: %s\n",tree->attr);
                        break;

                    case ConstK:
                        fprintf(out,"Const: %s\n",tree->attr);
                        break;

                    case IdK:
                        if(tree->isArray)
                            fprintf(out,"ArrayId: %s\n",tree->attr);
                        else
                            fprintf(out,"Id: %s\n",tree->attr);
                        break;

                    case CallK:
                        fprintf(out,"Call: %s\n",tree->attr);
                        break;
                }

                break;

            case DeclK:

                switch(tree->kind.decl) {

                    case VarDeclK:
                        if(tree->isArray)
                            fprintf(out,"VarDecl: %s[%s]\n",tree->attr,tree->arraySize);
                        else
                            fprintf(out,"VarDecl: %s\n",tree->attr);
                        break;

                    case FunDeclK:
                        fprintf(out,"FunDecl: %s\n",tree->attr);
                        break;

                    case ParamK:
                        if(tree->isArray)
                            fprintf(out,"Param: %s[]\n",tree->attr);
                        else
                            fprintf(out,"Param: %s\n",tree->attr);
                        break;
                }

                break;
        }

        indentno += 2;

        for(int i=0;i<MAXCHILDREN;i++)
            printTree(tree->child[i], indentno, out);

        indentno -= 2;

        tree = tree->sibling;
    }
}
