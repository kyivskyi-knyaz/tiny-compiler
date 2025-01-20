#include <stdlib.h>

#include "input.h"
#include "lex.h"
#include "parser.h"
#include "gen.h"
#include "vm.h"
#include "asm.h"
#include "func.h"

#define MIN_ARGS 2
#define SOURCE_ARG 1

int main ( int argc, char **argv )
{
    int *code;
    if ( argc < MIN_ARGS ) // проверка на минимальное число аргументов
    {
        fatal_error ( "No file provided! Usage: compiler <source>" );
    }

    open_file ( argv[SOURCE_ARG] ); // открываем файл

    code = compile ( parse ( lex() ) );

    close_file();

    puts ( "Generated ASM:" );
    print_asm ( code );

    puts ( "Execution result:" );
    run ( code );

    return EXIT_SUCCESS;
}
