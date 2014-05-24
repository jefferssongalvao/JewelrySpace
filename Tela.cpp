#include <iostream> // biblioteca padrão i/o do c++
#include <cstdlib> // para uso da função rand()

#include "Tela.h" // Inclusão da Biblioteca da Classe

using std::cout; // inclusão do metódo cout do namespace std

// Construtro Padrão
	Tela::Tela() {

		srand(time(NULL));

		int elemento, rep;

		int qtdElementos = 3;
		
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

// Construtor com Parâmetros
	Tela::Tela(int qtdElementos) {

		srand(time(NULL));

		int elemento, rep;
		
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
 // Função para imprimir a matriz
	void Tela::imprimir() const {
		for(int i = 0; i < eixoX; i++) {
			for(int j = 0; j < eixoY; j++) {
				cout << matriz[i][j] << " ";
			}
			cout << "\n";		
		}
	}