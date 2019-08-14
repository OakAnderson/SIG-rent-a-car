#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int main ( void ){
    int escolha;
    Cliente* cliente1 = cria_cliente( );

    printf("Digite o seu nome: ");
    at_nome( cliente1 );

    if( cliente1 != NULL )
        printf("Executado com sucesso!\n");
    
    most_nomeCliente( cliente1 );
    libera_cliente( cliente1 );
    exit(1);

    imp_menu();
    printf("Selecione: ");
    scanf(" %d", &escolha);
    get_menu( escolha );

    return 0;
}