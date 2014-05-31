#include <iostream> // biblioteca padrão I/O do C++
#include <cstdlib> // para uso do system clear
#include <string> // para o nome do usuário do jogo
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Usuario.h"
#include "Tela.h" // Inclusão da Biblioteca da Classe
#include "Pilha.h"
#include "Ponto.h"

using std::cout;
using std::cin;
using std::string;

int main() {

    Tela * jogo = new Tela();

    string str; // para o nome do usuario
    cout << "Digite o seu nome: ";
    getline(cin, str);

    jogo->setUsuario(str);

    system("clear");

    //Quit flag
    bool quit = false;

    //Initialize
    if( jogo->init() == false )
    {
        return 1;
    }

    //Load the files
    if( jogo->load_files() == false )
    {
        return 1;
    }

    //Inicia o jogo
    jogo->handle_events();
    
    //Clean up
    jogo->clean_up();

    std::cout << "Sua pontuacao foi: " << jogo->getPontuacao() << std::endl;

    delete jogo;

	return 0;
}