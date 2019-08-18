/* TAD: Funções que valida strings */

/* Função valida REGEX
** Operação que recebe uma regex e uma frase, combina e retorna
** verdadeiro ou falso
*/
int val_regex( char* expReg, char* frase );


/* Função valida email
** Operação que retorna o resultado da função val_regex combinando
** para emails
*/
int val_email( char* email );


/* Função valida cpf
** Operação que retorna o resultado da função val_regex combinando
** para CPFs
*/
int val_cpf( char* cpf );


/* Função valida número
** Operação que retorna o resultado da função val_regex combinando
** para números de telefone brasileiros
*/
int val_num( char* numero );


/* Função valida data
** Operação que retorna o resultado da função val_regex combinando
** para datas
*/
int val_data( char* data );


/* Função valida nome
** Operação que verifica se a entrada do usuário é um nome próprio
*/
int val_nome( char* nome );


/* FUnção valida inteiro
** Operação que verifica se o usuário digitou um número
*/
int val_inteiro( char* entrada );