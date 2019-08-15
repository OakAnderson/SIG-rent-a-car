#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "mylib.h"

#define NUMBERS "[0-9]"

typedef struct client {
    char** nome;
    char** cpf;
    char** datNasc;
} Cliente;

void imp_menu( void ){
    system("clear");
    printf("_ _ _ _ _ SIG CAR: Locadora de automóveis _ _ _ _ _\n\n");
    printf("1 - Cadastrar usuário\n");
    printf("2 - Cadastrar automóvel\n");
    printf("3 - Consultar automóveis disponíveis\n");
    printf("4 - Efetuar aluguel\n");
    printf("5 - Sobre\n");
}

void imp_sobre( void ){
    printf("\n\nPrograma desenvolvido por Anderson Carvalho\n\n_ _ _ _ _ Contatos _ _ _ _ _\n\nEmail: andersonfelipe01@live.com\nGithub: https://github.com/OakAnderson\n");
}

void cad_cliente( void ) {
    Cliente* novo;
    printf("Digite o nome do cliente: ");
    at_nome( novo );

    most_nomeCliente( novo );
}

void get_menu( int n ){
    system("clear");
    switch (n)
    {
    case 1:
        cad_cliente();
        break;
    
    case 2:
        printf("EM CONSTRUÇÃO\n");
        break;

    case 3:
        printf("EM CONSTRUÇÃO\n");
        break;

    case 4:
        printf("EM CONSTRUÇÃO\n");
        break;

    case 5:
        imp_sobre();
        break;

    default:
        printf("Foi impossível abrir um menu.\n");
        break;
    }
}

Cliente* cria_cliente( void ){
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

void at_nome( Cliente* pessoa ){
    char nome[128];
    char* resultado;
    
    scanf(" %127[^\n0-9]", nome);

    resultado = ( char* ) malloc ( strlen( nome ) * sizeof( char )+1 );

    strcpy( resultado, nome );

    *pessoa->nome = resultado;
}

void most_nomeCliente( Cliente* pessoa ){
    printf("\nNome do cliente: %s\n", *pessoa->nome);
}

void libera_cliente( Cliente* pessoa ){
    free( pessoa->nome );
}