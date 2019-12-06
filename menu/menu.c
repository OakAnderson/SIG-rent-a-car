#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "../veiculo/veiculo.h"
#include "../aluguel/aluguel.h"
#include "../usuario/usuario.h"
#include "../cliente/cliente.h"
#include "../mylib.h"
#include "../validacoes/validacoes.h"
#include "menu.h"


void menuCliente( void ){
    int escolha;

    do{
        imp_menu_cliente();
        escolha = menu_escolha(5);
        get_menu_cliente( escolha );
    }while( escolha != 0 );
}


void menuVeiculo( void ){
    int escolha;

    do{
        imp_menu_veiculo();
        escolha = menu_escolha(4);
        get_menu_veiculo( escolha );
    }while( escolha != 0 );
}


void menuAluguel( void ){
    int escolha;

    do{
        imp_menu_aluguel();
        escolha = menu_escolha(2);
        get_menu_aluguel( escolha );
    }while( escolha != 0 );
}


void get_menu_p( int n ){
    system("clear");
    switch (n)
    {
    case 1:
        menuCliente();
        break;
    
    case 2:
        menuVeiculo();
        break;

    case 3:
        menuAluguel();
        break;

    case 4:
        imp_sobre();
        voltar();
        imp_menu_p();
        get_menu_p( menu_escolha( 4 ) );
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
    printf("3 - Menu aluguel\n");
    printf("4 - Sobre\n");
    printf("0 - Encerrar o programa\n");
}


void get_menu_cliente( int n ){
    switch (n)
    {
    case 1:
        system("clear");
        printf("\n\n_ _ _ _ _ CADASTRO DE CLIENTE _ _ _ _ _\n\n");
        clnt_cad();
        voltar();
        break;

    case 2:
        system("clear");
        clnt_re_dados();
        break;

    case 3:
        system("clear");
        clnt_mostra_todos();
        voltar();
        break;

    case 4:
        system("clear");
        clnt_edita_dados();
        voltar();
        break;

    case 5:
        system("clear");
        clnt_deleta();
        break;

    case 0:
        break;

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
    printf("4 - Editar Cliente\n");
    printf("5 - Deletar cliente\n");
    printf("0 - sair\n");
}


void get_menu_veiculo( int n ){
    switch (n)
    {
    case 1:
        system("clear");
        printf("\n\n_ _ _ _ _ CADASTRO DE VEÍCULO _ _ _ _ _\n\n");
        veic_cad();
        voltar();
        break;

    case 2:
        system("clear");
        veic_re_dados();
        break;
    case 3:
        system("clear");
        veic_mostra_todos();
        voltar();
        break;

    case 4:
        system("clear");
        printf("- - - - - DELETAR CLIENTE - - - - -\n\n");
        veic_deleta();
        break;

    case 0:
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
    printf("3 - Mostrar todos os veículos\n");
    printf("4 - Deletar veículo\n");
    printf("0 - sair\n");
}


void imp_menu_aluguel( void ){
    system("clear");
    printf("\n- - - - - MENU ALUGUEL - - - - -\n");
    printf("1 - Alugar um veículo\n");
    printf("2 - Devolver um veículo\n");
    printf("0 - sair\n");
}


void get_menu_aluguel( int n ){
    switch (n)
    {
    case 1:
        system("clear");
        printf("- - - - - ALUGUEL DE VEÍCULOS - - - - -\n\n");
        alugarVeiculo();
        voltar();
        break;
    
    case 2:
        system("clear");
        printf("- - - - - DEVOLUÇÃO DE VEÍCULOS - - - - -\n\n");        
        devolverVeiculo();
        voltar();
        break;
    
    case 0:
        break;
    
    default:
        break;
    }
}


void imp_sobre( void ){
    printf("\n\nPrograma desenvolvido por Anderson Carvalho\n\n_ _ _ _ _ Contatos _ _ _ _ _\n\nEmail: andersonfelipe01@live.com\nGithub: https://github.com/OakAnderson\n");
}


void imp_clnt_visualizarDados( void ){
    printf("_ _ _ _ _ VISUALIZAR DADOS DE CLIENTE _ _ _ _ _\n\n");
}


void inicia_programa( void ){
    int escolha;

    do{
        imp_menu_p();
        escolha = menu_escolha( 4 );
        get_menu_p( escolha );
    } while( escolha != 0 );
}