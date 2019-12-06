#ifndef CLIENTE_H
#define CLIENTE_H

/*TAD: Funções para trabalhar com a estrutura cliente */

typedef struct client Cliente;


#define INSERECPF 0
#define INSERENOME 1
#define INSEREDOIS 2
#define INSEREDATANASC 3
#define INSEREENDERECO 4

#define NUM 1
#define CARROS_ALUGADOS 2
#define NOME 3
#define CPF 4
#define DATNASC 5
#define BAIRRO 6
#define ENDERECO 7
#define COMPLEMENTO 8
#define TELEFONE 9
#define STATUS 10

#define DEVENDO 1
#define LIVRE 0

/* Função salva
** Operação que salva os dados de um cliente em arquivo
*/
int clnt_salva( Cliente* pessoa );


/* Função recupera nome
** Operação que recupera os dados de um cliente salvo em
** arquivo, buscando pelo nome
*/
Cliente* clnt_recupera_nome( char* );


/* Função recupera cpf
** Operação que recupera os dados de um cliente salvo em
** arquivo, buscando pelo cpf
*/
Cliente* clnt_recupera_cpf( char* );


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


/* Função cliente nome
** Operação que retorna o nome do cliente
*/
char* clnt_nome( Cliente* );


/* Função cliente cpf
** Operação que retorna o cpf do cliente
*/
char* clnt_cpf( Cliente* );


/* Função cliente num
** Operação que retorna o numero de cadastro do cliente
*/
int clnt_num( Cliente* );


/* Função cliente status
** Operação que retorna o status do cliente
*/
int clnt_status( Cliente* );


/* Função cliente edita
** Operação que recebe um cliente e um campo para alterar, altera
** e salva no arquivo. Retorna 0 se a operação concluiu bem
*/
int clnt_edita( Cliente* cliente, int campo, void* alteracao );


/* Função carros alugados
** Operação que retorna o numero de carros alugados pelo cliente
*/
int clnt_carrosAlugados( Cliente* );


/* Função cliente insere Nome e CPF
** Operação que insere retorna a entrada do usuário
*/
char* clnt_insereNC( int modo );


/* Função cliente edita dados
** Operação que auxilia o usuário a alterar os dados
** de um cliente
*/
void clnt_edita_dados( void );

#endif