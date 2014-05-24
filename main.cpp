#include <iostream>

#include "Tela.h" // Inclusão da Biblioteca da Classe

int main() {
	
	Tela * fase = new Tela();

	fase->imprimir();

	delete fase;

	return 0;
}