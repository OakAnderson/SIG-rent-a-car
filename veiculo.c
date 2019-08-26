#ifndef BIBLIOTECAS
    #define BIBLIOTECAS
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    #include <time.h>
    #include <unistd.h>
    #include "cliente.h"
    #include "mylib.h"
    #include "validacoes.h"
    #include "menu.h"
    #include "veiculo.h"
#endif


typedef struct veiculo {
    char marca[15];
    char modelo[51];
    char ano[5];
    char renavam[12];
    char placa[9];
    char cor[5];
    char kmRod[10];
} Veiculo;


void veic_ins_marca( Veiculo* automovel ){
    char* resultado;
    
    resultado = entr_str( "Insira a marca do veículo: " );
    while( !( val_marca( resultado ) ) ){
        printf("Marca inserida é inválida.\n");
        resultado = entr_str( "Insira a marca do veículo: " );
    }

    strcpy( automovel->marca, resultado );
}


void veic_ins_modelo( Veiculo* automovel ){
    char* resultado;

    resultado = entr_str( "Insira o modelo do veículo: " );

    strcpy( automovel->modelo, resultado );
}


void veic_ins_ano( Veiculo* automovel ){
    char* resultado;

    resultado = entr_str( "Insira o ano do veículo: " );
    while( !( val_ano( resultado ) ) ){
        printf("Ano inserido inválido\n");
        resultado = entr_str( "Insira o ano do veículo: " );
    }

    strcpy( automovel->ano, resultado );
}


void veic_ins_renavam( Veiculo* automovel ){
    char* resultado;

    resultado = entr_str( "Insira o renavam do veículo: " );
    while( !( val_renavam( resultado ) ) ){
        printf("O renavam inserido é inválido.\n");
        resultado = entr_str( "Insira o renavam do veículo: " );
    }

    strcpy( automovel->renavam, resultado );
}


void veic_ins_placa( Veiculo* automovel ){
    char* resultado;
    
    resultado = entr_str( "Insira a placa do veículo: " );
    while( !( val_placa( resultado ) ) ){
        printf("A placa inserida é inválida.\n");
        resultado = entr_str( "Insira a placa do veículo: " );
    }

    strcpy( automovel->placa, resultado );
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


void veic_mostra_renavam( Veiculo* automovel ){
    printf("\nRenavam do veículo: %s\n", automovel->renavam);
}


void veic_mostra_placa( Veiculo* automovel ){
    printf("\nPlaca do veículo: %s\n", automovel->placa);
}


void veic_libera( Veiculo* automovel ){
    free( automovel );
}


Veiculo* veic_cria( void ){
    Veiculo* novo_veiculo = ( Veiculo* ) malloc ( sizeof( Veiculo ) );

    return novo_veiculo;
}


void veic_mostra( Veiculo* automovel ){
    veic_mostra_marca( automovel );
    veic_mostra_modelo( automovel );
    veic_mostra_ano( automovel );
    veic_mostra_renavam( automovel );
    veic_mostra_placa( automovel );
}


void veic_cad( void ) {
    Veiculo* novo = veic_cria();
    veic_ins_marca( novo );
    veic_ins_modelo( novo );
    veic_ins_ano( novo );
    veic_ins_renavam( novo );
    veic_ins_placa( novo );

    veic_mostra( novo );

    veic_libera( novo );
}
