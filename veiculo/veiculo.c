#include "veiculo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "../aluguel/aluguel.h"
#include "../cliente/cliente.h"
#include "../lista/lista.h"
#include "../usuario/usuario.h"
#include "../mylib.h"
#include "../validacoes/validacoes.h"
#include "../menu/menu.h"


typedef struct veiculo {
    float preco;
    float kmRod;
    int totalDeAlugueis;
    int status;
    int codigo;
    char marca[15];
    char modelo[51];
    char ano[5];
    char placa[9];
    char cor[20];
} Veiculo;


int veic_compara( Veiculo* veiculo1, Veiculo* veiculo2 ){
    if( !strcmp(veiculo1->placa, veiculo2->placa) ){
        if( !strcmp(veiculo1->marca, veiculo2->marca) ){
            if( !strcmp(veiculo1->modelo, veiculo2->modelo) ){
                return 0;
            }
        }
    }

    return 1;
}


int veic_codigo( Veiculo* automovel ){
    return automovel->codigo;
}


float veic_preco( Veiculo* automovel ){
    return (float) automovel->preco;
}


int veic_status( Veiculo* automovel ){
    return automovel->status;
}


int veic_edita( Veiculo* veiculo, int campo, void* alteracao ){
    FILE* arquivo;
    Veiculo* busca;
    short int achou = 0;

    if( campo == VEIC_STATUS ){
        veiculo->status = *((int*) alteracao);
    } else if( campo == TOTALDEALUGUEIS ){
        veiculo->totalDeAlugueis = *((int*) alteracao);
    }

    arquivo = fopen( "veiculo/Veiculo.dat", "r+b" );

    if( arquivo == NULL ){
        printf("Não foi possível salvar as informações\n");
        exit(0);
    }
    

    busca = veic_cria();
    while( !achou && fread( busca, sizeof(Veiculo), 1, arquivo ) ){
        if( !strcmp(busca->placa, veiculo->placa) ){
            achou = 1;
            fseek( arquivo, sizeof(Veiculo)*(-1), SEEK_CUR );
        }
    }

    if( achou ){
        fwrite(veiculo, sizeof(Veiculo), 1, arquivo);
    } else {
        printf("Ocorreu um erro ao salvar as alterações\n");
        exit(1);
    }

    fclose(arquivo);

    return !achou;
}


Array* veic_recupera( void ){
    FILE* arquivo;
    Veiculo* veiculo;
    Array* listaVeiculo;

    arquivo = fopen("veiculo/Veiculo.dat", "rb");
    if(arquivo == NULL){
        arquivo = fopen("veiculo/Veiculo.dat", "wb");
        if( arquivo == NULL ){
            printf("Impossível abrir o arquivo de veículos.\n");
            exit(1);
        }
    }

    listaVeiculo = arrayCria();

    fseek(arquivo, 0, SEEK_END);
    if( ftell(arquivo) < sizeof(Veiculo) ){
        printf("Não há veículos cadastrados.\n");
    }else {
        fseek(arquivo, 0, SEEK_SET);

        veiculo = veic_cria();
        fread( veiculo, sizeof(Veiculo), 1, arquivo );
        while( !feof(arquivo) ){
            append(listaVeiculo, veiculo);
            veiculo = veic_cria();
            fread( veiculo, sizeof(Veiculo), 1, arquivo );
        }
    }

    fclose(arquivo);
    return listaVeiculo;
}


Veiculo* veic_copia( Veiculo* veiculo1){
    Veiculo* veiculo2 = veic_cria();

    veiculo2->preco = veiculo1->preco;
    veiculo2->totalDeAlugueis = veiculo1->totalDeAlugueis;
    veiculo2->status = veiculo1->status;
    veiculo2->codigo = veiculo1->codigo;
    veiculo2->kmRod = veiculo1->kmRod;
    strcpy(veiculo2->marca, veiculo1->marca);
    strcpy(veiculo2->modelo, veiculo1->modelo);
    strcpy(veiculo2->ano, veiculo1->ano);
    strcpy(veiculo2->placa, veiculo1->placa);
    strcpy(veiculo2->cor, veiculo1->cor);

    return veiculo2;
}


