#include "Usuario.h"

Usuario::Usuario() { 
	pontuacao = 0;
	//Initialize the string
    nome = "";
    //Enable Unicode
    SDL_EnableUNICODE( SDL_ENABLE );
}

Usuario::Usuario(string str) {
	nome = str;
	pontuacao = 0;
}

Usuario::~Usuario() {
	//Free the old surface
    SDL_FreeSurface( text );

    //Disable Unicode
    SDL_EnableUNICODE( SDL_DISABLE );
}

void Usuario::reload() {
	pontuacao = 0;
	//Initialize the string
    nome = "";
}

string Usuario::getNome() const { return nome; }

int Usuario::getPontuacao() const { return pontuacao; }

void Usuario::setPontuacao(int p) { pontuacao = p; }

SDL_Surface * Usuario::handleInput(SDL_Event &event, TTF_Font *font, SDL_Color textColor) {
	//If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Keep a copy of the current version of the string
        std::string temp = nome;

        //If the string less than maximum size
        if( temp.length() <= 16 )
        {
            //If the key is a space
            if( event.key.keysym.unicode == (Uint16)' ' )
            {
                //Append the character
                nome += (char)event.key.keysym.unicode;
            }
            //If the key is a number
            else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                nome += (char)event.key.keysym.unicode;
            }
            //If the key is a uppercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                nome += (char)event.key.keysym.unicode;
            }
            //If the key is a lowercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                nome += (char)event.key.keysym.unicode;
            }
        }

        //If backspace was pressed and the nomeing isn't blank
        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( nome.length() != 0 ) )
        {
            //Remove a character from the end
            nome.erase( nome.length() - 1 );
        }

        //If the string was changed
        if( nome != temp )
        {
            //Free the old surface
            SDL_FreeSurface( text );

            //Render a new text surface
            text = TTF_RenderText_Solid( font, nome.c_str(), textColor );
    		
    		return text;
        }
    }
    return NULL;
}