#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int main ( void ){
    int escolha;
    
    imp_menu();
    printf("Selecione: ");
    scanf(" %d", &escolha);
    get_menu( escolha );

    return 0;
}