#ifndef LEX_H
#define LEX_H

#include "libtinycompiler_export.h"

#define EOP -1
#define ID 1
#define NUM 2
#define OP1 3
#define OP2 4
#define LBR 5
#define RBR 6
#define SEM 7
#define EQ 8
#define CMP 9
#define PRINTFF 10
#define MAX_LEN 20

LIBTINYCOMPILER_STRUCT_EXTENSION(Token) // структура токена
{
    int type; // тип
    int attr; // аттрибут
};

LIBTINYCOMPILER_EXPORT struct Token lex();
LIBTINYCOMPILER_EXPORT struct Token lookahead();

#endif
