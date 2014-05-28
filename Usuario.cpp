#include "Usuario.h"

Usuario::Usuario() { pontuacao = 0; }
Usuario::Usuario(string str) {
	nome = str;
	pontuacao = 0;
}

string Usuario::getNome() const { return nome; }
int Usuario::getPontuacao() const { return pontuacao; }
void Usuario::setPontuacao(int p) { pontuacao += p; }
