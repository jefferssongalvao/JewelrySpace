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

				void imprimir() const; // Função para imprimir a matriz

		};

#endif