from os import system as sys

sys("""
    gcc -c lista/lista.c 
    gcc -c cliente/cliente.c
    gcc -c veiculo/veiculo.c
    gcc -c aluguel/aluguel.c
    gcc -c menu/menu.c
    gcc -c mylib.c
    gcc -c validacoes/validacoes.c
    gcc -c usuario/usuario.c
    gcc -Wall -o exe main.c cliente.o aluguel.o menu.o mylib.o validacoes.o veiculo.o lista.o usuario.o
    rm *.o

""")