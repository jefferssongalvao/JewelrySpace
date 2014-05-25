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

// metódo GET
	int Tela::getElement(int x, int y) const { return matriz[x][y]; }
// metódo SET
	void Tela::setElement(int x, int y, int element) { matriz[x][y] = element; }

 // troca elementos de posição
	void Tela::switchElements(int x1, int y1, int x2, int y2) {
		int aux = getElement(x1, y1);
		setElement(x1, y1, getElement(x2, y2));
		setElement(x2, y2, aux);
	}

// Verifica se tem combinações (3 ou mais peças) possíveis
	// Verifica Linha
		bool Tela::checkLine(int x) const {
			int elemento = matriz[x][0], cont = 0;
			for (int i = 1; i < eixoX; ++i) {
				if(elemento == matriz[x][i])
					cont++;
				else {
					if(cont > 1) return true;
					else
						elemento = matriz[x][i];
					cont = 0;
				}
			}
			return false;
		}
	// Verifica Coluna
		bool Tela::checkColumn(int y) const {
			int elemento = matriz[0][y], cont = 0;
			for (int i = 1; i < eixoY; ++i) {
				if(elemento == matriz[i][y])
					cont++;
				else {
					if(cont > 1) return true;
					else
						elemento = matriz[i][y];
					cont = 0;
				}
			}
			return false;
		}
	// Verifica a troca
		bool Tela::checkSwitch(int x1, int y1, int x2, int y2) {
			switchElements(x1, y1, x2, y2);
			if(checkLine(x1) || checkColumn(y1) || checkLine(x2) || checkColumn(y2))
				return true;
			else {
				switchElements(x2, y2, x1, y1);
				return false;
			}
		}


 // Função para imprimir a matriz
	void Tela::print() const {
		for(int i = 0; i < eixoX; i++) {
			for(int j = 0; j < eixoY; j++) {
				cout << matriz[i][j] << " ";
			}
			cout << "\n";		
		}
	}