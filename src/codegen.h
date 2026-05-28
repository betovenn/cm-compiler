#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>

#include "ast.h"

int generateIntermediateCode(TreeNode *tree, FILE *out);

#endif
