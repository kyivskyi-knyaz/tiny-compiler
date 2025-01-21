#include "gen.h"
#include "sym.h"
#include "ast.h"
#include "parser.h"
#include "codes.h"

int obj[MAX_PROGRAM_SIZE];
int *cur = obj;

void gen ( int code )
{
    *cur++ = code;
}

int *compile ( const Node *node )
{
    if ( NULL == node )
        return NULL;

    switch ( node->type )
    {
        case SEQ_TYPE:
            COMPILE_BOTH;
            break;
        case SET_TYPE:
            compile ( node->op2 );
            gen ( WRITE );
            gen ( node->op1->val );
            break;
        case VAR_TYPE:
            gen ( READ );
            gen ( node->val );
            break;
        case NUM_TYPE:
            gen ( PUSH );
            gen ( node->val );
            break;
        case ADD_TYPE:
            COMPILE_BOTH;
            gen ( ADD );
            break;
        case SUB_TYPE:
            COMPILE_BOTH;
            gen ( SUB );
            break;
        case MUL_TYPE:
            COMPILE_BOTH;
            gen ( MUL );
            break;
        case DIV_TYPE:
            COMPILE_BOTH;
            gen ( DIV );
            break;
        case RET_TYPE:
            COMPILE_BOTH;
            gen ( RET );
            break;
        case CMP_TYPE:
            COMPILE_BOTH;
            gen ( CMP );
            break;
        case PRINTFF_FUNC:
            gen ( PRINTFF );
            break;
    }

    return obj;
}
