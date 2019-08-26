/*TAD: Funções para trabalhar com a estrutura cliente */

typedef struct client Cliente;


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

/* Função libera cliente
** Operação que libera o espaço armazenado por um cliente
*/
void clnt_libera( Cliente* pessoa );

/* Função cadastra cliente
** Operação que inicia o cadastro do cliente
*/
void clnt_cad( void );

/* Função mostra cpf cliente
** Operação que mostra o CPF do cliente na tela
*/
void clnt_mostra_cpf( Cliente* pessoa );


/* Função mostra data de nascimento cliente
** Operação que mostra a data de nascimento do cliente na tela
*/
void clnt_mostra_datNasc( Cliente* pessoa );

/* Função mostra
** Operação que mostra os dados do cliente na tela
*/
void clnt_mostra( Cliente* pessoa );