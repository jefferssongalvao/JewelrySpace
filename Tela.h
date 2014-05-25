#ifndef _TELA_H_
	#define _TELA_H_

		//Tamanho da Tela
			#define eixoX 8
			#define eixoY 8

		class Tela {
			int matriz[eixoX][eixoY];
			public:
				Tela(); // Construtor Padrão
				Tela(int qtdElementos); // Construtor com Parâmetros (serve para construir novas fases)

				// metódo GET
					int getElement(int x, int y) const;
				// metódo SET
					void setElement(int x, int y, int element);

				void switchElements(int x1, int y1, int x2, int y2); // troca elementos de posição

				// Verifica se tem combinações (3 ou mais peças) possíveis
					// Verifica Linha
						bool checkLine(int x) const;
					// Verifica Coluna
						bool checkColumn(int y) const;
					// Verifica a troca
						bool checkSwitch(int x1, int y1, int x2, int y2);

				void print() const; // Função para imprimir a matriz

		};

#endif