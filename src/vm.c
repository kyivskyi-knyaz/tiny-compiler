#include <stdio.h>

#include "vm.h"
#include "stack.h"
#include "sym.h"
#include "codes.h"

int *cur_byte;

int next_byte()
{
    return *cur_byte++;
}

void run ( int *code )
{
    static cmp_code = 0;
    int arg1, arg2;
    cur_byte = code;

    next_op:
    switch ( next_byte() )
    {
        case PUSH:
            push ( next_byte() );
            goto next_op;
        case READ:
            push ( get_sym ( next_byte() )->val );
            goto next_op;
        case WRITE:
            set_sym ( next_byte(), pop() );
            goto next_op;
        case ADD:
            POP_BOTH;
            push ( arg1 + arg2 );
            goto next_op;
        case SUB:
            POP_BOTH;
            push ( arg1 - arg2 );
            goto next_op;
        case MUL:
            POP_BOTH;
            push ( arg1 * arg2 );
            goto next_op;
        case DIV:
            POP_BOTH;
            push ( arg1 / arg2 );
            goto next_op;
        case CMP:
        {
            arg1 = get_cmp ( cmp_code )->val;
            arg2 = get_cmp ( cmp_code )->val2;
            printf ( "CMP %d, %d %s\n", arg1, arg2, arg1 == arg2 ? "true" : "false" );
            cmp_code++;
            goto next_op;
        }
        case PRINTFF:
        {
            printf ( "%s = %i\n", get_sym ( 0 )->name, get_sym ( 0 )->val );
            goto next_op;
        }
        case RET:
        {
            int i;
            for ( i = 0; i < get_table_size(); i++ )
            {
            //    printf ( "%s = %i\n", get_sym ( i )->name, get_sym ( i )->val );
            }
        }

        return;
    }

}
