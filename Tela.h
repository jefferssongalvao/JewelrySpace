#ifndef _TELA_H_
	#define _TELA_H_

		#define eixoX 8
		#define eixoY 8

		class Tela {
			int matriz[eixoX][eixoY];
			int qtdElementos;
			public:
				Tela();
				~Tela();
				void imprimir() const;

		};

#endif