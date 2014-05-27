#include <iostream> // biblioteca padrão i/o do c++
#include <cstdlib> // para uso da função rand()
#include <ctime> // para uso da função rand()

#include "Tela.h" // Inclusão da Biblioteca da Classe
#include "Pilha.h" // Inclusão da Biblioteca da Classe
#include "Ponto.h" // Inclusão da Biblioteca da Classe

using std::cout; // inclusão do metódo cout do namespace std

// Construtro Padrão
	Tela::Tela() {

		int elemento, rep;

		qtdElementos = 5;

		pontos = new Pilha();
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
	Tela::Tela(int qtd) {

		int elemento, rep;

		qtdElementos = qtd;
		
		pontos = new Pilha();

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

// Função para imprimir a matriz
	void Tela::print() const {
		for(int i = 0; i < eixoX; i++) {
			for(int j = 0; j < eixoY; j++) {
				cout << getElement(i, j) << " ";
			}
			cout << "\n";		
		}
	}		

 // troca elementos de posição
	void Tela::switchElements(int x1, int y1, int x2, int y2) {
		int aux = getElement(x1, y1);
		setElement(x1, y1, getElement(x2, y2));
		setElement(x2, y2, aux);
	}

// Movimento de elementos após pontuar
	void Tela::moveElement(Ponto ponto) {
		int elemento;

		if(ponto.x == 0) {
			elemento = (rand() % qtdElementos) + 1;
			setElement(ponto.x, ponto.y, elemento);	
			return;
		}

		elemento = getElement(ponto.x-1, ponto.y);
		setElement(ponto.x--, ponto.y, elemento);
		moveElement(ponto);
	}

// Sistema de pontuação
	int Tela::point() {
		int maiorX = 0, v[8], i = 0, pontuacao = 0;
		bool dif, check = true;
		Ponto ponto;

		while(check){
			while(pontos->getSize()) {
				pontuacao++;
				ponto = pontos->pop();
				if(ponto.x > maiorX) maiorX = ponto.x;
				dif = true;
				for(int j = 0; j < i; j++) {
					if(v[j] == ponto.y) dif = false;
				}
				if(dif) v[i++] = ponto.y;
				moveElement(ponto);
			}
			check = checkAfter(maiorX, v, i);
		}

		return pontuacao;

	}

// Verifica se tem combinações (3 ou mais peças) possíveis
	// Verifica Linha
		bool Tela::checkLine(int x) {
			
			int elemento = getElement(x, 0), cont = 1;
			bool flag = false;
			Ponto ponto;

			ponto.x = x;
			ponto.y = 0;

			pontos->push(ponto);

			for (int i = 1; i <= eixoX; ++i) {
				if(i == eixoX){
					if(cont > 2)
						flag = true;
					else {
						pontos->setSize(cont);
					}
				} else {
					if(elemento == getElement(x, i)) {
						ponto.x = x;
						ponto.y = i;

						pontos->push(ponto);

						cont++;
					} else {
						if(cont > 2)
							flag = true;
						else {
							pontos->setSize(cont);
						}
						ponto.x = x;
						ponto.y = i;
						pontos->push(ponto);

						elemento = getElement(x, i);
						cont = 1;
					}
				}
			}
			return flag;
		}
	// Verifica Coluna
		bool Tela::checkColumn(int y) {
			int elemento = getElement(eixoX-1, y), cont = 1;
			bool flag = false;
			Ponto ponto;

			ponto.x = eixoX-1;
			ponto.y = y;
			pontos->push(ponto);

			for (int i = eixoX-2; i >= -1; --i) {
				if(i < 0){
					if(cont > 2)
						flag = true;
					else {
						pontos->setSize(cont);
					}
				} else {
					if(elemento == getElement(i, y)) {
						ponto.x = i;
						ponto.y = y;

						pontos->push(ponto);

						cont++;
					} else {
						if(cont > 2)
							flag = true;
						else {
							pontos->setSize(cont);
						}
						ponto.x = i;
						ponto.y = y;
						pontos->push(ponto);

						elemento = getElement(i, y);
						cont = 1;
					}
				}
			}
			return flag;
		}
	// Verifica a troca
		bool Tela::checkSwitch(int x1, int y1, int x2, int y2) {
			bool flag = false;
			int maxLin, maxCol;
			
			switchElements(x1, y1, x2, y2);


			if(checkLine(x1)) flag = true;
			if(checkColumn(y1)) flag = true;
			if(x1 != x2 && checkLine(x2)) flag = true;
			if(y1 != y2 && checkColumn(y2)) flag = true;
			
			if(flag) {
				cout << "Marcou " << point() << " pontos.\n"; // Monta a pontuação
				return true;
			}

			switchElements(x2, y2, x1, y1);
			return false;
		}
	// Verifica após a troca
		bool Tela::checkAfter(int maxX, int * v, int n) {
			bool flag = false;
			for (int i = 0; i <= maxX; ++i)
				if(checkLine(i)) flag = true;
			for (int i = 0; i < n; ++i)
				if(checkColumn(v[i])) flag = true;
			return flag;
		}