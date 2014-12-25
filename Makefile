							# Makefile para compilação e linkedição do projeto

# define o compilador a ser utilizado
CP=g++

# utilizada para adicionar opcoes a compilacao
COPT=-c -Wall -std=c++11

# variavéis para flags de SDL
SDL=-lSDL
IMAG=-lSDL_image
MIX=-lSDL_mixer
TTF=-lSDL_ttf

# variável para flag da cmath
LM=-lm

# variavel para pasta 'src/'
SRC=src/

# variavel para pasta 'obj/'
OBJ=obj/

# variavel para pasta 'include/'
INC=include/

main: main.o Tela.o
	$(CP) $(OBJ)*.o -o main	$(LM) $(SDL) $(IMAG) $(MIX) $(TTF)

main.o: Tela.o
	$(CP) $(COPT) -I $(INC) $(SRC)main.cpp -o $(OBJ)main.o

Tela.o: Usuario.o Pilha.o
	$(CP) $(COPT) $(LM) $(SDL) $(IMAG) $(MIX) $(TTF) -I $(INC) $(SRC)Tela.cpp -o $(OBJ)Tela.o

Usuario.o:
	$(CP) $(COPT) $(SDL) $(TTF) -I $(INC) $(SRC)Usuario.cpp -o $(OBJ)Usuario.o

Pilha.o:
	$(CP) $(COPT) -I $(INC) $(SRC)Pilha.cpp -o $(OBJ)Pilha.o