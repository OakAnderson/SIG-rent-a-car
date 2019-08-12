#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

void imp_menu( void ){
    system("clear");
    printf("_ _ _ _ _ SIG CAR: Locadora de automóveis _ _ _ _ _\n\n");
    printf("1 - Cadastrar usuário\n");
    printf("2 - Cadastrar automóvel\n");
    printf("3 - Consultar automóveis disponíveis\n");
    printf("4 - Efetuar aluguel\n");
    printf("5 - Sobre")
}

void imp_sobre( void ){
    printf("\n\nPrograma desenvolvido por Anderson Carvalho\n\n_ _ _ _ _ Contatos _ _ _ _ _\n\nEmail: andersonfelipe01@live.com\nGithub: https://github.com/OakAnderson\n");
}

void get_menu( int n ){
    switch (n)
    {
    case 1:
        printf("EM CONSTRUÇÃO\n");
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