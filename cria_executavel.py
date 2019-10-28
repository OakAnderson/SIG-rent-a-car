from os import system as sys

sys("""
    gcc -c cliente.c
    gcc -c menu.c
    gcc -c mylib.c
    gcc -c validacoes.c
    gcc -c veiculo.c
    gcc -o exe main.c cliente.o menu.o mylib.o validacoes.o veiculo.o
    rm *.o

""")