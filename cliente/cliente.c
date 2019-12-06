#include "../veiculo/veiculo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "../aluguel/aluguel.h"
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


char* clnt_nome( Cliente* pessoa ){
    return pessoa->nome;
}


char* clnt_cpf( Cliente* pessoa ){
    return pessoa->cpf;
}


int clnt_status( Cliente* pessoa ){
    return pessoa->status;
}


int clnt_num( Cliente* pessoa ){
    return pessoa->num;
}


int clnt_carrosAlugados( Cliente* pessoa ){
    return pessoa->carrosAlugados;
}


int clnt_edita( Cliente* pessoa, int campo, void* alteracao ){
    FILE* arquivo;
    Cliente* busca;
    short int achou = 0;

    if( campo == CARROS_ALUGADOS ){
        pessoa->carrosAlugados = *((int*) alteracao);
    } else if ( campo == NOME ){
        strcpy( pessoa->nome, (char*) alteracao );
    } else if ( campo == ENDERECO ){
        strcpy( pessoa->endereco, (char*) alteracao );
    } else if ( campo == DATNASC ){
        strcpy( pessoa->datNasc, (char*) alteracao );
    } else if ( campo == STATUS ){
        pessoa->status = *((int*) alteracao);
    }

    arquivo = fopen( "cliente/Cliente.dat", "r+b" );

    if( arquivo == NULL ){
        printf("Não foi possível salvar as informações\n");
        exit(0);
    }


    busca = clnt_cria();
    while( !achou && fread( busca, sizeof(Cliente), 1, arquivo ) ){
        if( !strcmp(busca->cpf, pessoa->cpf) && busca->status != -1 ){
            fseek( arquivo, sizeof(Cliente)*(-1), SEEK_CUR );
            achou = 1;
        }
    }

    if( achou ){
        fwrite(pessoa, sizeof(Cliente), 1, arquivo);
    }

    fclose(arquivo);

    return achou;
}


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


Array* clnt_recupera_lista( void ){
    FILE* arquivo;
    Cliente* pessoa;
    Array* listaCliente;

    arquivo = fopen("cliente/Cliente.dat", "rb");
    if( arquivo == NULL ){
        printf("Impossível abrir o arquivo de clientes.");
        exit(1);
    }

    listaCliente = arrayCria();

    pessoa = clnt_cria();
    fread( pessoa, sizeof(Cliente), 1, arquivo );
    while( !feof(arquivo) ){
        if( pessoa->status == 0 ){
            append(listaCliente, pessoa);
            pessoa = clnt_cria();
        }
        fread( pessoa, sizeof(Cliente), 1, arquivo );
    }

    fclose(arquivo);
    return listaCliente;
}


Tree* clnt_recupera_arvoreNome( void ){
    FILE* arquivo;
    Cliente* pessoa;
    Tree* arvoreCliente;

    arquivo = fopen("cliente/Cliente.dat", "rb");
    if( arquivo == NULL ){
        printf("Impossível abrir o arquivo de clientes.");
        exit(1);
    }

    arvoreCliente = newTree();

    pessoa = clnt_cria();
    fread( pessoa, sizeof(Cliente), 1, arquivo );
    while( !feof(arquivo) ){
        if( pessoa->status != -1 ){
            addClienteNome(arvoreCliente, pessoa);
            pessoa = clnt_cria();
        }
        fread( pessoa, sizeof(Cliente), 1, arquivo );
    }

    fclose(arquivo);
    return arvoreCliente;
}


Tree* clnt_recupera_arvoreCPF( void ){
    FILE* arquivo;
    Cliente* pessoa;
    Tree* arvoreCliente;

    arquivo = fopen("cliente/Cliente.dat", "rb");
    if( arquivo == NULL ){
        printf("Impossível abrir o arquivo de clientes.");
        exit(1);
    }

    arvoreCliente = newTree();

    pessoa = clnt_cria();
    fread( pessoa, sizeof(Cliente), 1, arquivo );
    while( !feof(arquivo) ){
        if( pessoa->status != -1 ){
            addClienteCPF(arvoreCliente, pessoa);
            pessoa = clnt_cria();
        }
        fread( pessoa, sizeof(Cliente), 1, arquivo );
    }

    fclose(arquivo);
    return arvoreCliente;
}


