/* TAD: Funções que valida strings */
#ifndef VALIDACOES_H
#define VALIDACOES_H

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


/* Função valida placa
** Operação que retorna o resultado da função val_regex combinando
** para placas..
** Retorna 1 se for válido
*/
int val_placa( char* );


/* Função valida ano
** Operação que retorna o resultado da função val_regex combinando
** para anos
** Retorna 1 se for válido
*/
int val_ano( char* );


/* Função valida marca
** Operação que retorna o resultado da função val_regex combinando
** para marcas
** Retorna 1 se for válido
*/
int val_marca( char* );


/* Função valida renavam
** Operação que retorna o resultado da função val_regex combinando
** para marcas
** Retorna 1 se for válido
*/
int val_renavam( char* );


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


/* Função valida username
** Operação que valida nome de usuário
*/
int val_username( char* entrada );


/* Função valida senha
** Operação que valida senha de usuário
*/
int val_senha( char* entrada );


/* Função valida idade
** Verifica se o usuário tem a data mínima para cadastro
*/
int val_idade( char* data );


/* Função valida endereço
** Verifica se o endereço atende os parâmetros
*/
int val_endereco( char* endenreco );


/* Função valida bairro
** Verifica se o bairro atende os parâmetros
*/
int val_bairro( char* bairro );


/* Função valida quilometragem
** Verifica se a quilometragem atende os parâmetros
*/
int val_km( char* km );


/* Função valida preço
** Verifica se o preço atende os parâmetros
*/
int val_preco( char* preco );


/* Função compara nomes
** Verifica se os nomes inseridos são equivalentes
*/
int cmp_nomes( char*, char* );


/* Função valida dias
** Operação que retorna verdadeiro se o cliente
** Inseriu uma quantidade de dias para aluguel válida
*/
int val_dias( char* );


/* Função compara strings
** Operação que funciona similar a função strcmp, mas ignora uppercase
*/
int str_cmp( char* str1, char* str2 );
#endif