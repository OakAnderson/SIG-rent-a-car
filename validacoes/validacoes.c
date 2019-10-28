#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "../usuario/usuario.h"
#include "../cliente/cliente.h"
#include "../mylib.h"
#include "validacoes.h"
#include "../menu/menu.h"
#include "../veiculo/veiculo.h"


#define REGEX_EMAIL "^[0-9a-zA-Z]([-\\.a-z0-9_]*[0-9a-zA-Z_\\+])*@([0-9a-zA-Z][-a-z0-9_]*[0-9a-zA-Z]\\.)+[a-zA-Z]{2,9}$" 
// Expressão REGEX_EMAIL baseada no livro "Regular Expression Pocket Reference: Regular Expressions for Perl, Ruby, PHP, Python, C, Java and .NET" de Tony Stubblebine

#define REGEX_DATA "^(3[0-1]|[12][0-9]|0[1-9])/?(0[1-9]|1[0-2])/?([0-9]{2})?([0-9]{2})$"
// Expressão REGEX_DATA baseada no livro "Expressões regulares cookbook" de Jan Goyvaerts

#define REGEX_CPF "^([0-9]{3})\\.?([0-9]{3})\\.?([0-9]{3})-?([0-9]{2})$"

#define REGEX_NUMERO "^\\(?([0-9]{2})\\)?([0-9]{4,5})[-.]?([0-9]{4})$"

#define REGEX_NOME "^[A-Z\\. ]{3,50}+$"

#define REGEX_SN "^(s(im)?|n(ao)?)$"

#define REGEX_PLACA "^[a-z]{3}\\-?[0-9]{4}$"

#define REGEX_MARCA "^[a-z ]+$"

#define REGEX_ANO "^[0-9]{4}$"

#define REGEX_RENAVAM "^[0-9]{11}$"

#define REGEX_USERNAME "^[a-z0-9]{6,20}$"

#define REGEX_SENHA "^[\\x20-\\x7E]{6,20}$"


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


int val_cpf_r( char* cpf ){
    if( cpf[1] != '\0' ){

        if( cpf[1] != '.' && cpf[1] != '-' ){

            if( cpf[0] == cpf[1]  ){
                return val_cpf_r( &cpf[1] );
            }

            else{
                return 1;
            }
        }

        else{

            if( cpf[0] == cpf[2] ){
                return val_cpf_r( &cpf[2] );
            }

            else{
                return 1;
            }
        }
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


int val_placa( char* placa ){
    return val_regex( REGEX_PLACA, placa );
}


int val_marca( char* marca ){
    return val_regex( REGEX_MARCA, marca );
}


int val_ano( char* ano ){
    return val_regex( REGEX_ANO, ano );
}


int val_renavam( char* renavam ){
    int validacao = 0;

    if( val_regex( REGEX_RENAVAM, renavam ) ){
        for( int i = 9, j = 0; i >= 0; i--, j++ ){
            if( j+2 <= 9 ){
                validacao += (renavam[i] - '0')*(j+2);
            }
            else{
                validacao += (renavam[i] - '0')*(j-6);
            }
        }
        
        if( (validacao*10)%11 == (renavam[10] - '0') ){
            return 1;
        }

        else if( (validacao*10)%11 == 10 && (renavam[10] - '0') == 0 ){
            return 1;
        }

        return 0;
    }

    return 0;
}


int val_cpf( char* cpf ){
    int cont=0, digito1 = 0, digito2 = 0;
    char d1, d2;

    if ( val_regex( REGEX_CPF, cpf ) ){
        cont = 10;

        if (!(val_cpf_r(cpf)))
            return 0;

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
        if( digito1 == 10 ){
            digito1 = 0;
        }
        if( digito1 != (d1 - '0') ){
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
            if( digito2 == 10 ){
                digito2 = 0;
            }

            if ((digito1*10 + digito2) != ((d1 - '0')*10) + (d2 - '0')){
                return 0;
            }
        }
    } else {
        return 0;
    }
    
    return 1;
}


int val_SN( char* entrada ){
    return val_regex( REGEX_SN, entrada );
}


int val_username( char* entrada ){
    return val_regex( REGEX_USERNAME, entrada );
}


int val_senha( char* entrada ){
    return val_regex( REGEX_SENHA, entrada );
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


int cmp_nomes(char* nome1, char* nome2){

    for( int i = 0; nome1[i] != '\0'; i++ ){
        if( tolower(nome1[i]) != tolower(nome2[i]) ){
            return 0;
        }
    }

    return 1;
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