char* clnt_insereNC( int modo ){
    char* entrada;

    if( modo == INSERECPF ){
        entrada = entr_str("Digite o CPF do cliente: ");
        while( !val_cpf( entrada ) ){
            free(entrada);
            printf("CPF inválido.\n");
            entrada = entr_str("Digite o CPF do cliente: ");
        }

        entrada = form_cpf(entrada);

    } else if( modo == INSERENOME ) {
        entrada = entr_str("Digite o nome do cliente: ");
        while( !val_nome( entrada ) ){
            free(entrada);
            printf("Nome inválido.\n");
            entrada = entr_str("Digite o nome do cliente: ");
        }

    } else if( modo == INSEREDOIS ){
        entrada = entr_str("Digite o nome ou o CPF do cliente: ");
        while( !val_nome( entrada ) && !val_cpf( entrada ) ){
            free(entrada);
            printf("Nome ou CPF inválido.\n");
            entrada = entr_str("Digite o nome ou o CPF do cliente: ");
        }

        if( val_cpf(entrada) )
            entrada = form_cpf(entrada);

    } else if( modo == INSEREDATANASC ){
        entrada = entr_str("Digite a data de nascimento: ");
        while( !val_data( entrada ) || !val_idade( entrada ) ){
            free(entrada);
            printf("Data inválida\n");
            entrada = entr_str("Digite a data de nascimento: ");
        }

        entrada = form_data( entrada );

    } else if( modo == INSEREENDERECO ){
        entrada = entr_str("Digite o endereço: ");
        while( !val_endereco( entrada ) ){
            free(entrada);
            printf("Endereço inválido\n");
            entrada = entr_str("Digite o endereço: ");
        }
    }

    return entrada;
}

void clnt_edita_dados( void ){
    Cliente* busca;
    char* entrada;

    printf("- - - - - EDITAR CLIENTE - - - - -\n");

    while(busca == NULL){
        entrada = clnt_insereNC( INSERECPF );
        busca = clnt_recupera_cpf( entrada );
        if( busca == NULL )
            printf("Cliente não encontrado\n");

        free(entrada);
    }

    printf("Nº %d - - - - - - - - - - - - - - - -\n", busca->status);
    clnt_mostra( busca );
    printf("- - - - - - - - - - - - - - - - - - -\n\n");

    printf("1 - Editar Nome\n");
    printf("2 - Editar Data de Nascimento\n");
    printf("3 - Editar Endereço\n");
    printf("0 - voltar\n");

    switch ( menu_escolha(3) )
    {
    case 1:
        entrada = clnt_insereNC( INSERENOME );
        if( clnt_edita( busca, NOME, entrada ) )
            printf("Cliente editado com sucesso!\n");
        else {
            printf("Ocorreu um erro.\n Cliente não editado.\n");
        }
        free(entrada);
        break;

    case 2:
        entrada = clnt_insereNC( INSEREDATANASC );
        if( clnt_edita( busca, DATNASC, entrada ) )
            printf("Cliente editado com sucesso!\n");
        else {
            printf("Ocorreu um erro.\n Cliente não editado.\n");
        }
        free(entrada);
        break;

    case 3:
        entrada = clnt_insereNC( INSEREENDERECO );
        if( clnt_edita( busca, ENDERECO, entrada ) )
            printf("Cliente editado com sucesso!\n");
        else {
            printf("Ocorreu um erro.\n Cliente não editado.\n");
        }
        free(entrada);
        break;

    default:
        break;
    }
}


