#ifndef _TELA_H_
	#define _TELA_H_

		#include <iostream> // biblioteca padrão i/o do c++
		#include <cstdlib> // para uso da função rand()
		#include <ctime> // para uso da função rand()
		#include <string> // para o nome do usuário do jogo
		#include <cmath> //para calcular módulo
        #include <SDL/SDL.h> //para manipulação de eventos e interface
        #include <SDL/SDL_image.h> //para manipulação de imagens
		#include <SDL/SDL_mixer.h> //para manipulação de audio

		#include "Usuario.h" // Inclusão da Biblioteca da Classe
		#include "Pilha.h" // Inclusão da Biblioteca da Classe
		#include "Ponto.h" // Inclusão da Biblioteca da Classe
        #include "Gems.h" // Inclusão da Biblioteca da Classe

		//Tamanho da Tela
        const int linhasMatriz = 8; //Mexi aqui pra corrigir -|-
        const int colunasMatriz = 8;

        //Atributos da tela
        const int SCREEN_WIDTH = 1000;
        const int SCREEN_HEIGHT = 700;
        const int SCREEN_BPP = 32;

        //Atributos de uma celula (tamanho de uma célula)
        const int CELULA_WIDHT = 60;
        const int CELULA_HEIGHT = 60;

        //Atributos da matriz (posição da tela onde colocar a matriz)
        const int MAT_INITIAL_POINT_X = 300;
        const int MAT_INITIAL_POINT_Y = 120;

        //Constantes para mixagem do audio
        const int AUDIO_RATE = 44100;
  		const int AUDIO_CHANNELS = 2;
  		const int AUDIO_BUFFERS = 1024;

		const int FPS = 60;

        //Enumeração para representar joias
        enum { YELLOW, WHITE, BLUE, RED, PURPLE, ORANGE, GREEN, BLANK };

		using std::cout; // inclusão do metódo cout do namespace std
		using std::string; // inclusão da classe string da STL

		class Tela {

            Gems matriz[linhasMatriz][colunasMatriz]; //Matriz de joias

			int qtdElementos;
			int bonus; // peça que será considerada ponto dobrado.
			int level; // qual a fase o jogador está no momento
			bool changedLevel; // variavel que determinará que uma fase foi alterada
			bool audio; //variavel para desligar/ligar a music

			Pilha * pontos; // pontos que foram marcados após um movimento

            Usuario * user;

            Ponto dica;

			public:

            //Superficies
            SDL_Surface *gems;
            SDL_Surface *gems_on;
            SDL_Surface *screen;

            //Cortes da figura (teremos oito joias)
            SDL_Rect clipsGems[9];
            SDL_Rect clipsGems_on[9];

			/* Mix_Music actually holds the music information.  */
			Mix_Music *music;

            SDL_Event event;

				Tela(); // Construtor Padrão
				void fillMatriz(int n);
				void setrects(SDL_Rect * rects, int x, int y);
				// metódo GET
					int getElement(int x, int y) const;
					int getPontuacao() const;
					Ponto getDica() const;
					void getBonus() const;
					int getLevel() const;
				// metódo SET
					void setElement(int x, int y, int element);
					void setUsuario(string str);

				void switchElements(int x1, int y1, int x2, int y2); // troca elementos de posição
				void moveElement(int * cols, int n); // Movimento de elementos após pontuar
				int point(); // Sistema de pontuação

				// Verifica se tem combinações (3 ou mais peças) possíveis
					// Verifica Linha
						bool checkLine(int x);
					// Verifica Coluna
						bool checkColumn(int y);
					// Verifica a troca
						bool checkSwitch(int x1, int y1, int x2, int y2);
					// Verifica após a troca
						bool checkAfter(int maxX, int * v, int n);

				bool saoAdjacentes(int x1, int y1, int x2, int y2);

                void initializeGem(int x, int y, int codigo);

                void setClip(int x, int y, int cod);

                void contrastItem(int x, int y, int cod);

                SDL_Surface* load_image(string filename);

                bool load_files();

                void clean_up();

                void set_clips(SDL_Rect *clips);

                bool init();

                void handle_events();

                void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);//, SDL_Rect* clip);

                void showGame(); // Função para começar o jogo

                void showScreen();

                bool testMove(); // Algoritmos que buscará as possível jogadas
                bool changeLevel(); //  para mudança das fases
                void print();
		};

#endif
