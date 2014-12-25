/* 
 * Usuario.h
 *
 * Estrutura que armazena informações relacionadas com o jogador
 */

#ifndef _USUARIO_H_
#define _USUARIO_H_
		
#include <string>
#include <SDL/SDL.h> 		// para manipulação de eventos e interface
#include <SDL/SDL_ttf.h> 	// para mostrar textos

using std::string;

class Usuario {
	
	string nome;
	int pontuacao;
	SDL_Surface *text;

	public:
		Usuario();
		Usuario(string str);
		void reload();
		string getNome() const;
		int getPontuacao() const;
		void setPontuacao(int p);
		SDL_Surface * handleInput(SDL_Event &event, TTF_Font *font, SDL_Color textColor); // Método responsável pela leitura do nome
		
};

#endif