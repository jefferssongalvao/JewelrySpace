#include <iostream>
#include "Tela.h" // Inclusão da Biblioteca da Classe

using std::cout;

int main() {

    Tela * jogo = new Tela();

    //Inicializa tudo, encerra a execução do programa se algo der errado
    if( jogo->init() == false ) {
        cout << "Falha na inicialização!\n";
        return 1;
    }

    //Carrega arquivos necessários, encerra a execução do programa se algo der errado
    if( jogo->load_files() == false ) {
        cout << "Falha no carregamento de arquivos!\n";
        return 1;
    }

    //Loop do jogo
    while(!jogo->showTelaInicial()) {
        if(jogo->showGameOver() == false) {
            jogo->reload();
            continue;
        } else {
            jogo->clean_up(); //Libera arquivos e encerra SDLs
            break;
        }
    }

    delete jogo;

	return 0;
}