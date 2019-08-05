#include <stdio.h>
#include "validacoes.c"

int main (void){
    int bool = 0;
    char palavra1[4] = "nao", palavra2[4] = "nao";

    bool = val_resposta( "Continuar?" );
    printf( "bool = %d\n", bool );

    return 0;
}