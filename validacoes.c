#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include "validacoes.h"
#include "mylib.h"

#define REGEX_EMAIL "^[A-Z0-9!#$%&'*+/=?`{|}~^.-]+@[A-Z0-9.-]+$" 
// Expressão REGEX_EMAIL baseada no livro "Expressões regulares Cookbook" de Jan Goyvaerts

#define REGEX_DATA "^(3[0-1]|[12][0-9]|0[1-9])/?(0[1-9]|1[0-2])/?([0-9]{2})?([0-9]{2})$"
// Expressão REGEX_DATA baseada no livro "Expressões regulares cookbook" de Jan Goyvaerts

#define REGEX_CPF "^([0-9]{3})\\.?([0-9]{3})\\.?([0-9]{3})-?([0-9]{2})$"

#define REGEX_NUMERO "^\\(?([0-9]{2})\\)?([0-9]{4,5})[-.]?([0-9]{4})$"

#define REGEX_NOME "^[A-Z\\. ]{3,50}+$"

#define REGEX_SN "^(s(im)?|n(ao)?)$"


int val_regex( char* expReg, char* frase ){
    regex_t expressao;
    regmatch_t combinacoes[1];
    int result;

    result = regcomp( &expressao, expReg, REG_EXTENDED|REG_ICASE );

    if( result != 0 ){
        printf("Erro %d ao compilar a expressão. Abortando.\n", result);
        exit(1);
    }

    if( regexec( &expressao, frase, 1, combinacoes, 0 ) == 0 ){
        return 1;
    }

    return 0;
}


int bissesto( int ano ){
    if( ano % 400 == 0 ){
        return 1;
    }

    else if( (ano % 4 == 0) && (ano % 100 != 0) ){
        return 1;
    }

    return 0;
}



int val_email( char* email ){
    return val_regex( REGEX_EMAIL, email );
}


int val_cpf( char* cpf ){
    int cont=0, digito1 = 0, digito2 = 0;
    char d1, d2;

    if ( val_regex( REGEX_CPF, cpf ) ){
        cont = 10;
        for( int i = 0; cpf[i] != '\0'; i++ ){
            if( ( cpf[i] != '.' ) && cont >= 2 ){
                digito1 += (cpf[i] - '0') * cont;
                cont--;
            }

            if( (cont < 2 && cpf[i] != '-') && cpf[i+1] != '\0' ){
                d1 = cpf[i];
            }
        }

        digito1 = (digito1*10) % 11;
        if( digito1 != d1 - '0' ){
            return 0;
        }

        else{
            cont = 11;
            for( int i = 0; cpf[i] != '\0'; i++ ){
                if( ( cpf[i] != '.' && cpf[i] != '-' ) && cont >= 2 ){
                    digito2 += (cpf[i] - '0') * cont;
                    cont--;
                }

                if( cont < 2 ){
                    d2 = cpf[i];
                }
            }

            digito2 = (digito2*10) % 11;

            if ((digito1*10 + digito2) != ((d1 - '0')*10) + (d2 - '0')){
                return 0;
            }
        }
    }

    else{
        return 0;
    }
    
    return 1;
}


int val_SN( char* entrada ){
    return val_regex( REGEX_SN, entrada );
}


int val_num( char* numero ){
    return val_regex( REGEX_NUMERO, numero );
}


int val_data( char* data ){
    int ano = 0, mes = 0, dia = 0;
    char* resultado = form_data( data );

    if( val_regex( REGEX_DATA, data ) ){
        ano = (resultado[6] - '0') * 1000 + (resultado[7] - '0') * 100 + (resultado[8] - '0') * 10 + (resultado[9] - '0');
        mes = (resultado[3] - '0') * 10 + (resultado[4] - '0');
        dia = (resultado[0] - '0') * 10 + (resultado[1] - '0');

        if( mes == 2 ){
            if( bissesto( ano ) ){
                return dia <= 29;
            }
            else{
                return dia <= 28;
            }
        }

        else if( mes == 4 || mes == 6 || mes == 9 || mes == 11 ){
            return dia <= 30;
        }

        return 1;
    }

    return 0;
}


int val_idade( char* data ){
    int ano = (data[6] - '0')*1000 + (data[7] - '0')*100 + (data[8] - '0')*10 + (data[9] - '0');
    int mes = (data[3] - '0')*10 + (data[4] - '0');
    int dia = (data[0] - '0')*10 + (data[1] - '0');

    if( ano > ano_atual() ){
        printf("Ano inválido\n");
        return 0;
    }

    else if( ano > ano_atual()-18 ){
        printf("É preciso ser maior de 18 para se cadastrar\n");
        return 0;
    }

    else if( ano == ano_atual()-18 ){
        if( mes > mes_atual() ){
            printf("É preciso ser maior de 18 para se cadastrar\n");
            return 0;
        }
        else if( mes == mes_atual() && dia > dia_atual() ){
            printf("É preciso ser maior de 18 para se cadastrar\n");
            return 0;
        }
    }
    
    return 1;
}


int val_nome( char* nome ){
    return val_regex( REGEX_NOME, nome );
}


int val_inteiro( char* entrada ){
    for( int i = 0; entrada[i] != '\0'; i++){
        if( entrada[i] >= '0' && entrada[i] <= '9' && entrada[i] != '\0' ){
            continue;
        }

        else{
            return 0;
        }
    }

    return 1;
}