Veiculo* veic_recupera_placa( void ){
    char* placa;
    Array* listaVeiculo;
    Veiculo* veiculo, *retorno;

    placa = entr_str("Digite a placa do veículo: ");
    while( !val_placa( placa ) ){
        printf("Placa inválida.\n");
        placa = entr_str("Digite a placa do veículo: ");
    }

    listaVeiculo = veic_recupera();

    for( int i=0; i < size(listaVeiculo); i++ ){
        veiculo = (Veiculo*) pos(listaVeiculo, i);
        if( !str_cmp(veiculo->placa, placa) ){
            retorno = veic_copia(veiculo);
            liberaLista(listaVeiculo);
            return retorno;
        }
    }
    
    liberaLista(listaVeiculo);
    return NULL;
}


Veiculo* veic_recupera_codigo( int codigo ){
    Array* listaVeiculo;
    Veiculo* veiculo, *retorno;

    listaVeiculo = veic_recupera();

    for( int i=0; i < size(listaVeiculo); i++ ){
        veiculo = (Veiculo*) pos(listaVeiculo, i);
        if( veiculo->codigo == codigo ){
            retorno = veic_copia(veiculo);
            liberaLista(listaVeiculo);
            return retorno;
        }
    }
    
    liberaLista(listaVeiculo);
    return NULL;
}


void imp_veic_visualizarDados( void ){
    printf("\n- - - - - VISUALIZAR DADOS DO VEÍCULO - - - - -\n");
    printf("1 - Procurar por placa\n");
    printf("0 - sair\n");
}


void veic_re_dados( void ){
    char* nome;
    Veiculo* veiculo;

    imp_veic_visualizarDados();

    switch ( menu_escolha(2) )
    {
    case 1:
        veiculo  = veic_recupera_placa();
        break;

    case 0:
        return;

    default:
        printf("Não foi possível abrir o menu\n");
        break;
    }

    if( veiculo != NULL ){
        veic_mostra( veiculo );
        veic_libera( veiculo );
        voltar();
    } else {
        printf("Veiculo não encontrado!\n");
        sleep(2);
    }
}


int veic_salva( Veiculo* veiculo ){
    FILE *arquivo;
    Veiculo* save = veic_cria();
    int result;

    veiculo->status = 0;

    arquivo = fopen( "veiculo/Veiculo.dat", "a+b" );

    if( arquivo == NULL ){
        arquivo = fopen( "veiculo/Veiculo.dat", "w+b" );
    }
    
    fseek(arquivo, 0, SEEK_END);
    if( ftell(arquivo) == 0 ){
        veiculo->codigo = 1;
    } else {
        fseek(arquivo, (sizeof(Veiculo))*(-1), SEEK_CUR);
        fread(save, sizeof(Veiculo), 1, arquivo);
        veiculo->codigo = save->codigo+1;
        fseek(arquivo, 0, SEEK_SET);
    }


    result = fwrite( veiculo, sizeof( Veiculo ), 1, arquivo);
    if( result == EOF ){
        return 0;
    }

    fclose(arquivo);

    return 1;
}


