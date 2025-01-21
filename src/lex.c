#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"
#include "input.h"
#include "defs.h"
#include "func.h"
#include "sym.h"
#include "ast.h"

bool look_done = false;
struct Token look_tok;
int value;
int value2;
int cmp_table_index = 0;
struct Token lex()
{
    int ch;
    struct Token tok;

    // If lookaheaded
    if (look_done) {
        look_done = false;

        return look_tok;
    }

    eat:
    switch (ch = fgetc(get_file())) {
        case ' ': case '\n': goto eat;
        case EOF: tok.type = EOP; break;
        case '+': tok.type = OP1; tok.attr = ADD_TYPE; break;
        case '-': tok.type = OP1; tok.attr = SUB_TYPE; break;
        case '*': tok.type = OP2; tok.attr = MUL_TYPE; break;
        case '/': tok.type = OP2; tok.attr = DIV_TYPE; break;
        case '(': tok.type = LBR; break;
        case ')': tok.type = RBR; break;
        case '=': tok.type = EQ; break;
        case ';': tok.type = SEM; break;
        case 'p':
        {
            char buffer[8];
            buffer[0] = ch;
            buffer[1] = fgetc(get_file());
            buffer[2] = fgetc(get_file());
            buffer[3] = fgetc(get_file());
            buffer[4] = fgetc(get_file());
            buffer[5] = fgetc(get_file());
            buffer[6] = fgetc(get_file());
            buffer[7] = '\0';

            if (strcmp(buffer, "printff") == 0)
             //   printf("printff now\n");
            tok.type = PRINTFF;
            tok.attr = PRINTFF_FUNC;
            fgetc(get_file()); // space after printff

            ch = fgetc(get_file());
            if (isalpha(ch)) {
                char *idname = safe_malloc(MAX_LEN);
                int len = 0;
                idname[len++] = ch;
                do {
                    if (MAX_LEN == len)
                        fatal_error("Lexer: Variable name is too long");
                    idname[len++] = (ch = fgetc(get_file()));
                } while (isalpha(ch) || isdigit(ch));
                idname[len - 1] = '\0';

                ungetc(ch, get_file());
            }
        }
        break;
        case 'C':
        {
            char buffer[4];
            buffer[0] = ch;
            buffer[1] = fgetc(get_file());
            buffer[2] = fgetc(get_file());
            buffer[3] = '\0';

            if (strcmp(buffer, "CMP") == 0) {
                tok.type = CMP;
                tok.attr = CMP_TYPE;
                LIBTINYCOMPILER_DEPRECATED_SOURCE("CMP");
                ch = fgetc(get_file());
                X:
                ch = fgetc(get_file());

                if (isdigit(ch)) {
                    value = ch - '0';
                    while (isdigit(ch = fgetc(get_file())))
                        value = value * 10 + (ch - '0');
                } else if (ch == ' ')
                    goto X;
                /*else if (isalpha(ch)) {
                 *                   char *id_name = safe_malloc(MAX_LEN);
                 *                   int len = 0;
                 *                   id_name[len++] = ch;
                 *                   do {
                 *                       if (MAX_LEN == len)
                 *                           fatal_error("Lexer: Variable name is too long");
                 *                       id_name[len++] = (ch = fgetc(get_file()));
            } while (isalpha(ch) || isdigit(ch));
            }*/
                Y:
                ch = fgetc(get_file());
                if (isdigit(ch)) {
                    value2 = ch - '0';
                    while (isdigit(ch = fgetc(get_file())))
                        value2 = value2 * 10 + (ch - '0');
                    set_cmp(get_cmp(cmp_table_index), value, value2);
                    cmp_table_index++;
                } else if(ch == ' ') {
                    goto Y;
                }
                ungetc(ch, get_file());
                break;
            }
        }
        default:
            // ID
            if (isalpha(ch)) {
                char *id_name = safe_malloc(MAX_LEN);
                int len = 0;
                id_name[len++] = ch;
                do {
                    if (MAX_LEN == len)
                        fatal_error("Lexer: Variable name is too long");
                    id_name[len++] = (ch = fgetc(get_file()));
                } while (isalpha(ch) || isdigit(ch));
                id_name[len - 1] = '\0';

                tok.type = ID;
                tok.attr = add_sym(id_name);

                // NUM
            } else if (isdigit(ch)) {
                int val = ch - '0';
                while (isdigit(ch = fgetc(get_file())))
                    val = val * 10 + (ch - '0');
                tok.type = NUM;
                tok.attr = val;

                // Error
            } else {
                fatal_error("Lexer: Unexpected symbol");
            }

            ungetc(ch, get_file());
    }
    return tok;
}

struct Token lookahead()
{
    look_tok = lex();
    look_done = true;

    return look_tok;
}
