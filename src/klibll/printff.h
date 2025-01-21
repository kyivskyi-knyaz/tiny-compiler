#ifndef PRINTFF_H_INCLUDED
#define PRINTFF_H_INCLUDED

#include "../libtinycompiler_export.h"
#include "../sym.h"

LIBTINYCOMPILER_STRUCT_EXTENSION(table_struct) {
    int (*func)(Table *T);
    char *name;
};

int printff(Table *T);

#endif // PRINTFF_H_INCLUDED
