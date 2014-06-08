#ifndef _USUARIO_H_
	#define _USUARIO_H_
		
		#include <iostream>
		#include <string>

		using std::string;

		class Usuario {
			string nome;
			int pontuacao;
			public:
				Usuario();
				Usuario(string str);
				~Usuario();
				void reload();
				string getNome() const;
				int getPontuacao() const;
				void setPontuacao(int p);
		};

#endif