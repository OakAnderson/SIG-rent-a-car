#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "usuario/usuario.h"
#include "cliente/cliente.h"
#include "mylib.h"
#include "validacoes/validacoes.h"
#include "menu/menu.h"
#include "veiculo/veiculo.h"


char* entr_str( char* frase ){
    char entrada[128];
    char* resultado;

    printf("%s", frase);
    scanf(" %127[^\n]", entrada);

    resultado = (char*) malloc (strlen( entrada )*sizeof( char )+1);

    strcpy(resultado, entrada);

    return resultado;
}


void limpa_linha( int num ){
    for( int i = 0; i < num; i++){
        printf("\033[A\33[2K\r");
    }
}


int ano_atual( void ){
    struct tm* data;
    time_t segundos;

    time(&segundos);
    data = localtime(&segundos);

    return data->tm_year+1900;
}


int mes_atual( void ){
    struct tm* data;
    time_t segundos;

    time(&segundos);
    data = localtime(&segundos);

    return data->tm_mon+1;
}


int dia_atual( void ){
    struct tm* data;
    time_t segundos;

    time(&segundos);
    data = localtime(&segundos);

    return data->tm_mday;
}


char* form_cpf( char* entrada ){
    int cont = 0, p2 = 7, h1 = 11;
    char* resultado;

    resultado = (char*) malloc ( 15*sizeof(char) );

    for( int i = 0; entrada[i] != '\0'; i++ ){
        if((i == 3 || i == p2) && entrada[i] != '.' ){
            resultado[cont] = '.';
            cont++;
            p2--;
            h1--;
        }

        else if( i == h1 && entrada[i] != '-' ){
            resultado[cont] = '-';
            cont++;
        }

        resultado[cont] = entrada[i];
        cont++;
    }

    return resultado;
}


char* form_data( char* entrada ){
    int cont = 0, b2 = 5;
    char* resultado;

    resultado = ( char* ) malloc ( 11*sizeof( char ) );

    for( int i = 0; entrada[i] != '\0'; i++ ){
        if( (i == 2 || i == b2 ) && entrada[i] != '/' ){
            resultado[cont] = '/';
            cont++;
            b2--;
        }

        resultado[cont] = entrada[i];
        cont++;

        if( entrada[i+1] == '\0' && strlen( resultado ) == 8 ){
            resultado[8] = resultado[6];
            resultado[9] = resultado[7];
            resultado[6] = '1';
            resultado[7] = '9';
        }
    }

    return resultado;
}


// Função copiada de https://pt.stackoverflow.com/questions/9427/limpeza-do-buffer-do-teclado-após-scanf
void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}


int get_resposta( char* opcao ){

    if( opcao[0] == 's' || opcao[0] == 'S' ){
        return 1;
    }

    return 0; 
}


void voltar( int linhas ){
    char* opcao;
    int cont = 0, erro = 0;

    printf("\nAperte ENTER para voltar...\n");
    flush_in();
    getchar();
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