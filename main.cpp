#include <iostream> // biblioteca padrão I/O do C++
#include <cstdlib> // para uso do system clear
#include <string> // para o nome do usuário do jogo

#include "Usuario.h"
#include "Tela.h" // Inclusão da Biblioteca da Classe
#include "Pilha.h"
#include "Ponto.h"

using std::cout;
using std::cin;
using std::string;

int main() {

    Tela * jogo = new Tela();

    system("clear");

    //Initialize
    if( jogo->init() == false ) return 1;

    //Load the files
    if( jogo->load_files() == false ) return 1;

    while(!jogo->showTelaInicial()) {
        if(jogo->showGameOver() == false) {
            jogo->clean_up();
            delete jogo;
            Tela * jogo = new Tela();
            //Initialize
            if( jogo->init() == false ) return 1;
            //Load the files
            if( jogo->load_files() == false ) return 1;
            continue;
        } else {
            jogo->clean_up();
        }
    }

    //Inicia o jogo
    //jogo->handle_events();
    
    //Clean up
    //jogo->clean_up();

    //std::cout << "Sua pontuacao foi: " << jogo->getPontuacao() << std::endl;

    delete jogo;

	return 0;
}