void veic_deleta( void ){
    FILE* arquivo;
    Veiculo *veiculo, *veiculoR;
    char* resposta;
    short int achou = 0;

    veiculo = veic_recupera_placa();
    veiculoR = veic_cria();


    if( veiculo != NULL ){
        arquivo = fopen("veiculo/Veiculo.dat", "r+b");
        if( arquivo == NULL ){
            printf("Erro ao deletar o veículo\n");
            exit(1);
        }

        while( !achou && fread( veiculoR, sizeof(Veiculo), 1, arquivo ) ){
            if( !veic_compara(veiculoR, veiculo) && veiculo->status != -1 ){
                achou = 1;
                fseek(arquivo, (-1)*sizeof(Veiculo), SEEK_CUR);
            }
        }

        if( achou ){
            printf("Nº %d - - - - - - - - - - - - - - - -\n", veiculo->codigo);
            veic_mostra(veiculo);
            printf("- - - - - - - - - - - - - - - - - - -\n");

            resposta = entr_str("Deseja realmente apagar este veículo? ");
            while( !val_SN(resposta) ){
                free(resposta);
                printf("Digite apenas sim ou não");
                resposta = entr_str("Deseja realmente apagar este veículo? ");
            }

            if( get_resposta(resposta) ){
                veiculo->status = -1;
                fwrite(veiculo, sizeof(Veiculo), 1, arquivo);
                fclose(arquivo);

                printf("Veiculo deletado com sucesso!\n");
                voltar();
            } else {
                printf("O veículo não foi deletado.\n");
                voltar();
            }
        } else {
            printf("Ocorreu um erro ao salvar.\n");
            voltar();
        }
    } else {
        printf("Veiculo não encontrado.\n");
        voltar();
    }
}


void veic_mostra_todos( void ){
    Array* listaVeiculo;
    Veiculo *busca;

    listaVeiculo = veic_recupera();

    for( int i = 0; i < size(listaVeiculo); i++ ){
        busca = (Veiculo*) pos(listaVeiculo, i);
            printf("\nNº %d - - - - - - - - - - - - - - - -\n", busca->codigo);
            veic_mostra( busca );
            printf("\n- - - - - - - - - - - - - - - - - - -\n");
    }

    liberaLista( listaVeiculo );
}


void veic_ins_preco( Veiculo* automovel ){
    char* resultado;
    float preco;
    
    resultado = entr_str( "Insira o preço do veículo: " );
    while( !( val_preco( resultado ) ) ){
        printf("O preço inserido é inválido.\n");
        resultado = entr_str( "Insira o preço do veículo: " );
    }

    preco = form_preco( resultado );

    automovel->preco = preco;
    free(resultado);
}


void veic_ins_marca( Veiculo* automovel ){
    char* resultado;
    
    resultado = entr_str( "Insira a marca do veículo: " );
    while( !( val_marca( resultado ) ) ){
        printf("Marca inserida é inválida.\n");
        resultado = entr_str( "Insira a marca do veículo: " );
    }

    strcpy( automovel->marca, resultado );
    free(resultado);
}


void veic_ins_modelo( Veiculo* automovel ){
    char* resultado;

    resultado = entr_str( "Insira o modelo do veículo: " );

    strcpy( automovel->modelo, resultado );
    free(resultado);
}


void veic_ins_ano( Veiculo* automovel ){
    char* resultado;

    resultado = entr_str( "Insira o ano do veículo: " );
    while( !( val_ano( resultado ) ) ){
        printf("Ano inserido inválido\n");
        resultado = entr_str( "Insira o ano do veículo: " );
    }

    strcpy( automovel->ano, resultado );
    free(resultado);
}


void veic_ins_placa( Veiculo* automovel ){
    char* resultado;
    
    resultado = entr_str( "Insira a placa do veículo: " );
    while( !( val_placa( resultado ) ) ){
        printf("A placa inserida é inválida.\n");
        resultado = entr_str( "Insira a placa do veículo: " );
    }

    strcpy( automovel->placa, resultado );
    free(resultado);
}


void veic_ins_km( Veiculo* automovel ){
    char* resultado;

    resultado = entr_str("Insira a quilometragem do veículo: ");
    while( !( val_km(resultado) ) ){
        printf("Digite apenas a quilometragem em inteiro.\n");
        resultado = entr_str("Insira a quilometragem do veículo: ");
    }

    automovel->kmRod = form_preco(resultado);

    free(resultado);
}


void veic_ins_cor( Veiculo* automovel ){
    char* resultado;

    resultado = entr_str("Insira a cor do veículo: ");
    while( !( val_nome(resultado) ) ){
        printf("Digite uma cor pelo nome.\n");
        resultado = entr_str("Insira a cor do veículo: ");
    }

    strcpy( automovel->cor, resultado );
    free(resultado);
}


