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



// Função copiada de https://pt.stackoverflow.com/questions/9427/limpeza-do-buffer-do-teclado-após-scanf
void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}


float eval(float num, int exp){
    if( exp == 1 ){
        return num;
    } else if( exp == 0){
        return 1;
    }

    if( exp > 0 )
        return num * eval(num, exp-1);
    else
        return eval(num, exp+1)/num;
}


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


char* form_numero( char* entrada, int mostrar ){
    int indx = 0, i = 0;
    char* saida;

    if (mostrar){
        saida = (char*) malloc (sizeof(char)*16);
        for( i=0; entrada[i] != '\0'; i++ ){
            if (i == 0){
                saida[0] = '(';
                saida[1] = entrada[i];
                indx++;
            }

            else if (i == 1){
                saida[2] = entrada[i];
                saida[3] = ')';
                indx++;
            }
            
            else if ((strlen(entrada) == 11 && i == 6) || (strlen(entrada) == 10 && i == 5)){
                saida[indx] = entrada[i];
                saida[indx+1] = '-';
                indx++;
            }

            else{
                saida[indx] = entrada[i];
            }
            
            indx++;
        }

    }
    else{
        saida = (char*) malloc (sizeof(char)*12);
        for( i = 0; entrada[i] != '\0'; i++ ){
            if( !(entrada[i] == '(' || entrada[i] == ')' || entrada[i] == ' ' || entrada[i] == '-' )){
                saida[indx] = entrada[i];
                indx++;
            }
        }
        saida[indx] = '\0';
    }

    strcpy(entrada, saida);
}


float form_preco( char* entrada ){
    float preco;
    int v = 0, count = 0;

    for( int i = 0; entrada[i] != '\0'; i++ ){
        if( entrada[i] == ',' || entrada[i] == '.' ){
            v = i;
        }
    }

    if( !v ){
        v = strlen(entrada);
    }
    for( int i = 0; entrada[i] != '\0'; i++ ){
        printf("GOTCHA\n");
        if( v > 0 && entrada[i] != '.' && entrada[i] != ',' ){
            preco += (entrada[i] - '0') * eval(10.0, --v);
        }
        else if( entrada[i-1] == ',' || entrada[i-1] == '.' ){
            preco += (entrada[i] - '0') * 0.1;
        }
        else if( entrada[i-2] == ',' || entrada[i-2] == '.' ){
            preco += (entrada[i] - '0') * 0.01;
        }
    }

    return preco;
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