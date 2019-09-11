#ifndef BIBLIOTECAS
    #define BIBLIOTECAS
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    #include <time.h>
    #include <unistd.h>
    #include <ctype.h>
    #include "cliente.h"
    #include "mylib.h"
    #include "validacoes.h"
    #include "menu.h"
    #include "veiculo.h"
#endif


int main ( void ){
    char* a;

    system("clear");
    printf("\n_ _ _ _ _ LOGIN _ _ _ _ _\n\n");

    a = entr_str("Usuário: ");
    a = entr_str("Senha: ");

    free(a);

    inicia_programa();
    return 0;
}