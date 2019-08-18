#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "mylib.h"
#include "validacoes.h"


typedef struct client {
    char** nome;
    char** cpf;
    char** datNasc;
} Cliente;


void clnt_ins_nome( Cliente* pessoa ){
    char* resultado;
    
    resultado = entr_str( "Insira o nome do cliente: " );
    while( !( val_nome( resultado ) ) ){
        printf("Nome inserido é inválido.\n");
        resultado = entr_str( "Insira o nome do cliente: " );
    }

    *pessoa->nome = resultado;
}


void clnt_ins_cpf( Cliente* pessoa ){
    char* resultado;
    
    resultado = entr_str( "Insira o CPF do cliente: " );
    while( !( val_cpf( resultado ) ) ){
        printf("CPF inserido é inválido.\n");
        resultado = entr_str( "Insira o CPF do cliente: " );
    }

    *pessoa->cpf = resultado;
}


void clnt_ins_datNasc( Cliente* pessoa ){
    char* resultado;
    
    resultado = entr_str( "Insira a data de nascimento do cliente: " );
    while( !( val_data( resultado ) ) ){
        printf("Data inserida é inválida.\n");
        resultado = entr_str( "Insira a data de nascimento do cliente: " );
    }

    *pessoa->datNasc = resultado;
}


void clnt_mostra_nome( Cliente* pessoa ){
    printf("\nNome do cliente: %s\n", *pessoa->nome);
}


void clnt_mostra_cpf( Cliente* pessoa ){
    printf("\nCPF do cliente: %s\n", *pessoa->cpf);
}


void clnt_mostra_datNasc( Cliente* pessoa ){
    printf("\nData de Nascimento do cliente: %s\n", *pessoa->datNasc);
}


void clnt_libera( Cliente* pessoa ){
    free( pessoa->nome );
}


Cliente* clnt_cria( void ){
    Cliente* novo_cliente = ( Cliente* ) malloc ( sizeof( Cliente ) );

    novo_cliente->nome = ( char** ) malloc ( sizeof( char* ) );
    novo_cliente->cpf = ( char** ) malloc ( sizeof( char* ) );
    novo_cliente->datNasc = ( char** ) malloc ( sizeof( char* ) );

    if( novo_cliente == NULL ){
        printf("Memória insuficiente. Encerrando o programa...");
        exit(1);
    }

    return novo_cliente;
}


void clnt_mostra( Cliente* pessoa ){
    clnt_mostra_nome( pessoa );
    clnt_mostra_cpf( pessoa );
    clnt_mostra_datNasc( pessoa );
}


void clnt_cad( void ) {
    Cliente* novo = clnt_cria();
    clnt_ins_nome( novo );
    clnt_ins_cpf( novo );
    clnt_ins_datNasc( novo );

    clnt_mostra( novo );

    clnt_libera( novo );
}
