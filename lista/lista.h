/* TAD: Estrura lista para manipulação dos dados */
#ifndef LISTA_H
#define LISTA_H

#define CLIENTE 0
#define VEICULO 1

typedef struct lista Lista;

/* Função cria cria lista
** Operação que cria uma nova lista alocando o primeiro elemento
*/
Lista* arrayCria( void );


/* Função adiciona ao final
** Operação que adiciona ao final da lista um novo elemento
*/
void append( Lista*, void* );


/* Função posição
** Retorna a informação guardada na posição solicitada
*/
void* pos( Lista*, int indice);


/* Função tamanho
** Retorna o tamanho da lista
*/
int size( Lista* );


/* Função libera lista
** Libera da memória todos os elementos da lista
*/
void liberaLista( Lista* );

#endif