void clnt_deleta( void ){
    FILE* arquivo;
    Cliente *pessoa, *pessoaR;
    char* resposta;
    short int achou = 0;

    pessoa = clnt_recupera_cpf( clnt_insereNC( INSERECPF ) );
    pessoaR = clnt_cria();


    if( pessoa != NULL && pessoa->status != DEVENDO ){
        arquivo = fopen("cliente/Cliente.dat", "r+b");
        if( arquivo == NULL ){
            printf("Erro ao deletar o cliente\n");
            exit(1);
        }

        while( !achou && fread( pessoaR, sizeof(Cliente), 1, arquivo ) ){
            if( !clnt_compara(pessoaR, pessoa) && pessoa->status != -1 ){
                achou = 1;
                fseek(arquivo, (-1)*sizeof(Cliente), SEEK_CUR);
            }
        }

        if( achou ){    
            printf("Nº %d - - - - - - - - - - - - - - - -\n", pessoa->num);
            clnt_mostra(pessoa);
            printf("- - - - - - - - - - - - - - - - - - -\n");

            resposta = entr_str("Deseja realmente apagar este cliente? ");
            while( !val_SN(resposta) ){
                free(resposta);
                printf("Digite apenas sim ou não");
                resposta = entr_str("Deseja realmente apagar este cliente? ");
            }
            if( get_resposta(resposta) ){
                pessoa->status = -1;
                fwrite(pessoa, sizeof(Cliente), 1, arquivo);
                fclose(arquivo);

                printf("Cliente deletado com sucesso!\n");
            } else {
                printf("O cliente não foi deletado.\n");
            }
        } else {
            printf("Ocorreu um erro ao salvar.\n");
        }
    } else if( pessoa->status == DEVENDO ) {
        printf("O cliente não pode ser deletado, pois o mesmo está em débito\n");
    } else {
        printf("Cliente não encontrado.\n");
    }
    voltar();
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
    destino->carrosAlugados = origem->carrosAlugados;
    destino->num = origem->num;
    destino->status = origem->status;
    
}


Cliente* clnt_recupera_nome( char* nome ){
    Tree* listaCliente;
    Cliente* pessoa, *busca;

    listaCliente = clnt_recupera_arvoreNome();

    busca = searchClienteNome(listaCliente, nome);
    if( busca != NULL ){
        pessoa = clnt_cria();
        clnt_copia( pessoa, busca );
    } else {
        pessoa = NULL;
    }

    freeTreeCliente(listaCliente);

    return pessoa;
}


Cliente* clnt_recupera_cpf( char* cpf ){
    Tree* listaCliente;
    Cliente* pessoa, *busca;


    cpf = form_cpf( cpf );

    listaCliente = clnt_recupera_arvoreCPF();
    
    busca = searchClienteCPF(listaCliente, cpf);
    if( busca != NULL ){
        pessoa = clnt_cria();
        clnt_copia(pessoa, busca);
    } else {
        pessoa = NULL;
    }


    freeTreeCliente(listaCliente);

    return pessoa;
}


void clnt_mostra_todos( void ){
    Tree* listaCliente;
    // Array* listaCliente;
    Cliente *busca;

    listaCliente = clnt_recupera_arvoreNome();
    //listaCliente = clnt_recupera_lista();

    /*
    for( int i = 0; i < size(listaCliente); i++ ){
        busca = (Cliente*) pos(listaCliente, i);
        if( !busca->status ){
            printf("\nNº %d - - - - - - - - - - - - - - - -\n", busca->num);
            clnt_mostra( busca );
            printf("\n- - - - - - - - - - - - - - - - - - -\n");
        }
    }
    */

    mostraCliente( listaCliente );

    freeTreeCliente(listaCliente);

    // liberaLista( listaCliente );
}


void clnt_re_dados( void ){
    char* entrada;
    Cliente* pessoa;

    imp_clnt_visualizarDados();

    entrada = clnt_insereNC( INSEREDOIS );


    if( val_nome( entrada ) ){
        pessoa  = clnt_recupera_nome( entrada );
    } else if ( val_cpf( entrada ) ){
        pessoa = clnt_recupera_cpf( entrada );
    }

    if( pessoa != NULL ){
        clnt_mostra( pessoa );
        clnt_libera( pessoa );
        voltar();
    } else {
        printf("Cliente não encontrado!\n");
        voltar();
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
    while( !( val_km( endereco ) ) ){
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


void clnt_mostra_carrosAlugados( Cliente* pessoa ){
    printf("\nNº de carros alugados: %d\n", pessoa->carrosAlugados);
}


void clnt_mostra_status( Cliente* pessoa ){
    if( pessoa->status == LIVRE ){
        printf("Status: Livre\n");
    } else if( pessoa->status == DEVENDO ){
        printf("Status: Devendo\n");
    }
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
    clnt_mostra_carrosAlugados( pessoa );
    clnt_mostra_status( pessoa );
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
