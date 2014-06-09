//Estrutura responsável por guardar telas de jogadas, para fazer o efeito de desfazer uma jogada
#ifndef _UNDO_H_
	#define _UNDO_H_
		typedef struct {
			Gems mat[8][8];
			int pontosAnterior;
		} Undo;
#endif