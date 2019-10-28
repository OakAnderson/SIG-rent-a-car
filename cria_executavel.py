from os import system as sys

sys("""
    gcc -c cliente/cliente.c
    gcc -c menu/menu.c
    gcc -c mylib.c
    gcc -c validacoes/validacoes.c
    gcc -c veiculo/veiculo.c
    gcc -c usuario/usuario.c
    gcc -o exe main.c cliente.o menu.o mylib.o validacoes.o veiculo.o usuario.o
    rm *.o

""")