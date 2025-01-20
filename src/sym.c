#include <stdlib.h>
#include <string.h>

#include "sym.h"
#include "func.h"

struct Table* symbol_table[MAX_SYMBOL_TABLE_SIZE];
struct cmptable* cmp_table[MAX_SYMBOL_TABLE_SIZE];
int table_size = 0;
struct Table *get_sym ( int id )
{
    return symbol_table[id];
}

int add_sym ( char *name )
{
    int i;
    for ( i = 0; i < table_size; i++ )
    {
        if ( strcmp ( symbol_table[i]->name, name ) == 0 )
            return symbol_table[i]->id;
    }

    struct Table *item = safe_malloc ( sizeof ( struct Table ) ); // выделяем место под один item
    item->id = table_size; // записываем айди (индекс в таблице)
    item->name = name; // записываем имя

    symbol_table[table_size] = item; // записываем наш item в глобальный массив указателей с индексом

    return table_size++; // увеличиваем индекс (следующий item будет на +1 индексе от этого)
}

inline void set_cmp ( cmptable* cmptab, int val, int val2 )
{
    cmptab->val = val;
    cmptab->val2 = val2;
}

inline struct cmptable *get_cmp ( int id )
{
    if ( cmp_table[id] == NULL )
        cmp_table[id] = malloc ( sizeof ( cmptable ) );
    return cmp_table[id];
}

void set_sym ( int id, int val )
{
    symbol_table[id]->val = val;
}

int get_table_size()
{
    return table_size;
}
