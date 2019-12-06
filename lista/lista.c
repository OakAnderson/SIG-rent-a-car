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
#include "../aluguel/aluguel.h"
#include "../usuario/usuario.h"
#include "../mylib.h"
#include "../validacoes/validacoes.h"
#include "../menu.h"


#define par(a) a % 2 == 0 ? (1) : (0)

typedef struct _elemento {
    void* info;
    struct _elemento* ant;
    struct _elemento* prox;
} Elem;


typedef struct _array {
    struct _elemento* ini;
    struct _elemento* fim;
    int size;
} Array;


typedef struct node {
    void* info;
    struct node *left;
    struct node *right;
} Node;


typedef struct tree {
    struct node *root;
} Tree;


void indice_error(void){
    printf("Indíce fora da lista.\n");
    exit(1);
}


Node* setNode( void* info ){
    Node* new = (Node*) malloc (sizeof(Node));

    new->info = info;
    new->left = NULL;
    new->right = NULL;

    return new;
}


void addNodeClienteNome( Node* node, Node* new ){
    int side;
    Cliente* nodeC, *newC;

    nodeC = (Cliente*) node->info;
    newC = (Cliente*) new->info;

    side = str_cmp(clnt_nome(nodeC), clnt_nome(newC));

    if( side > 0 ){
        if( node->left == NULL ){
            node->left = new;
        } else {
            addNodeClienteNome(node->left, new);
        }
    } else if( side < 0 ){
        if( node->right == NULL ){
            node->right = new;
        } else {
            addNodeClienteNome(node->right, new);
        }
    }
}


void addNodeClienteCPF( Node* node, Node* new ){
    int side;
    Cliente* nodeC, *newC;

    nodeC = (Cliente*) node->info;
    newC = (Cliente*) new->info;

    side = strcmp(clnt_cpf(nodeC), clnt_cpf(newC));

    if( side < 0 ){
        if( node->left == NULL ){
            node->left = new;
        } else {
            addNodeClienteCPF(node->left, new);
        }
    } else if( side > 0 ){
        if( node->right == NULL ){
            node->right = new;
        } else {
            addNodeClienteCPF(node->right, new);
        }
    }
}


Tree* newTree( void ){
    return (Tree*) malloc (sizeof(Tree));
}


void addClienteNome( Tree* tree, void* cliente ){
    Node* new;

    new = setNode(cliente);
    if( tree->root == NULL ){
        srand(clock());
        tree->root = new;
    } else {
        addNodeClienteNome(tree->root, new);
    }
}


void addClienteCPF( Tree* tree, void* cliente ){
    Node* new;

    new = setNode(cliente);
    if( tree->root == NULL ){
        srand(clock());
        tree->root = new;
    } else {
        addNodeClienteCPF(tree->root, new);
    }
}


Cliente* searchNodeClienteNome( Node* node, char* palavra ){
    int achou;
    Cliente* nodeC;

    nodeC = (Cliente*) node->info;

    achou = cmp_nomes(palavra, clnt_nome(nodeC));

    if( achou == 0 ){
        return (Cliente*) node->info;
    } else if( achou < 0 ){
        if( node->left != NULL ){
            return searchNodeClienteNome( node->left, palavra );
        } else {
            return NULL;
        }
    } else if ( achou > 0 ){
        if( node->right != NULL ){
            return searchNodeClienteNome( node->right, palavra );
        } else {
            return NULL;
        }
    }
}


Cliente* searchNodeClienteCPF( Node* node, char* palavra ){
    int achou;
    Cliente* nodeC;

    nodeC = (Cliente*) node->info;

    achou = strcmp(palavra, clnt_cpf(nodeC));

    if( achou == 0 ){
        return (Cliente*) node->info;
    } else if( achou > 0 ){
        if( node->left != NULL ){
            return searchNodeClienteCPF( node->left, palavra );
        } else {
            return NULL;
        }
    } else if ( achou < 0 ){
        if( node->right != NULL ){
            return searchNodeClienteCPF( node->right, palavra );
        } else {
            return NULL;
        }
    }
}


Cliente* searchClienteNome( Tree* tree, char* palavra ){
    return searchNodeClienteNome(tree->root, palavra);
}


Cliente* searchClienteCPF( Tree* tree, char* palavra ){
    return searchNodeClienteCPF(tree->root, palavra);
}


void mostraNodeCliente( Node* node ){
    if( node->left != NULL ){
        mostraNodeCliente( node->left );
    }

    printf("\nNº %d - - - - - - - - - - - - - - - -\n", clnt_num((Cliente*) node->info));
    clnt_mostra( (Cliente*) node->info );
    printf("\n- - - - - - - - - - - - - - - - - - -\n");

    if( node->right != NULL ){
        mostraNodeCliente( node->right );
    }
}


