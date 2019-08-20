/* TAD: Funções que valida strings */

/* Função valida REGEX
** Operação que recebe uma regex e uma frase, combina e retorna
** verdadeiro ou falso
** Retorna 1 se for válido
*/
int val_regex( char* expReg, char* frase );


/* Função valida email
** Operação que retorna o resultado da função val_regex combinando
** para emails
** Retorna 1 se for válido
*/
int val_email( char* email );


/* Função valida cpf
** Operação que retorna o resultado da função val_regex combinando
** para CPFs
** Retorna 1 se for válido
*/
int val_cpf( char* cpf );


/* Função valida número
** Operação que retorna o resultado da função val_regex combinando
** para números de telefone brasileiros
** Retorna 1 se for válido
*/
int val_num( char* numero );


/* Função valida data
** Operação que retorna o resultado da função val_regex combinando
** para datas
** Retorna 1 se for válido
*/
int val_data( char* data );


/* Função valida nome
** Operação que verifica se a entrada do usuário é um nome próprio
** Retorna 1 se for válido
*/
int val_nome( char* nome );


/* Função valida inteiro
** Operação que verifica se o usuário digitou um número
** Retorna 1 se for inteiro, 0 se diferente de inteiro
*/
int val_inteiro( char* entrada );


/* Função valida sim não
** Verifica se o usuário digitou sim ou nao
** Retorna 1 se foi um dos dois
*/
int val_SN( char* entrada );