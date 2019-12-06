#include "../cliente/cliente.h"
#include "../veiculo/veiculo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "aluguel.h"
#include "../lista/lista.h"
#include "../usuario/usuario.h"
#include "../mylib.h"
#include "../validacoes/validacoes.h"
#include "../menu.h"

struct aluguel{
    float preco;
    int status;
    int codCliente;
    int codAutomovel;
    int dias;
    char dia_aluguel[31];
    char dia_devolucao[31];
    struct tm data;
};


Aluguel* preencheAluguel( int dias, float preco ){
    Aluguel* aluguel;

    aluguel = (Aluguel*) malloc(sizeof(Aluguel));

    struct tm* horario;
    time_t hora;
    char* strtime;

    time(&hora);
    horario = localtime(&hora);

    strftime(aluguel->dia_aluguel, 80, "%d de %B, %a %R", horario);

    aluguel->preco = preco;

    horario->tm_mday += dias;
    mktime(horario);

    strftime(aluguel->dia_devolucao, 80, "%d de %B, %a %R", horario);

    aluguel->data = *horario;

    return aluguel;
}


Aluguel* aluguel_cria( void ){
    return (Aluguel*) malloc(sizeof(Aluguel));
}


void printRelatorio( Aluguel* aluguel ){
    printf("Preço: R$%.2f\nData do Aluguel: %s\nData de devolução: %s\n\nCódigo do carro: %d\nCódigo do Cliente: %d\nMulta de 5%% a cada dia atraso\n\n", aluguel->preco, aluguel->dia_aluguel, aluguel->dia_devolucao, aluguel->codAutomovel, aluguel->codCliente);
}


int salvaRelatorio( Aluguel* aluguel ){
    int salvar = 0;
    char* decisao;
    FILE* arquivo;

    decisao = entr_str("Concluir o aluguel? ");
    while( !val_SN(decisao) ){
        printf("\nDigite apenas (S)im ou (N)ão!\n");
        free(decisao);
        decisao = entr_str("Concluir o aluguel? ");
    }

    if( get_resposta( decisao ) ){
        salvar = 1;
    } else {
        free(decisao);
        decisao = entr_str("Deseja cancelar a operação? ");
        if( get_resposta( decisao ) ){
            printf("Operação cancelada com sucesso.\n");
        } else {
            salvar = 1;
        }
    }

    if( salvar ){
        arquivo = fopen("aluguel/aluguel.dat", "ab");
        if( arquivo == NULL ){
            arquivo = fopen("aluguel/aluguel.dat", "wb");
            if( arquivo == NULL ){
                printf("Não foi possível abrir o arquivo.\n\nAbortando...\n\n");
                exit(1);
            }
        }

        fseek(arquivo, 0, SEEK_END);
        salvar = fwrite( aluguel, sizeof(Aluguel), 1, arquivo );
        if( salvar == EOF ){
            printf("Não foi possível salvar o relatório\n");
            exit(1);
        }
        printf("Aluguel efetuado com sucesso!\n");
        fclose(arquivo);
        return 1;
    } else {
        return 0;
    }
}


int difDias( struct tm* anterior, struct tm* atual ){
    time_t ant, now;
    float diferenca;

    ant = mktime(anterior);
    now = mktime(atual);

    diferenca = difftime(ant, now);

    if( diferenca > 86400 ){
        diferenca = diferenca/60;
        diferenca = diferenca/60;
        diferenca = diferenca/24;
        return (int) diferenca;
    } else if( diferenca*(-1) > 86400 ){
        diferenca = diferenca/60;
        diferenca = diferenca/60;
        diferenca = diferenca/24;
        return (int) diferenca*(-1);
    }else {
        return 0;
    }
}


float calculaPreco( struct tm* anterior, struct tm* atual ){

}


