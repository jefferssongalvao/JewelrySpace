#ifndef _USUARIO_H_
	#define _USUARIO_H_
		
		#include <iostream>
		#include <string>
		#include <SDL/SDL.h> //para manipulação de eventos e interface
		#include <SDL/SDL_ttf.h> //para mostrar textos

		using std::string;

		class Usuario {
			string nome;
			int pontuacao;
			SDL_Surface *text;
			//Fonte a ser usada
            TTF_Font *font;
            //Cor da fonte (branco)
            SDL_Color textColor;

			public:
				Usuario();
				Usuario(string str);
				~Usuario();
				void reload();
				string getNome() const;
				int getPontuacao() const;
				void setPontuacao(int p);
				SDL_Surface * handleInput(SDL_Event &event);
		};

#endif