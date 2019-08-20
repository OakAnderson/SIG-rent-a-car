#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "mylib.h"
#include "validacoes.h"


typedef struct client {
    char nome[52];
    char cpf[15];
    char datNasc[11];
} Cliente;


void clnt_ins_nome( Cliente* pessoa ){
    char* resultado;
    
    resultado = entr_str( "Insira o nome do cliente: " );
    while( !( val_nome( resultado ) ) ){
        printf("Nome inserido é inválido.\n");
        resultado = entr_str( "Insira o nome do cliente: " );
    }

    strcpy( pessoa->nome, resultado );
}


void clnt_ins_cpf( Cliente* pessoa ){
    char* resultado;
    
    resultado = entr_str( "Insira o CPF do cliente: " );
    while( !( val_cpf( resultado ) ) ){
        printf("CPF inserido é inválido.\n");
        resultado = entr_str( "Insira o CPF do cliente: " );
    }

    resultado = form_cpf( resultado );

    strcpy( pessoa->cpf, resultado );
}


void clnt_ins_datNasc( Cliente* pessoa ){
    char* resultado;
    int a;
    
    resultado = entr_str( "Insira a data de nascimento do cliente: " );
    while( !( val_data( resultado ) ) ){
        printf("Data inserida é inválida.\n");
        resultado = entr_str( "Insira a data de nascimento do cliente: " );
    }

    resultado = form_data( resultado );

    strcpy( pessoa->datNasc, resultado );
}


void clnt_mostra_nome( Cliente* pessoa ){
    printf("\nNome do cliente: %s\n", pessoa->nome);
}


void clnt_mostra_cpf( Cliente* pessoa ){
    printf("\nCPF do cliente: %s\n", pessoa->cpf);
}


void clnt_mostra_datNasc( Cliente* pessoa ){
    printf("\nData de Nascimento do cliente: %s\n", pessoa->datNasc);
}


void clnt_libera( Cliente* pessoa ){
    free( pessoa );
}


Cliente* clnt_cria( void ){
    Cliente* novo_cliente = ( Cliente* ) malloc ( sizeof( Cliente ) );

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

    if( !( val_idade(novo->datNasc) ) ){
        clnt_ins_datNasc( novo );
    }

    clnt_mostra( novo );

    clnt_libera( novo );
}