void mostraCliente( Tree* tree ){
    mostraNodeCliente(tree->root);
}


void freeSingleNodeCliente( Node* node ){
    clnt_libera( (Cliente*) node->info );
    free( node );
}


void freeNodesCliente( Node* node ){
    if( node->left != NULL ){
        freeNodesCliente( node->left );
    }

    if( node->right != NULL ){
        freeNodesCliente( node->right );
    }

    freeSingleNodeCliente( node );
}


void freeTreeCliente( Tree* tree ){
    freeNodesCliente(tree->root);
}


Elem* acessaInversa( Array* array, int indice ){
    Elem* inicio;
    int cont = array->size-1;

    if( ((par(cont)) && (par(indice))) || (!(par(cont)) && !(par(indice))) ){
        inicio = array->fim;
        cont = array->size-1;
    } else {
        inicio = array->fim->ant;
        cont = array->size-2;
    }

    for( Elem *i = inicio; i != NULL; i = i->ant->ant, cont-=2 ){
        if( cont == indice ){
            return i;
        }
    }
}


Elem* acessaFrente( Array* array, int indice ){
    Elem* inicio;
    int cont = 0;

    if( par(indice) ){
        inicio = array->ini->prox->prox;
        cont = 2;
    } else {
        inicio = array->ini->prox;
        cont = 1;
    }

    for( Elem *i = inicio; i != NULL; i = i->prox->prox, cont+=2 ){
        if( cont == indice ){
            return i;
        }
    }
}


Array* arrayCria( void ){
    Array* novo;

    srand(clock());

    novo = ( Array* ) malloc ( sizeof(Array) );

    novo->ini = NULL;
    novo->fim = NULL;
    novo->size = 0;

    return novo;
}


Elem* acessa( Array* array, int indice ){
    Elem* i, *inicio;
    int cont, auxI;

    auxI = indice;

    if( indice == -1 )
        return array->fim;

    else if( indice == 0 )
        return array->ini;

    else if( indice > array->size )
        indice_error();
    
    else if( indice < 0 )
        auxI = array->size + indice;


    if( auxI > array->size/2 )
        return acessaInversa(array, auxI);

    else
        return acessaFrente(array, auxI);
}

void append( Array* array, void* elemento ){
    Elem* novo;
    if( array->size == 0 ){
        novo = (Elem*) malloc(sizeof(Elem));
        novo->ant = NULL; novo->prox = NULL;
        novo->info = elemento;
        array->fim = novo;
        array->ini = novo;
        array->size++;
    } else {
        novo = (Elem*) malloc(sizeof(Elem));
        novo->info = elemento;
        novo->ant = array->fim;
        novo->prox = NULL;
        array->fim->prox = novo;
        array->fim = novo;
        array->size++;
    }
}


void appendInt( Array* array, int num ){
    int *valor = (int*) malloc(sizeof(int));
    *valor = num;
    append( array, valor );
}


int intIn( Array* array, int num ){
    for( Elem* i = array->ini; i != NULL; i = i->prox ){
        if( *(int*) i->info == num ){
            return 1;
        }
    }

    return 0;
}


int size( Array* array ){
    return array->size;
}


void pop( Array* array, int indice ){
    Elem *aux1;
    
    if( array->ini == NULL ){
        indice_error();
    }

    aux1 = acessa(array, indice);

    if( indice == 0 ){
        array->ini = aux1->prox;
        array->ini->ant = NULL;
    } else if( aux1->prox == NULL ){
        aux1->ant->prox = NULL;
        array->fim = aux1->ant;
    } else {
        aux1->ant->prox = aux1->prox;
        aux1->prox->ant = aux1->ant;
    }

    free(aux1->info);
    free(aux1);
}


void __liberaElems__( Elem* elemento ){
    if( elemento != NULL ){
        __liberaElems__(elemento->prox);
        free(elemento->info);
        free(elemento);
    }
}


void liberaLista( Array* array ){
    if( array != NULL ){
        __liberaElems__(array->ini);
    }
}


void swap( Array* array, int indice1, int indice2 ){
    Elem *pI1, *pI2, pn1;

    if( indice1 == indice2 ){
        return;
    }

    pI1 = acessa(array, indice1);
    pI2 = acessa(array, indice2);
    pn1.info = pI1->info;
    pI1->info = pI2->info;
    pI2->info = pn1.info;
}


void* pos( Array* array, int indice ){
    return acessa(array, indice)->info;
}


