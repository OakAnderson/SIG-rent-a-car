/*TAD: Minha biblioteca para o SIG-car */
#ifndef MYLIB_H
#define MYLIB_H


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


/* Função formata preco
** Função que retorna o valor de um float a partir
** de uma string
*/
float form_preco( char* );


/* Função formata CPF
** Coloca os pontos e o hífen na posição correta
*/
char* form_cpf( char* entrada );


/* Função formata data
** Coloca as barras nas posições corretas
*/
char* form_data(  char* entrada);


/* Função formata número
** Retorna um novo vetor de caracteres com ou sem formatação
** depende da variável mostrar
*/
char* form_numero( char* entrada, int mostrar );


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
void voltar( void );


/* Função obtem resposta
** Operação que retorna 1 se a resposta do usuário for sim
*/
int get_resposta( char* );


void flush_in(void);
#endif