void alugarVeiculo( void ){
    Cliente* cliente;
    Veiculo* automovel;
    char* dias, *entrada;
    float resultado;
    int intDias, alteracao;
    Aluguel *novo;

    entrada = clnt_insereNC( INSERECPF );
    cliente = clnt_recupera_cpf( entrada );
    while( cliente == NULL ){
        printf("Cliente não cadastrado.\n");
        free(entrada);
        entrada = clnt_insereNC( INSERECPF );
        cliente = clnt_recupera_cpf( entrada );
    }

    do{
        automovel = veic_recupera_placa();
        while( automovel == NULL ){
            printf("Veículo não encontrado!\n");
            automovel = veic_recupera_placa();
        }
        if( veic_status( automovel ) != 0 ){
            printf("Veículo não disponível\n");
        }
    }while( veic_status(automovel) != 0 );

    printf("\nCódigo Nº %d - - - - - - - - - - - - \n", veic_codigo(automovel));
    veic_mostra(automovel);
    printf("\n- - - - - - - - - - - - - - - - - - -\n\n");

    dias = entr_str("Por quantos dias deseja ficar com o veículo? ");
    while( !val_dias(dias) ){
        printf("Só é possível alugar um automóvel entre 1 e 90 dias\n");
        free(dias);
        dias = entr_str("Por quanto tempo deseja ficar com o veículo? ");
    }

    if( strlen(dias) == 1 ){
        intDias = (dias[0] - '0');
    } else {
        intDias = ((dias[0] - '0')*10 + (dias[1] - '0'));
    }

    resultado = intDias * veic_preco(automovel);

    novo = preencheAluguel( intDias, resultado);

    novo->codAutomovel = veic_codigo( automovel );
    novo->codCliente = clnt_num( cliente );
    novo->dias = intDias;
    novo->status = 0;

    printRelatorio( novo );

    free(dias);
    if( salvaRelatorio(novo) ){
        alteracao = clnt_carrosAlugados(cliente)+1;
        clnt_edita( cliente, CARROS_ALUGADOS, &alteracao );
        alteracao = DEVENDO;
        clnt_edita( cliente, STATUS, &alteracao );
        alteracao = -1;
        veic_edita( automovel, VEIC_STATUS, &alteracao );
    }
}


Array* recuperaAlugueis( void ){
    FILE* arquivo;
    Aluguel* aluguel;
    Array* listaAlugueis;

    arquivo = fopen("aluguel/aluguel.dat", "rb");
    if(arquivo == NULL){
        arquivo = fopen("aluguel/bluguel.dat", "wb");
        if( arquivo == NULL ){
            printf("Impossível abrir o arquivo de aluguéis.\n");
            exit(1);
        }
    }

    listaAlugueis = arrayCria();

    fseek(arquivo, 0, SEEK_END);
    if( ftell(arquivo) < sizeof(Aluguel) ){
        printf("Não há alugueis efetuados.\n");
        listaAlugueis = NULL;
    } else {
        fseek(arquivo, 0, SEEK_SET);

        aluguel = aluguel_cria();
        while( fread( aluguel, sizeof(Aluguel), 1, arquivo ) ){
            if( aluguel->status == 0 ){
                append(listaAlugueis, aluguel);
                aluguel = aluguel_cria();
            }
        }
    }

    fclose(arquivo);
    return listaAlugueis;
}


void aluguelDevolve( Aluguel* aluguel ){
    FILE* arquivo;
    Aluguel* busca;
    short int achou = 0;

    arquivo = fopen( "aluguel/aluguel.dat", "r+b" );

    if( arquivo == NULL ){
        printf("Não foi possível salvar as informações\n");
        exit(0);
    }

    busca = aluguel_cria();
    while( !achou && fread( busca, sizeof(Aluguel), 1, arquivo ) ){
        if( aluguel->codAutomovel == busca->codAutomovel && aluguel->codCliente == busca->codCliente ){
            printf("Achou\n");
            achou = 1;
            fseek( arquivo, sizeof(Aluguel)*(-1), SEEK_CUR );
        }
    }

    if( achou ){
        aluguel->status = 1;
        fwrite(aluguel, sizeof(Aluguel), 1, arquivo);
    } else {
        printf("Ocorreu um erro ao salvar as alterações\n");
        exit(1);
    }

    fclose(arquivo);
}


