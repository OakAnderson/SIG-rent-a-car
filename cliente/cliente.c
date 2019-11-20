#include "../veiculo/veiculo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "../usuario/usuario.h"
#include "cliente.h"
#include "../lista/lista.h"
#include "../mylib.h"
#include "../validacoes/validacoes.h"
#include "../menu/menu.h"

#define MOSTRAR 1

#define SALVAR 0
typedef struct client {
    int num;
    int carrosAlugados;
    char nome[52];
    char cpf[15];
    char datNasc[11];
    char bairro [21];
    char endereco[52];
    char complemento[52];
    char telefone[12];
    short int status;
} Cliente;


int clnt_salva( Cliente* pessoa ){
    FILE *arquivo;
    Cliente* save = clnt_cria();
    int result;

    pessoa->status = 0;

    arquivo = fopen( "cliente/Cliente.dat", "a+b" );

    if( arquivo == NULL ){
        arquivo = fopen( "cliente/Cliente.dat", "w+b" );
    }
    
    fseek(arquivo, 0, SEEK_END);
    if( ftell(arquivo) == 0 ){
        pessoa->num = 1;
    } else {
        fseek(arquivo, (sizeof(Cliente))*(-1), SEEK_CUR);
        fread(save, sizeof(Cliente), 1, arquivo);
        pessoa->num = save->num+1;
        fseek(arquivo, 0, SEEK_SET);
    }


    result = fwrite( pessoa, sizeof( Cliente ), 1, arquivo);
    if( result == EOF ){
        return 0;
    }

    fclose(arquivo);

    return 1;
}


Lista* clnt_recupera( void ){
    FILE* arquivo;
    Cliente* pessoa;
    Lista* listaCliente;

    arquivo = fopen("cliente/Cliente.dat", "rb");
    if( arquivo == NULL ){
        printf("Impossível abrir o arquivo de clientes.");
        exit(1);
    }

    listaCliente = arrayCria();

    pessoa = clnt_cria();
    fread( pessoa, sizeof(Cliente), 1, arquivo );
    while( !feof(arquivo) ){
        append(listaCliente, pessoa);
        pessoa = clnt_cria();
        fread( pessoa, sizeof(Cliente), 1, arquivo );
    }

    fclose(arquivo);
    return listaCliente;
}


void clnt_deleta( void ){
    FILE* arquivo;
    Cliente *pessoa, *pessoaR;
    char* resposta;

    pessoa = clnt_recupera_cpf();
    pessoaR = clnt_cria();


    if( pessoa != NULL ){
        arquivo = fopen("cliente/Cliente.dat", "r+b");
        if( arquivo == NULL ){
            printf("Erro ao deletar o cliente\n");
            exit(1);
        }

        do {
            fread( pessoaR, sizeof(Cliente), 1, arquivo );
        } while(clnt_compara(pessoaR, pessoa) && !feof(arquivo) && !pessoa->status);

        printf("Nº %d - - - - - - - - - - - - - - - -\n", pessoa->num);
        clnt_mostra(pessoa);
        printf("- - - - - - - - - - - - - - - - - - -\n");

        resposta = entr_str("Deseja realmente apagar este cliente? ");
        while( !val_SN(resposta) ){
            printf("Digite apenas sim ou não");
            resposta = entr_str("Deseja realmente apagar este cliente? ");
        }
        if( get_resposta(resposta) ){
            pessoa->status = -1;
            fseek(arquivo, (-1)*sizeof(Cliente), SEEK_CUR);
            fwrite(pessoa, sizeof(Cliente), 1, arquivo);
            fclose(arquivo);

            printf("Cliente deletado com sucesso!\n");
            voltar(0);
        } else {
            printf("O cliente não foi deletado.\n");
            voltar(0);
        }
    } else {
        printf("Cliente não encontrado.\n");
        voltar(0);
    }
}


int clnt_compara( Cliente* pessoa1, Cliente* pessoa2 ){
    if ( !strcmp(pessoa1->cpf, pessoa2->cpf) ){
        return 0;
    }

    return 1;
}


int clnt_existe( Cliente* pessoaV ){
    FILE* arquivo;
    Cliente* pessoa = clnt_cria();

    arquivo = fopen("cliente/Cliente.dat", "rb");
    if(arquivo != NULL ){
        fread( pessoa, sizeof(Cliente), 1, arquivo );
        while( !feof(arquivo) ){
            if( !pessoa->status && !clnt_compara(pessoaV, pessoa) ){
                clnt_libera(pessoa);
                fclose(arquivo);
                return 1;
            }
            fread( pessoa, sizeof(Cliente), 1, arquivo );
        }
        fclose(arquivo);
    }

    clnt_libera(pessoa);

    return 0;
}


void clnt_copia( Cliente* destino, Cliente* origem ){
    strcpy(destino->nome, origem->nome);
    strcpy(destino->cpf, origem->cpf);
    strcpy(destino->datNasc, origem->datNasc);
    strcpy(destino->bairro, origem->bairro);
    strcpy(destino->endereco, origem->endereco);
    strcpy(destino->complemento, origem->complemento);
    strcpy(destino->telefone, origem->telefone);
    destino->num = origem->num;
    destino->status = origem->status;
    
}


Cliente* clnt_recupera_nome( void ){
    char* nome;
    Lista* listaCliente;
    Cliente* pessoa;

    nome = entr_str("Digite o nome do cliente: ");
    while( !val_nome( nome ) ){
        printf("Nome inválido.\n");
        nome = entr_str("Digite o nome do cliente: ");
    }

    listaCliente = clnt_recupera();

    for( int i=0; i < size(listaCliente); i++ ){
        pessoa = (Cliente*) pos(listaCliente, i);
        if( cmp_nomes(nome, pessoa->nome) && !pessoa->status ){
            clnt_copia(pessoa, pessoa);
            liberaLista(listaCliente);
            return pessoa;
        }
    }

    return NULL;
}


