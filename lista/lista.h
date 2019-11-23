/* TAD: Estrura lista para manipulação dos dados */
#ifndef LISTA_H
#define LISTA_H

#define CLIENTE 0
#define VEICULO 1

typedef struct _array Array;
typedef struct _elemento Elem;

typedef struct tree Tree;

/* Função cria cria lista
** Operação que cria uma nova lista alocando o primeiro elemento
*/
Array* arrayCria( void );


/* Função adiciona ao final
** Operação que adiciona ao final da lista um novo elemento
*/
void append( Array*, void* );


/* Função posição
** Retorna a informação guardada na posição solicitada
*/
void* pos( Array*, int indice);


/* Função tamanho
** Retorna o tamanho da lista
*/
int size( Array* );


/* Função libera lista
** Libera da memória todos os elementos da lista
*/
void liberaLista( Array* );


Tree* newTree( void );


void addClienteNome( Tree*, void* );


void addClienteCPF( Tree*, void* );


Cliente* searchClienteNome( Tree*, char* );


Cliente* searchClienteCPF( Tree*, char* );

#endif