void devolverVeiculo( void ){
    time_t aux;
    Cliente* pessoa = NULL;
    Veiculo* veiculo = NULL;
    Aluguel* aluguel = NULL;
    int codCLiente, codVeiculo, dias, alteracao;
    float preco;
    struct tm* dataAtual;
    Array* listaAlugueis, *automoveis;
    char* entrada;

    pessoa = clnt_recupera_cpf( clnt_insereNC( INSERECPF ) );
    if( pessoa != NULL && clnt_status( pessoa ) != LIVRE ){
        printf("\nNº %d - - - - - - - - - - - - - - - -\n", clnt_num(pessoa));
        clnt_mostra(pessoa);
        printf("- - - - - - - - - - - - - - - - - - -\n");
        codCLiente = clnt_num(pessoa);


        if( clnt_carrosAlugados(pessoa) > 0 ){
            printf("\n___CARROS ALUGADOS PELO CLIENTE___\n");
        }

        listaAlugueis = recuperaAlugueis();
        automoveis = arrayCria();

        if( listaAlugueis != NULL && size(listaAlugueis) > 0 ){
            for( int i = 0; i < size(listaAlugueis); i++ ){
                aluguel = (Aluguel*) pos(listaAlugueis, i);
                if( aluguel->codCliente == codCLiente ){
                    printf("\n%d  - - - - - - - - - - - - - - -\n", i+1);
                    printRelatorio( aluguel );
                    printf("- - - - - - - - - - - - - - - - -\n");
                    appendInt(automoveis, aluguel->codAutomovel);
                }
            }

            liberaLista(listaAlugueis);

            do{
                entrada = entr_str("Digite o código do carro que deseja devolver: ");
                while( !val_km(entrada) ){
                    printf("Digite um código válido.\n");
                    free(entrada);
                    entrada = entr_str("Digite o código do carro que deseja devolver: ");
                }
                codVeiculo = form_preco(entrada);
                free(entrada);
            } while( !intIn(automoveis, codVeiculo) );

            time(&aux);
            dataAtual = localtime(&aux);
            
            veiculo = veic_recupera_codigo( codVeiculo );

            veic_mostra(veiculo);

            dias = difDias(&aluguel->data, dataAtual);
            if( dias > 0 && dias - aluguel->dias > 0 ){
                preco = veic_preco( veiculo )*dias;
                preco += preco*0.05;
            } else if( aluguel->dias + dias > 0){
                preco = dias*veic_preco( veiculo );
            } else {
                preco = aluguel->preco;
            }

            printf("O preço atual será de R$%.2f\n", preco);
            entrada = entr_str("Deseja efetuar o pagamento?");
            while( !val_SN ){
                printf("Digite apenas (S)im ou (N)ão!\n");
                free(entrada);
                entrada = entr_str("Deseja efetuar o pagamento? \n");
            }

            if( get_resposta(entrada) ){
                alteracao = clnt_carrosAlugados(pessoa)-1;
                clnt_edita( pessoa, CARROS_ALUGADOS, &alteracao );
                if( alteracao == 0 ){
                    alteracao = LIVRE;
                    clnt_edita( pessoa, STATUS, &alteracao );
                }
                alteracao = 0;
                veic_edita( veiculo, VEIC_STATUS, &alteracao );

                aluguelDevolve(aluguel);

                printf("Devolução realizada com sucesso\n");
            } else {
                printf("A devolução não foi finalizada.\n");
            }
        }

        if( automoveis != NULL )
            liberaLista(automoveis);
        if( pessoa != NULL )
            clnt_libera(pessoa);
        if( veiculo != NULL )
            veic_libera(veiculo);
    } else {
        if( listaAlugueis != NULL ){
            liberaLista(listaAlugueis);
        }

        printf("Não há alugueis cadastrados neste CPF\n");
    }
}