#include "Usuario.h"

Usuario::Usuario() { 
	pontuacao = 0;
    nome = "";
    SDL_EnableUNICODE( SDL_ENABLE );
}

Usuario::Usuario(string str) {
	nome = str;
	pontuacao = 0;
}

void Usuario::reload() {
	pontuacao = 0;
    nome = "";
}

string Usuario::getNome() const { return nome; }

int Usuario::getPontuacao() const { return pontuacao; }

void Usuario::setPontuacao(int p) { pontuacao = p; }

/* Método responsável pela leitura do nome do jogador. Retorna uma surface temporária que será usada pela exibir o nome que está sendo digitado */
SDL_Surface * Usuario::handleInput(SDL_Event &event, TTF_Font *font, SDL_Color textColor) {

    if( event.type == SDL_KEYDOWN )
    {
        //Cria uma cópia da string
        std::string temp = nome;

        //O maximo de caracteres é 16
        if( temp.length() <= 16 )
        {
            //Espaço
            if( event.key.keysym.unicode == (Uint16)' ' )
            {
                //Inclui este caractere
                nome += (char)event.key.keysym.unicode;
            }
            //Numero
            else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Inclui este caractere
                nome += (char)event.key.keysym.unicode;
            }
            //Letra maiuscula
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Inclui este caractere
                nome += (char)event.key.keysym.unicode;
            }
            //Letra minuscula
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Inclui este caractere
                nome += (char)event.key.keysym.unicode;
            }
        }

        //Se o backspace foi pressionado e a string não está vazia
        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( nome.length() != 0 ) )
        {
            //Remove o caractere do final
            nome.erase( nome.length() - 1 );
        }

        //Se a string foi alterada
        if( nome != temp )
        {
            //Libera superficie antiga
            SDL_FreeSurface( text );

            //Cria uma nova superficie com o nome atual
            text = TTF_RenderText_Solid( font, nome.c_str(), textColor );
    		
    		return text;
        }
    }
    return NULL;
}