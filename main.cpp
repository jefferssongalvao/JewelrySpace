#include <iostream> // biblioteca padrão I/O do C++
#include <cstdlib> // para uso do system clear

#include "Tela.h" // Inclusão da Biblioteca da Classe

using namespace std;

int main() {
	
	Tela * jogo = new Tela();
	int x1, y1, x2, y2;

	jogo->print();
	
	while(cin >> x1 >> y1) {
		if(x1 < 0 || y1 < 0) break;

		cin >> x2 >> y2;
		
		system("clear");
		if(jogo->checkSwitch(x1, y1, x2, y2)) cout << "Pontos marcados!\n"; else cout << "Movimento inválido\n";

		jogo->print();
	}

	delete jogo;

	return 0;
}