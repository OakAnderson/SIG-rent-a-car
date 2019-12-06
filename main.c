#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "usuario/usuario.h"
#include "cliente/cliente.h"
#include "mylib.h"
#include "validacoes/validacoes.h"
#include "menu/menu.h"
#include "veiculo/veiculo.h"


int main ( int args, char** argv ){

    system("clear");
    printf("\n_ _ _ _ _ LOGIN _ _ _ _ _\n\n");

    if( args == 1)
        usr_login();
    
    setlocale(LC_ALL, "");
    
    inicia_programa();
    return 0;
}