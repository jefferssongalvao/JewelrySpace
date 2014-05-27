#ifndef _TELA_H_
	#define _TELA_H_

		#include <iostream>
		#include "Pilha.h" // Inclusão da Biblioteca da Classe Pilha

		//Tamanho da Tela
			#define eixoX 8
			#define eixoY 8

		class Tela {
			int matriz[eixoX][eixoY]; // pontos na tela
			int qtdElementos;
			Pilha * pontos; // pontos que foram marcados após um movimento
			Pilha * possibilidades; // possibilidades de pontuação
			public:
				Tela(); // Construtor Padrão
				Tela(int qtdElementos); // Construtor com Parâmetros (serve para construir novas fases)

				// metódo GET
					int getElement(int x, int y) const;
				// metódo SET
					void setElement(int x, int y, int element);

				void switchElements(int x1, int y1, int x2, int y2); // troca elementos de posição

				void moveElement(Ponto ponto); // Movimento de elementos após pontuar

				// Verifica se tem combinações (3 ou mais peças) possíveis
					// Verifica Linha
						bool checkLine(int x);
					// Verifica Coluna
						bool checkColumn(int y);
					// Verifica a troca
						bool checkSwitch(int x1, int y1, int x2, int y2);


				void print() const; // Função para imprimir a matriz

		};

#endif