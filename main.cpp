#include <iostream> // biblioteca padrão I/O do C++

#include "Tela.h" // Inclusão da Biblioteca da Classe

int main() {
	
	Tela * jogo = new Tela();

	jogo->imprimir();

	delete jogo;

	return 0;
}