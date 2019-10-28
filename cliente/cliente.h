#ifndef CLIENTE_H
#define CLIENTE_H

/*TAD: Funções para trabalhar com a estrutura cliente */

typedef struct client Cliente;


/* Função salva
** Operação que salva os dados de um cliente em arquivo
*/
int clnt_salva( Cliente* pessoa );


/* Função recupera nome
** Operação que recupera os dados de um cliente salvo em
** arquivo, buscando pelo nome
*/
Cliente* clnt_recupera_nome( void );


/* Função recupera cpf
** Operação que recupera os dados de um cliente salvo em
** arquivo, buscando pelo cpf
*/
Cliente* clnt_recupera_cpf( void );


/* Função recupera dados
** Operação que busca dados de um cliente a partir de um
** paramêtro escolhido
*/
void clnt_re_dados( void );

/* Função obtém nome
** Operação que obtém o nome do cliente
*/
void clnt_ins_nome( Cliente* pessoa );


/* Função obtém CPF
** Operação que obtém o CPF do cliente
*/
void clnt_ins_cpf( Cliente* pessoa );


/* Função obtém data de nascimento
** Operação que obtém a data de nascimento do cliente
*/
void clnt_ins_datNasc( Cliente* pessoa );


/* Função mostra nome cliente
** Operação que mostra o nome do cliente na tela
*/
void clnt_mostra_nome( Cliente* pessoa );


/* Função mostra cpf cliente
** Operação que mostra o CPF do cliente na tela
*/
void clnt_mostra_cpf( Cliente* pessoa );


/* Função mostra data de nascimento cliente
** Operação que mostra a data de nascimento do cliente na tela
*/
void clnt_mostra_datNasc( Cliente* pessoa );

/* Função libera cliente
** Operação que libera o espaço armazenado por um cliente
*/
void clnt_libera( Cliente* pessoa );

/* Função cliente cria
** Operação que aloca um espaço na memória para um cliente
*/
Cliente* clnt_cria( void );

/* Função mostra
** Operação que mostra os dados do cliente na tela
*/
void clnt_mostra( Cliente* pessoa );


/* Função cadastra cliente
** Operação que inicia o cadastro do cliente
*/
void clnt_cad( void );

/* Função mostra todos os clientes
** Operação que mostra na tela todos os clientes cadastrados
*/
void clnt_mostra_todos( void );


/* Função compara clientes
** Operação que retorna 1 se as estruturas passadas forem iguais
*/
int clnt_compara( Cliente*, Cliente* );


/* Função existe cliente
** Operação que retorna 1 se o cliente já estiver cadastrado
*/
int clnt_existe( Cliente* );


/* Função deleta cliente
** Operação que deleta (altera o status) um cliente dos dados
*/
void clnt_deleta( void );

#endif