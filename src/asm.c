#include <stdio.h>

#include "asm.h"
#include "sym.h"
#include "codes.h"
#include "gen.h"

void print_asm ( int *code )
{
    static cmp_opcode = 0;
    int cur_byte;
    int i = 0;

    while ( ( cur_byte = code[i++] ) != RET )
    {
        switch ( cur_byte )
        {
            case PUSH:
                printf ( "PUSH %i\n", code[i++] );
                break;
            case READ:
                cur_byte = code[i++];
                printf ( "READ %s\n",get_sym ( cur_byte )->name );
                break;
            case WRITE:
                cur_byte = code[i++];
                printf ( "WRITE %s\n", get_sym ( cur_byte )->name );
                break;
            case ADD:
                puts ( "ADD POP, POP" );
                break;
            case SUB:
                puts ( "SUB POP, POP" );
                break;
            case MUL:
                puts ( "MUL POP, POP" );
                break;
            case DIV:
                puts ( "DIV POP, POP" );
                break;
            case CMP:
            {
                printf ( "CMP %d, %d\n", get_cmp ( cmp_opcode )->val, get_cmp ( cmp_opcode )->val2 );
                cmp_opcode++;
                break;
            }
            case PRINTFF: {
                puts("PRINTFF POP");
                break;
            }
        }
    }
    puts ( "RET" );
}
