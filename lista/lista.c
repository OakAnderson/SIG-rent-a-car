#include "../cliente/cliente.h"
#include "../veiculo/veiculo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "lista.h"
#include "../usuario/usuario.h"
#include "../mylib.h"
#include "../validacoes/validacoes.h"
#include "../menu.h"


typedef struct lista{
    void* info;
    struct lista* prox;
} Lista;


Lista* arrayCria( void ){
    Lista* array;

    srand(clock());

    array = (Lista*) malloc (sizeof(Lista));

    array->info = NULL;
    array->prox = NULL;

    return array;
}


Lista* acessa( Lista* array, int indice ){
    Lista* i, *inicio;
    int j;

    if( indice == -1 ){
        return array;
    }

    j = indice % 2 == 0;
    inicio = j ? array : array->prox;

    for( i = inicio, j = !j; i != NULL; i = i->prox->prox, j += 2 ){
        if( j == indice ){
            return i->prox;
        }
    }

    printf("Indíce fora da lista.\n");
    exit(1);
}


void append( Lista* array, void* novoElemento ){
    Lista* nova, *busca;

    nova = arrayCria();

    nova->info = novoElemento;

    busca = array;
    while( busca->prox != NULL ){
        busca = busca->prox;
    }

    busca->prox = nova;
}


int size( Lista* array ){
    Lista* i;
    int j;

    if( array->prox == NULL ){
        return 0;
    }

    for( i = array->prox, j = 0; i->prox != NULL; i = i->prox, j++ ){
    }

    return j+1;
}


void pop( Lista* array, int indice ){
    Lista* aux, *aux1;
    
    if( array->prox == NULL ){
        printf("Indíce fora da lista.\n");
        exit(1);
    }

    aux1 = acessa(array, indice);

    if( aux1->prox == NULL ){
        acessa(array, indice-1)->prox = NULL;
    } else {
        aux = acessa(array, indice+1);
        acessa(array, indice-1)->prox = aux1;
    }

    free(aux1);
}


void liberaLista( Lista* array ){
    if( array != NULL ){
        liberaLista(array->prox);
        free(array);
    }
}


void swap( Lista* array, int indice1, int indice2 ){
    Lista *pI1, *pI2, pn1;

    if( indice1 == indice2 ){
        return;
    }

    pI1 = acessa(array, indice1);
    pI2 = acessa(array, indice2);
    pn1.info = pI1->info;
    pI1->info = pI2->info;
    pI2->info = pn1.info;
}


void* pos( Lista* array, int indice ){
    Lista* i, *inicio;
    int j;

    if( array->prox == NULL ){
        printf("Indíce fora da lista.\n");
        exit(1);
    }
        

    j = indice % 2 == 0;
    inicio = j ? array : array->prox;

    for( i = inicio, j = !j; i->prox != NULL; i = i->prox->prox, j += 2 ){
        if( j == indice ){
            return i->prox->info;
        }
    }

    printf("Indíce fora da lista.\n");
    exit(1);
}





/*
void quicksortStr( Lista* array, int began, int end ){
    int i, j, pivo;
    
    i = began;
    j = end - 1;
    pivo = pos(array, (began + end)/2);

    while( i <= j ){
        while( pos(array, i) < pivo && i < end ){
            i++;
        }
        while( pos(array, j) > pivo && j > began ){
            j--;
        }
        if( i <= j ){
            swap(array, i, j);
            i++;
            j--;
        }
    }

    if( j > began ){
        quicksort( array, began, j+1 );
    }
    if( i < end ){
        quicksort( array, i, end );
    }
}

*/