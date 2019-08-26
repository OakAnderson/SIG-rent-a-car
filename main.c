#ifndef BIBLIOTECAS
    #define BIBLIOTECAS
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    #include <time.h>
    #include <unistd.h>
    #include "cliente.h"
    #include "mylib.h"
    #include "validacoes.h"
    #include "menu.h"
    #include "veiculo.h"
#endif

/* Comando para compilação:
gcc -c cliente.c
gcc -c menu.c
gcc -c mylib.c
gcc -c validacoes.c
gcc -c veiculo.c
gcc -o exe main.c cliente.o menu.o mylib.o validacoes.o veiculo.o

*/


int main ( void ){
    
    inicia_programa();

    return 0;
}