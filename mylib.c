#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>
#include "cliente.h"
#include "validacoes.h"
#include "mylib.h"


char* entr_str( char* frase ){
    char entrada[256];
    char* resultado;

    printf("%s", frase);
    scanf(" %255[^\n]", entrada);

    resultado = (char*) malloc (strlen( entrada )*sizeof( char )+1);

    strcpy(resultado, entrada);

    return resultado;
}


int get_resposta( char* opcao ){

    if( opcao[0] == 's' ){
        return 1;
    }

    return 0; 
}


void voltar( void ){
    char* opcao;

    opcao = entr_str("Voltar?(s/n) ");
    while( !( val_SN( opcao ) ) ){
        printf("Aceito apenas: s|n|sim|nao\n");
        opcao = entr_str("Voltar?(s/n) ");
    }

    if( !(get_resposta( opcao )) ){
        voltar();
    }
}


int menu_escolha( int n ){
    char* entrada;

    entrada = entr_str("Opção n°: ");

    while( !( val_inteiro(entrada) ) ){
        printf("Opção inválida.\n");
        entrada = entr_str("Opção n°: ");
    }

    if( atoi(entrada) < 0 || atoi(entrada) > n ){
        do{
            printf("Opção inválida.\n");
            entrada = entr_str("Opção n°: ");
        } while( atoi(entrada) < 0 || atoi(entrada) > n );
    }

    return atoi(entrada);
}


void get_menu_p( int n ){
    system("clear");
    switch (n)
    {
    case 1:
        imp_menu_cliente();
        get_menu_cliente( menu_escolha( 2 ) );
        break;
    
    case 2:
        system("clear");
        printf("EM CONSTRUÇÃO.\n");
        sleep( 2 );
        imp_menu_p();
        get_menu_p( menu_escolha( 4 ) );
        break;

    case 3:
        system("clear");
        printf("EM CONSTRUÇÃO.\n");
        sleep( 2 );
        imp_menu_p();
        get_menu_p( menu_escolha( 4 ) );
        break;

    case 4:
        system("clear");
        printf("EM CONSTRUÇÃO.\n");
        sleep( 2 );
        imp_menu_p();
        get_menu_p( menu_escolha( 4 ) );
        break;

    case 0:
        imp_sobre();
        voltar();
        imp_menu_p();
        get_menu_p( menu_escolha( 4 ) );
        break;

    default:
        printf("Não foi possível abrir um menu.\n");
        break;
    }
}


void imp_menu_p( void ){
    system("clear");
    printf("_ _ _ _ _ SIG CAR: Locadora de automóveis _ _ _ _ _\n\n");
    printf("1 - Menu cliente\n");
    printf("2 - Menu automóvel\n");
    printf("3 - Efetuar devolução\n");
    printf("4 - Efetuar aluguel\n");
    printf("0 - Sobre\n");
}


void get_menu_cliente( int n ){
    switch (n)
    {
    case 1:
        clnt_cad();
        break;

    case 2:
        system("clear");
        printf("EM CONSTRUÇÃO.\n");
        sleep( 2 );
        imp_menu_p();
        get_menu_p( menu_escolha( 2 ) );
        break;

    case 0:
        imp_menu_p();
        get_menu_p( menu_escolha( 4 ) );

    default:
        printf("Não foi possível abrir o menu\n");
        break;
    }
}


void imp_menu_cliente( void ){
    system("clear");
    printf("_ _ _ _ _ MENU CLIENTE _ _ _ _ _\n\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Visualizar dados do cliente\n");
    printf("0 - sair\n");
}


void imp_sobre( void ){
    printf("\n\nPrograma desenvolvido por Anderson Carvalho\n\n_ _ _ _ _ Contatos _ _ _ _ _\n\nEmail: andersonfelipe01@live.com\nGithub: https://github.com/OakAnderson\n");
}


void inicia_programa( void ){
    imp_menu_p();
    get_menu_p( menu_escolha( 4 ) );
}