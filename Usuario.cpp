#include "Usuario.h"

Usuario::Usuario() { 
	pontuacao = 0;
	//Initialize the string
    nome = "";
}

Usuario::Usuario(string str) {
	nome = str;
	pontuacao = 0;
}

Usuario::~Usuario() {}

void Usuario::reload() {
	pontuacao = 0;
	//Initialize the string
    nome = "";
}

string Usuario::getNome() const { return nome; }

int Usuario::getPontuacao() const { return pontuacao; }

void Usuario::setPontuacao(int p) { pontuacao = p; }