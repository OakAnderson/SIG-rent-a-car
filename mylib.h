/*TAD: Minha biblioteca para o SIG-car */

typedef struct client Cliente;

/* Função imprime menu
** Operação que mostra o menu principal na tela
*/
void imp_menu( void );

/* Função imprime sobre
** Operação que mostra a tela de sobre para o usuário
*/
void imp_sobre( void );

/* Função get menu
** Operação que abre uma nova página de acordo com a entrada do usuário
*/
void get_menu( int n );

/* Função aloca cliente
** Operação que reserva um espaço na memória para um cliente
*/
Cliente* cria_cliente( void );

/* Função obtém nome
** Operação que obtém o nome do cliente
*/
void at_nome( Cliente* pessoa );

/* Função mostra nome cliente
** Operação que mostra o nome do cliente na tela
*/
void most_nomeCliente( Cliente* pessoa );

/* Função libera cliente
** Operação que libera o espaço armazenado por um cliente
*/
void libera_cliente( Cliente* pessoa );

/* Função cadastra cliente
** Operação que inicia o cadastro do cliente
*/
void cad_cliente( void );