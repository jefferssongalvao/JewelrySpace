#include <iostream>
#include <cstdlib> // para uso da função rand()

#include "Tela.h" // Inclusão da Biblioteca da Classe

using std::cout;

Tela::Tela() {

	srand(time(NULL));

	int elemento, rep;
	
	qtdElementos = 4;
	
	for(int i = 0; i < eixoX; i++) {
		rep = 0;
		for(int j = 0; j < eixoY; j++) {
			elemento = (rand() % qtdElementos) + 1;
			if(rep == 0) {
				if(i > 1) {
					while(matriz[i-1][j] == elemento && matriz[i-2][j] == elemento)
						elemento = (rand() % qtdElementos) + 1;
				}
				if(j > 0 && matriz[i][j-1] == elemento) rep++;
			} else {
				if(i > 1) {
					while(matriz[i-1][j] == elemento && matriz[i-2][j] == elemento || matriz[i][j-1] == elemento)
						elemento = (rand() % qtdElementos) + 1;
				} else {
					while(matriz[i][j-1] == elemento)
						elemento = (rand() % qtdElementos) + 1;
				}
				rep = 0;
			}
			matriz[i][j] = elemento;
		}
	}
}

Tela::~Tela() {
}
void Tela::imprimir() const {
	for(int i = 0; i < eixoX; i++) {
		for(int j = 0; j < eixoY; j++) {
			cout << matriz[i][j] << " ";
		}
		cout << "\n";		
	}
}