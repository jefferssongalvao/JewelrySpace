#ifndef _TELA_H_
	#define _TELA_H_

		#include <iostream> // biblioteca padrão i/o do c++
		#include <cstdlib> // para uso da função rand()
		#include <ctime> // para uso da função rand()
		#include <string> // para o nome do usuário do jogo

		#include "Usuario.h" // Inclusão da Biblioteca da Classe
		#include "Pilha.h" // Inclusão da Biblioteca da Classe
		#include "Ponto.h" // Inclusão da Biblioteca da Classe


		//Tamanho da Tela
			#define eixoX 8
			#define eixoY 8

		using std::cout; // inclusão do metódo cout do namespace std
		using std::string; // inclusão da classe string da STL

		class Tela {
			int matriz[eixoX][eixoY]; // pontos na tela
			int qtdElementos;

			Pilha * pontos; // pontos que foram marcados após um movimento
			Pilha * possibilidades; // possibilidades de pontuação

			Usuario * user;

			public:
				Tela(); // Construtor Padrão
				Tela(int qtdElementos); // Construtor com Parâmetros (serve para construir novas fases)

				// metódo GET
					int getElement(int x, int y) const;
				// metódo SET
					void setElement(int x, int y, int element);
					void setUsuario(string str);

				void switchElements(int x1, int y1, int x2, int y2); // troca elementos de posição
				void moveElement(Ponto ponto); // Movimento de elementos após pontuar
				int point(); // Sistema de pontuação

				// Verifica se tem combinações (3 ou mais peças) possíveis
					// Verifica Linha
						bool checkLine(int x);
					// Verifica Coluna
						bool checkColumn(int y);
					// Verifica a troca
						bool checkSwitch(int x1, int y1, int x2, int y2);
					// Verifica após a troca
						bool checkAfter(int maxX, int * v, int n);


				void print() const; // Função para imprimir a matriz

		};

#endif