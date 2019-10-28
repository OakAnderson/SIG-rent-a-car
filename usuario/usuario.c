#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "usuario.h"
#include "../cliente/cliente.h"
#include "../mylib.h"
#include "../validacoes/validacoes.h"
#include "../menu/menu.h"
#include "../veiculo/veiculo.h"

#define SEM_USUARIO -1

typedef struct usuario{
    char username[21];
    char senha[21];
} Usuario;


int usr_recupera( Usuario* usuarioEntrada ){
    FILE* arquivo;
    Usuario* usuarioSaida;

    arquivo = fopen("Usuario.dat", "rb");
    if( arquivo == NULL){
        arquivo = fopen("Usuario.dat", "wb");
        return -1;
    }

    usuarioSaida = (Usuario*) malloc (sizeof(Usuario));

    fread( usuarioSaida, sizeof(Usuario), 1, arquivo );
    while( !feof(arquivo) ){
        if( !strcmp(usuarioSaida->username, usuarioEntrada->username) ){
            if( !strcmp(usuarioSaida->senha, usuarioEntrada->senha) ){
                fclose(arquivo);
                free(usuarioSaida);
                return 1;
            }
        }
        fread( usuarioSaida, sizeof(Usuario), 1, arquivo );
    }

    free(usuarioSaida);
    fclose(arquivo);

    return 0;
}


void usr_login( void ){
    Usuario* user;
    char *nome, *senha;
    int cont = 1;

    nome = entr_str("Usuário: ");
    while (!val_username(nome))
    {
        printf("Nome de usuário inválido!\n");
        nome = entr_str("Usuário: ");
    }
    
    senha = entr_str("Senha: ");
    while( !val_senha(senha) ){
        printf("A senha deve ser entre 6 e 20 e conter apenas caracteres válidos\n");        
        senha = entr_str("Senha: ");
    }

    user = (Usuario*) malloc(sizeof(Usuario));

    strcpy(user->username, nome);
    strcpy(user->senha, senha);

    if(usr_recupera(user) == SEM_USUARIO){
        usr_cad(nome, senha);
    } else {
        while( !( usr_recupera(user) ) && cont < 3 ){
            printf("Nome de usuário ou senha incorreto!\n");
            nome = entr_str("Usuário: ");
            senha = entr_str("Senha: ");

            strcpy(user->username, nome);
            strcpy(user->senha, senha);
            cont++;
        }
    }

    if( cont == 3 ){
        system("clear");
        printf("Não foi possível logar. Tente novamente mais tarde.\n");
        sleep(3);
        exit(0);
    } else {
        system("clear");
        printf("Login efetuado com sucesso!\n");
        sleep(3);
    }
}


void usr_cad(char *nome, char *senha ){
    Usuario* user;
    FILE* arquivo;
    int result;

    arquivo = fopen("Usuario.dat", "ab");
    if(arquivo == NULL){
        arquivo = fopen("Usuario.dat", "wb");
    }

    user = (Usuario*) malloc(sizeof(Usuario));
    strcpy(user->username, nome);
    strcpy(user->senha, senha);

    result = fwrite( user, sizeof( Usuario ), 1, arquivo);
    if( result == EOF ){
        exit(1);
    }

    free(user);
    fclose(arquivo);
}