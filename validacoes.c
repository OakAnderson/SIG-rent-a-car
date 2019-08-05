#include <stdio.h>
#include <string.h>

typedef enum bool {
    True = 1,
    False = 0
} Bool;


/*Função resposta: valida se o usuário digitou sim, retorna Falso ou verdadeiro */
Bool val_resposta( char* output ){
    char entrada[4], nao[4] = "nao";

    printf( "%s ", output );
    scanf( " %3[^\n]", entrada );

    if ( ( entrada[0] != 's' && entrada[0] != 'S' ) && ( entrada[0] != 'n' && entrada[0] != 'N' ) ){
        return val_resposta( output );
    }

    else if( entrada[1] != '\0' && ( entrada[1] != 'i' && entrada[1] != 'I' ) && ( entrada[1] != 'a' && entrada[1] != 'A' )){
        return val_resposta( output );
    }

    else if( entrada[2] != '\0' && ( entrada[2] != 'm' && entrada[2] != 'M' ) && ( entrada[2] != 'o' && entrada[2] != 'O' ) ){
        return val_resposta( output );
    }

    if( entrada[0] == 'n' || entrada[0] == 'N' ){
        return False;
    }
    else {
        return True;
    }
}

Bool val_inteiro( char* output )
{
    char entrada[21];

    printf( "%s ", output );
    scanf( " %20[^\n]", entrada);

    for( int i = 0; entrada[i] != '\0'; i++){
        if( !( (entrada[i] < '9' && entrada[i] > '0') || entrada[i] == '.' ) ){
            return False;
        }
    }
}