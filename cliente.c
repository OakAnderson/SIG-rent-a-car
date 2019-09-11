#ifndef BIBLIOTECAS
    #define BIBLIOTECAS
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    #include <time.h>
    #include <unistd.h>
    #include <ctype.h>
    #include "cliente.h"
    #include "mylib.h"
    #include "validacoes.h"
    #include "menu.h"
    #include "veiculo.h"
#endif


typedef struct client {
    char nome[52];
    char cpf[15];
    char datNasc[11];
} Cliente;


int clnt_salva( Cliente* pessoa ){
    FILE *arquivo;
    int result;

    arquivo = fopen( "Cliente.dat", "ab" );

    if( arquivo == NULL ){
        arquivo = fopen( "Cliente.dat", "wb" );
    }

    result = fwrite( pessoa, sizeof( Cliente ), 1, arquivo);
    if( result == EOF ){
        return 0;
    }

    fclose(arquivo);

    return 1;
}


Cliente* clnt_recupera_nome( void ){
    char* nome;
    FILE* arquivo;
    Cliente* pessoa;

    nome = entr_str("Digite o nome do cliente: ");
    while( !val_nome( nome ) ){
        printf("Nome inválido.\n");
        nome = entr_str("Digite o nome do cliente: ");
    }

    arquivo = fopen("Cliente.dat", "rb");

    fread( pessoa, sizeof(Cliente), 1, arquivo );
    while( !feof(arquivo) ){
        if( cmp_nomes(nome, pessoa->nome) ){
            fclose(arquivo);
            return pessoa;
        }
        fread( pessoa, sizeof(Cliente), 1, arquivo );
    }

    fclose(arquivo);

    return NULL;
}


Cliente* clnt_recupera_cpf( void ){
    char* cpf;
    FILE* arquivo;
    Cliente* pessoa;

    cpf = entr_str("Digite o cpf do cliente: ");
    while( !val_cpf( cpf ) ){
        printf("Nome inválido.\n");
        cpf = entr_str("Digite o cpf do cliente: ");
    }

    cpf = form_cpf( cpf );

    arquivo = fopen("Cliente.dat", "rb");

    fread( pessoa, sizeof(Cliente), 1, arquivo );
    while( !feof(arquivo) ){
        if( strcmp(cpf, pessoa->cpf) == 0 ){
            fclose(arquivo);
            return pessoa;
        }
        fread( pessoa, sizeof(Cliente), 1, arquivo );
    }

    fclose(arquivo);

    clnt_libera( pessoa );
    return NULL;
}


void clnt_re_dados( void ){
    char* nome;
    Cliente* pessoa = NULL;

    imp_clnt_visualizarDados();

    switch ( menu_escolha(2) )
    {
    case 1:
        pessoa  = clnt_recupera_nome();
        break;
    
    case 2:
        pessoa = clnt_recupera_cpf();
        break;

    case 0:
        return;

    default:
        printf("Não foi possível abrir o menu\n");
        break;
    }

    if( pessoa != NULL ){
        clnt_mostra( pessoa );
        clnt_libera( pessoa );
        voltar(0);
    } else {
        printf("Cliente não encontrado!\n");
        sleep(2);
    }
}


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

    if( !(clnt_salva(novo)) ){
        printf("Não foi possível salvar os dados do cliente.\n");
    }

    clnt_libera( novo );
}
