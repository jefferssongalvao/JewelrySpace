#include <iostream>

#include "Tela.h" // Inclusão da Biblioteca da Classe

int main() {
	
	Tela * jogo = new Tela();

	jogo->imprimir();

	delete jogo;

	return 0;
}