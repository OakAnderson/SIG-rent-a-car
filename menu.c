#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "usuario.h"
#include "cliente.h"
#include "mylib.h"
#include "validacoes.h"
#include "menu.h"
#include "veiculo.h"


void get_menu_p( int n ){
    system("clear");
    switch (n)
    {
    case 1:
        imp_menu_cliente();
        get_menu_cliente( menu_escolha( 3 ) );
        break;
    
    case 2:
        imp_menu_veiculo();
        get_menu_veiculo( menu_escolha( 2 ) );
        break;

    case 3:
        system("clear");
        printf("EM CONSTRUÇÃO.\n");
        sleep( 2 );
        imp_menu_p();
        get_menu_p( menu_escolha( 5 ) );
        break;

    case 4:
        system("clear");
        printf("EM CONSTRUÇÃO.\n");
        sleep( 2 );
        imp_menu_p();
        get_menu_p( menu_escolha( 5 ) );
        break;

    case 5:
        imp_sobre();
        voltar(0);
        imp_menu_p();
        get_menu_p( menu_escolha( 5 ) );
        break;
    
    case 0:
        printf("Obrigado por usar nosso sistema!\n");
        sleep(2);
        system("clear");
        exit(0);

    default:
        printf("Não foi possível abrir um menu.\n");
        break;
    }
}


void imp_menu_p( void ){
    system("clear");
    printf("_ _ _ _ _ SIG CAR: Locadora de automóveis _ _ _ _ _\n\n");
    printf("1 - Menu cliente\n");
    printf("2 - Menu veículo\n");
    printf("3 - Efetuar devolução\n");
    printf("4 - Efetuar aluguel\n");
    printf("5 - Sobre\n");
    printf("0 - Encerrar o programa\n");
}


void get_menu_cliente( int n ){
    switch (n)
    {
    case 1:
        system("clear");
        printf("\n\n_ _ _ _ _ CADASTRO DE CLIENTE _ _ _ _ _\n\n");
        clnt_cad();
        voltar(0);
        imp_menu_p();
        get_menu_p( menu_escolha( 5 ) );
        break;

    case 2:
        system("clear");
        clnt_re_dados();
        imp_menu_cliente();
        get_menu_cliente( menu_escolha( 2 ) );
    /*
        system("clear");
        printf("EM CONSTRUÇÃO.\n");
        sleep( 2 );
        imp_menu_p();
        get_menu_p( menu_escolha( 5 ) );
        break;
    */
    case 3:
        system("clear");
        clnt_mostra_todos();
        voltar(0);
        imp_menu_cliente();
        get_menu_cliente( menu_escolha( 2 ) );
    case 0:
        imp_menu_p();
        get_menu_p( menu_escolha( 5 ) );

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
    printf("3 - Visualizar todos os clientes\n");
    printf("0 - sair\n");
}


void get_menu_veiculo( int n ){
    switch (n)
    {
    case 1:
        system("clear");
        printf("\n\n_ _ _ _ _ CADASTRO DE VEÍCULO _ _ _ _ _\n\n");
        veic_cad();
        voltar(0);
        imp_menu_p();
        get_menu_p( menu_escolha( 5 ) );

    case 2:
        system("clear");
        printf("EM CONSTRUÇÃO.\n");
        sleep( 2 );
        imp_menu_p();
        get_menu_p( menu_escolha( 5 ) );
        break;
    case 0:
        imp_menu_p();
        get_menu_p( menu_escolha( 5 ) );
        break;
    
    default:
        printf("Não foi possível abrir o menu\n");
        break;
    }
}


void imp_menu_veiculo( void ){
    system("clear");
    printf("_ _ _ _ _ MENU VEÍCULO _ _ _ _ _\n\n");
    printf("1 - Cadastrar veículo\n");
    printf("2 - Visualizar status do veículo\n");
    printf("0 - sair\n");
}


void imp_sobre( void ){
    printf("\n\nPrograma desenvolvido por Anderson Carvalho\n\n_ _ _ _ _ Contatos _ _ _ _ _\n\nEmail: andersonfelipe01@live.com\nGithub: https://github.com/OakAnderson\n");
}


void imp_clnt_visualizarDados( void ){
    printf("_ _ _ _ _ VISUALIZAR DADOS DE CLIENTE _ _ _ _ _\n\n");
    printf("1 - Pesquisar por nome\n");
    printf("2 - Pesquisar por CPF\n");
    printf("0 - sair\n");
}


void inicia_programa( void ){
    imp_menu_p();
    get_menu_p( menu_escolha( 5 ) );
}