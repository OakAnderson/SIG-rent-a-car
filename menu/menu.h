/* TAD: Menus */
#ifndef MENU_H
#define MENU_H

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

/* Função imprime menu veículo
** Operação que mostra na tela o menu secundário de opções para veículo
*/
void imp_menu_veiculo( void );


/* Função get menu veículo
** Operação que obtém e executa a escolha do usuário
*/
void get_menu_veiculo( int );


/* Função inicia programa
** Operação que dá início ao programa, começando pela tela principal
*/
void inicia_programa( void );


/* Função imprime menu
** Operação que mostra o menu principal na tela
*/
void imp_menu_p( void );


/* Função imprime sobre
** Operação que mostra a tela de sobre para o usuário
*/
void imp_sobre( void );


/* Função imprime cliente dados
** Operação que mostra na tela as opções de recuperação de dados
*/
void imp_clnt_visualizarDados( void );
#endif