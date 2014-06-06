#ifndef _PILHA_H_
	#define _PILHA_H_
		#include "Ponto.h"
		#define max 1000

		class Pilha{
			Ponto ponto[max];
			int size;
			public:
				Pilha();
				~Pilha();

				Ponto pop();
				void push(Ponto element);
				void clearStack();

				void setSize(int n);
				int getSize();

				void imprimir();
				
		};
		
#endif