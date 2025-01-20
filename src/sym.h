#ifndef SYM_TABLE
#define SYM_TABLE

#define MAX_SYMBOL_TABLE_SIZE 100

#include "libtinycompiler_export.h"
extern int cmp_tablesize;
extern int table_size;
extern int cmp_table_index  ;
LIBTINYCOMPILER_STRUCT_EXTENSION(Table) // таблица
{
    int id; // айди
    int val; // значение
    char *name; // имя
};

LIBTINYCOMPILER_STRUCT_EXTENSION(cmptable) {
    int val;
    int val2;
};

LIBTINYCOMPILER_EXPORT inline struct cmptable *get_cmp(int id);
LIBTINYCOMPILER_EXPORT inline void set_cmp(cmptable* cmptab, int val, int val2);
LIBTINYCOMPILER_EXPORT struct Table *get_sym(int id);
LIBTINYCOMPILER_EXPORT int add_sym(char *name);
LIBTINYCOMPILER_EXPORT void set_sym(int id, int val);
LIBTINYCOMPILER_EXPORT int get_table_size();

#endif
