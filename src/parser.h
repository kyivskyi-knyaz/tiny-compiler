#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "libtinycompiler_export.h"
#include "lex.h"

LIBTINYCOMPILER_EXPORT Node * parse(Token tok);

#endif