Cliente* clnt_recupera_cpf( void ){
    char* cpf;
    Lista* listaCliente;
    Cliente* pessoa;

    cpf = entr_str("Digite o cpf do cliente: ");
    while( !val_cpf( cpf ) ){
        printf("Nome inválido.\n");
        cpf = entr_str("Digite o cpf do cliente: ");
    }

    cpf = form_cpf( cpf );

    listaCliente = clnt_recupera();

    for( int i=0; i < size(listaCliente); i++ ){
        pessoa = (Cliente*) pos(listaCliente, i);
        if( !strcmp(pessoa->cpf, cpf) && !pessoa->status ){
            clnt_copia(pessoa, (Cliente*) pos(listaCliente, i));
            liberaLista(listaCliente);
            return pessoa;
        }
    }
    
    return NULL;
}


void clnt_mostra_todos( void ){
    Lista* listaCliente;
    Cliente *busca;

    listaCliente = clnt_recupera();

    for( int i = 0; i < size(listaCliente); i++ ){
        busca = (Cliente*) pos(listaCliente, i);
        if( !busca->status ){
            printf("\nNº %d - - - - - - - - - - - - - - - -\n", busca->num);
            clnt_mostra( busca );
            printf("\n- - - - - - - - - - - - - - - - - - -\n");
        }
    }

    liberaLista( listaCliente );
}


void clnt_re_dados( void ){
    char* nome;
    Cliente* pessoa;

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


void clnt_ins_endereco( Cliente* pessoa ){
    char* endereco, *complemento, *bairro, *numero;

    endereco = entr_str( "Insira o endereço do cliente(av., rua, pç.): " );
    while( !( val_endereco( endereco ) ) ){
        printf("O endereço inserido é inválido.\n");
        endereco = entr_str( "Insira o endereço do cliente(av., rua, pç.): " );
    }

    strcpy( pessoa->endereco, endereco );

    endereco = entr_str( "Nº: " );
    while( !( val_ano( endereco ) ) ){
        printf("O número inserido é inválido.\n");
        endereco = entr_str( "Nº: " );
    }

    strcat(pessoa->endereco, " Nº ");
    strcat(pessoa->endereco, endereco);

    bairro = entr_str( "Insira o bairro: " );
    while( !( val_bairro( bairro ) ) ){
        printf("O bairro inserido é inválido.\n");
        bairro = entr_str( "Insira o bairro do cliente(av., rua, pç.): " );
    }

    strcpy( pessoa->bairro, bairro );

    complemento = entr_str( "Insira o complemento (apto., prox. a): " );
    while( !( val_endereco( complemento ) ) ){
        printf("O complemento inserido é inválido.\n");
        complemento = entr_str( "Insira o complemento (nº, apto.): " );
    }

    strcpy( pessoa->complemento, complemento );
}


void clnt_ins_num( Cliente* pessoa ){
    char* numero;

    numero = entr_str( "Insira um número para contato( (xx) 9xxxx-xxxx ): " );
    while( !( val_num( numero ) ) ){
        printf("O número de celular inserido é inválido.\n");
        numero = entr_str( "Insira um número para contato( (xx) 9xxxx-xxxx ): " );
    }

    form_numero(numero, SALVAR);

    strcpy( pessoa->telefone, numero );
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


void clnt_mostra_endereco( Cliente* pessoa ){
    printf("\nEndereço: %s, bairro: %s\n", pessoa->endereco, pessoa->bairro);
    printf("\nComplemento: %s\n", pessoa->complemento);
}


void clnt_mostra_numero( Cliente* pessoa ){
    char* numero = (char*) malloc (sizeof(char)*16);

    strcpy(numero, pessoa->telefone);
    form_numero(numero, MOSTRAR);
    printf("\nNº de celular: %s\n", numero);
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
    clnt_mostra_numero( pessoa );
    clnt_mostra_endereco( pessoa );
}


void clnt_cad( void ) {
    char* resposta;

    Cliente* novo = clnt_cria();
    clnt_ins_nome( novo );
    clnt_ins_cpf( novo );
    clnt_ins_datNasc( novo );
    clnt_ins_num( novo );
    clnt_ins_endereco( novo );
    novo->carrosAlugados = 0;

    if( !( val_idade(novo->datNasc) ) ){
        clnt_ins_datNasc( novo );
    }

    if( clnt_existe( novo ) ){
        printf("\nJá existe alguém cadastrado com este CPF. Verifique corretamente e tente novamente.\n");
    }

    else {
        clnt_mostra( novo );
        resposta = entr_str("Deseja salvar os dados? ");
        while( !val_SN(resposta) ){
            printf("Digite apenas sim ou não.\n");
            resposta = entr_str("Deseja salvar os dados? ");
        }

        if( tolower(resposta[0]) == 's' ){
            if( !(clnt_salva(novo)) ){
                printf("Não foi possível salvar os dados do cliente.\n");
            }
            else {
                printf("\nCliente cadastrado com sucesso!\n");
            }
        } else {
            resposta = entr_str("Deseja realmente descartar os dados? ");
            while( !val_SN(resposta) ){
                printf("Digite apenas sim ou não.\n");
                resposta = entr_str("Deseja realmente descartar os dados? ");
            }
            if( tolower(resposta[0]) == 'n' ){
                if( !(clnt_salva(novo)) ){
                    printf("Não foi possível salvar os dados do cliente.\n");
                }
                else {
                    printf("\nCliente cadastrado com sucesso!\n");
                }
            }
        }
    }

    clnt_libera( novo );
}
