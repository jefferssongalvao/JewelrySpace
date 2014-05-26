#include <iostream> // biblioteca padrão i/o do c++
#include <cstdlib> // para uso da função rand()

#include "Tela.h" // Inclusão da Biblioteca da Classe
#include "Pilha.h" // Inclusão da Biblioteca da Classe
#include "Ponto.h" // Inclusão da Biblioteca da Classe

using std::cout; // inclusão do metódo cout do namespace std

// Construtro Padrão
	Tela::Tela() {

		srand(time(NULL));

		int elemento, rep;

		int qtdElementos = 3;

		pilha = new Pilha();
		
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
		
		pilha = new Pilha();

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
		bool Tela::checkLine(int x) {
			
			int elemento = getElement(x, 0), cont = 1;
			bool flag = false;
			Ponto ponto;

			ponto.x = x;
			ponto.y = 0;

			pilha->push(ponto);

			for (int i = 1; i <= eixoX; ++i) {
				if(i == eixoX){
					if(cont > 2)
						flag = true;
					else {
						pilha->setSize(cont);
					}
				} else {
					if(elemento == getElement(x, i)) {
						ponto.x = x;
						ponto.y = i;

						pilha->push(ponto);

						cont++;
					} else {
						if(cont > 2)
							flag = true;
						else {
							pilha->setSize(cont);
						}
						if(i < eixoX-1) {

							ponto.x = x;
							ponto.y = i;
							pilha->push(ponto);

							elemento = getElement(x, i);
							cont = 1;
						}
					}
				}
			}
			return flag;
		}
	// Verifica Coluna
		bool Tela::checkColumn(int y) {
			int elemento = getElement(0, y), cont = 1;
			bool flag = false;
			Ponto ponto;

			ponto.x = 0;
			ponto.y = y;
			pilha->push(ponto);

			for (int i = 1; i < eixoY; ++i) {
				if(i == eixoY){
					if(cont > 2)
						flag = true;
					else {
						pilha->setSize(cont);
					}
				} else {
					if(elemento == getElement(i, y)) {
						ponto.x = i;
						ponto.y = y;

						pilha->push(ponto);

						cont++;
					} else {
						if(cont > 2)
							flag = true;
						else {
							pilha->setSize(cont);
						}
						if(i < eixoY-1) {

							ponto.x = i;
							ponto.y = y;
							pilha->push(ponto);

							elemento = getElement(i, y);
							cont = 1;
						}
					}
				}
			}
			return flag;
		}
	// Verifica a troca
		bool Tela::checkSwitch(int x1, int y1, int x2, int y2) {
			bool flag;
			
			switchElements(x1, y1, x2, y2);

			Ponto ponto;

			if(checkLine(x1)) flag = true;
			if(checkColumn(y1)) flag = true;
			if(checkLine(x2)) flag = true;
			if(checkColumn(y2)) flag = true;
			
			if(flag) {
				while(pilha->getSize()) {
					ponto = pilha->pop();
					setElement(ponto.x, ponto.y, 0);
				}
				return true;
			}

			switchElements(x2, y2, x1, y1);
			return false;
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