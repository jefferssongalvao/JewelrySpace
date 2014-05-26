#ifndef _PILHA_H_
	#define _PILHA_H_
		#include "Ponto.h"
		#define max 64

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
				
		};
		
#endif