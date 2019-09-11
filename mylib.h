/*TAD: Minha biblioteca para o SIG-car */



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


/* Função voltar
** Operação que solicita ao cliente se ele deseja voltar
*/
void voltar( int );