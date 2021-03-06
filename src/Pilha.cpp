#include <iostream>
#include "Pilha.h"

using std::cout;

// construtor da pilha
Pilha::Pilha() { size = 0; }

// destrutor da pilha
Pilha::~Pilha() {};

Ponto Pilha::pop() {
	if (size) {
		size--;
		return ponto[size];
	} else {
		cout << "Pilha esta vazia!\n";
	}
}

void Pilha::push(Ponto element) {
	if (size < max) {
		ponto[size] = element;
		size++;
	} else {
		cout << "Pilha esta cheia!\n";
	}
}

void Pilha::clearStack() { 
	size = 0; 
}

void Pilha::setSize(int n) { 
	if(size >= n) {
		 size -= n;
	}
}

int Pilha::getSize() { 
	return size;
}