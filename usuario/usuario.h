/* TAD: Usuario */
#ifndef USUARIO_H
#define USUARIO_H

typedef struct usuario Usuario;

/* Função recupera usuario
** Operação que recupera um usuario nos dados e compara com o usuario de entrada
*/
int usr_recupera( Usuario* );


/* Função user login
** Operação que efetua o login de usuario, solicitando o nome e senha
*/
void usr_login( void );


/* Função cadastra usuário
** Operação que salva um usuario nos dados
*/
void usr_cad( char*, char* );
#endif