#include <iostream> // biblioteca padrão I/O do C++
#include "Tela.h" // Inclusão da Biblioteca da Classe

int main() {

    Tela * jogo = new Tela();

    //Initialize
    if( jogo->init() == false ) return 1;

    //Load the files
    if( jogo->load_files() == false ) return 1;

    //jogo->showTelaInicial();
    while(!jogo->showTelaInicial()) {
        if(jogo->showGameOver() == false) {
            jogo->reload();
            continue;
        } else {
            jogo->clean_up();
            break;
        }
    }

    delete jogo;

	return 0;
}