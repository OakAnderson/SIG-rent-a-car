/*TAD: Minha biblioteca para o SIG-car */


/* Função imprime menu
** Operação que mostra o menu principal na tela
*/
void imp_menu_p( void );


/* Função imprime sobre
** Operação que mostra a tela de sobre para o usuário
*/
void imp_sobre( void );


/* Função get menu
** Operação que abre uma nova página de acordo com a entrada do usuário
*/
void get_menu( int n );


/* Função input
** Operação que obtém a entrada do usuário e aloca corretamente
*/
char* entr_str( char* frase );


/* Função escolha de menu
** Recebe um número de opções e valida se a escolha do usuário está dentro
** das opções; retorna a escolha do usuário como inteiro
*/
int menu_escolha( int n);


/* Função get menu principal
** Operação que executa um menu secundário de acordo com a escolha do usuário
*/
void get_menu_p( int n );


/* Função imprime menu cliente
** Operação que mostra na tela o menu secundário de opções para cliente
*/
void imp_menu_cliente( void );


/* Função get menu cliente
** Operação que obtém executa a escolha do usuário
*/
void get_menu_cliente( int n );


/* Função inicia programa
** Operação que dá início ao programa, começando pela tela principal
*/
void inicia_programa( void );


/* Função formata CPF
** Coloca os pontos e o hífen na posição correta
*/
char* form_cpf( char* entrada );


/* Função formata data
** Coloca as barras nas posições corretas
*/
char* form_data(  char* entrada);


/* Função ano atual
** Retorna o ano em que o usuário está
*/
int ano_atual( void );


/* Função mes atual
** Retorna o mes em que o usuário está
*/
int mes_atual( void );


/* Função dia atual
** Retorna o dia em que o usuário está
*/
int dia_atual( void );