void veic_mostra_preco( Veiculo* automovel ){
    printf("\nPreço(p/ dia): R$%.2f\n", automovel->preco);
}


void veic_mostra_marca( Veiculo* automovel ){
    printf("\nMarca do veículo: %s\n", automovel->marca);
}


void veic_mostra_modelo( Veiculo* automovel ){
    printf("\nModelo do veículo: %s\n", automovel->modelo);
}


void veic_mostra_ano( Veiculo* automovel ){
    printf("\nAno: %s\n", automovel->ano);
}


void veic_mostra_placa( Veiculo* automovel ){
    printf("\nPlaca do veículo: %s\n", automovel->placa);
}


void veic_mostra_km( Veiculo* automovel ){
    printf("\n%.2fkm rodados\n", automovel->kmRod);
}

void veic_mostra_cor( Veiculo* automovel ){
    printf("\nCor do veículo: %s\n", automovel->cor);
}


void veic_libera( Veiculo* automovel ){
    free( automovel );
}


Veiculo* veic_cria( void ){
    Veiculo* novo_veiculo = ( Veiculo* ) malloc ( sizeof( Veiculo ) );

    return novo_veiculo;
}


int veic_existe( Veiculo* veiculo ){
    FILE* arquivo;
    Veiculo* busca = veic_cria();

    arquivo = fopen("veiculo/Veiculo.dat", "rb");
    if(arquivo != NULL ){
        fread( busca, sizeof(Veiculo), 1, arquivo );
        while( !feof(arquivo) ){
            if( !busca->status && !veic_compara(veiculo, busca) ){
                veic_libera(busca);
                fclose(arquivo);
                return 1;
            }
            fread( busca, sizeof(Veiculo), 1, arquivo );
        }
        fclose(arquivo);
    }

    veic_libera(busca);

    return 0;
}


void veic_mostra( Veiculo* automovel ){
    veic_mostra_marca( automovel );
    veic_mostra_modelo( automovel );
    veic_mostra_ano( automovel );
    veic_mostra_placa( automovel );
    veic_mostra_cor( automovel );
    veic_mostra_km( automovel );
    veic_mostra_preco( automovel );

    printf("\nStatus do veículo: ");
    if( automovel->status == 0 ){
        printf("Disponível\n");
    } else {
        printf("Alugado\n");
    }
}


void veic_cad( void ) {
    char* resposta;

    Veiculo* novo = veic_cria();
    veic_ins_marca( novo );
    veic_ins_modelo( novo );
    veic_ins_ano( novo );
    veic_ins_placa( novo );
    veic_ins_cor( novo );
    veic_ins_km( novo );
    veic_ins_preco( novo );

    novo->status = 0;

    if( veic_existe( novo ) ){
        printf("Este veículo já está cadastrado no sistema.\n");
    }

    else {
        veic_mostra( novo );
        resposta = entr_str("Deseja salvar os dados? ");
        while( !val_SN(resposta) ){
            printf("Digite apenas sim ou não.\n");
            resposta = entr_str("\nDeseja salvar os dados? ");
        }

        if( tolower(resposta[0]) == 's' ){
            if( !(veic_salva(novo)) ){
                printf("\nNão foi possível salvar os dados do veículo.\n");
            }
            else {
                printf("\nVeículo cadastrado com sucesso!\n");
            }
        } else {
            resposta = entr_str("Deseja realmente descartar os dados? ");
            while( !val_SN(resposta) ){
                printf("Digite apenas sim ou não.\n");
                resposta = entr_str("\nDeseja realmente descartar os dados? ");
            }
            if( tolower(resposta[0]) == 'n' ){
                if( !(veic_salva(novo)) ){
                    printf("\nNão foi possível salvar os dados do veículo.\n");
                }
                else {
                    printf("\nVeículo cadastrado com sucesso!\n");
                }
            }
        }
    }

    veic_libera( novo );
}
