#ifndef _TELA_H_
	#define _TELA_H_

		#include <iostream> // biblioteca padrão i/o do c++
		#include <cstdlib> // para uso da função rand()
        #include <cstdio>
		#include <ctime> // para uso da função rand()
		#include <string> // para o nome do usuário do jogo
		#include <cmath> //para calcular módulo
        #include <SDL/SDL.h> //para manipulação de eventos e interface
        #include <SDL/SDL_image.h> //para manipulação de imagens
		#include <SDL/SDL_mixer.h> //para manipulação de audio
        #include <SDL/SDL_ttf.h> //para mostrar textos
        #include <stack>

		#include "Usuario.h" // Inclusão da Biblioteca da Classe
		#include "Pilha.h" // Inclusão da Biblioteca da Classe
		#include "Ponto.h" // Inclusão da Biblioteca da Classe
        #include "Gems.h" // Inclusão da Biblioteca da Classe
        #include "Undo.h" // Inclusão da Biblioteca da Classe
    

		//Tamanho da Tela
        const int linhasMatriz = 8; //Mexi aqui pra corrigir -|-
        const int colunasMatriz = 8;

        //Atributos da tela
        const int SCREEN_WIDTH = 820;
        const int SCREEN_HEIGHT = 630;
        const int SCREEN_BPP = 32;

        //Atributos de uma celula (tamanho de uma célula)
        const int CELULA_WIDHT = 60;
        const int CELULA_HEIGHT = 60;

        //Atributos da matriz (posição da tela onde colocar a matriz)
        const int MAT_INITIAL_POINT_X = 300;
        const int MAT_INITIAL_POINT_Y = 100;

        //Constantes para mixagem do audio
        const int AUDIO_RATE = 44100;
  		const int AUDIO_CHANNELS = 2;
  		const int AUDIO_BUFFERS = 1024;

		const int FPS = 30;

        //Enumeração para representar joias
        enum { YELLOW, WHITE, BLUE, RED, PURPLE, ORANGE, GREEN, BLANK };

		using std::cout; // inclusão do metódo cout do namespace std
		using std::string; // inclusão da classe string da STL
        using std::stack;

		class Tela {

            Gems matriz[linhasMatriz][colunasMatriz]; //Matriz de joias

			int qtdElementos;
			int bonus; // peça que será considerada ponto dobrado.
			int level; // qual a fase o jogador está no momento
			bool changedLevel; // variavel que determinará que uma fase foi alterada
			bool audio; //variavel para desligar/ligar a music
            stack<Undo> telasAnt;

			Pilha * pontos; // pontos que foram marcados após um movimento

            Usuario * user;

            Ponto dica;

			public:

            //Telas
            SDL_Surface *telaInicial;
            SDL_Surface *telaIdentificacao;
            SDL_Surface *telaInstrucoes;
            SDL_Surface *telaConfigSound_ON;
            SDL_Surface *telaConfigSound_OFF;
            SDL_Surface *telaLevelUp;
            SDL_Surface *telaGameOver;


            //Superficies
            SDL_Surface *gems;
            SDL_Surface *gems_dica;
            SDL_Surface *screen;
            SDL_Surface *fundo;
            //Mensagens
            SDL_Surface *nomeJogador;
            SDL_Surface *pontosJogador;
            //bonus
            SDL_Surface *gemYellow;
            SDL_Surface *gemWhite;
            SDL_Surface *gemBlue;
            SDL_Surface *gemRed;
            SDL_Surface *gemPurple;
            SDL_Surface *gemOrange;
            SDL_Surface *gemGreen;
            // fases
            SDL_Surface *fase1;
            SDL_Surface *fase2;
            SDL_Surface *fase3;
            SDL_Surface *fase4;

            // Botões
            SDL_Surface *hint;

            //Cortes da figura (teremos oito joias)
            SDL_Rect clipsGems[8];
            SDL_Rect clipsGems_dica[8];

			/* Mix_Music actually holds the music information.  */
			Mix_Music *music;

            SDL_Event event;

            //Fonte a ser usada
            TTF_Font *font;
            //Cor da fonte (branco)
            SDL_Color textColor;

				Tela(); // Construtor Padrão
                void reload();
                bool showTelaInicial();
                bool showConfScreen();
                bool showInstrucoes();
                bool showIDscreen();
                void showLevelUp();
                bool showGameOver();
				void fillMatriz(int n);
				void setrects(SDL_Rect * rects, int x, int y);
				// metódo GET
					int getElement(int x, int y) const;
					int getPontuacao() const;
					Ponto getDica() const;
					void getBonus();
					int getLevel() const;
				// metódo SET
					void setElement(int x, int y, int element);
					void setUsuario(string str);

				void switchElements(int x1, int y1, int x2, int y2); // troca elementos de posição
				void moveElement(int * cols, int n); // Movimento de elementos após pontuar
				int point(); // Sistema de pontuação
                void showPontuacao();

				// Verifica se tem combinações (3 ou mais peças) possíveis
					// Verifica Linha
						bool checkLine(int x);
					// Verifica Coluna
						bool checkColumn(int y);
					// Verifica a troca
						void checkSwitch(int x1, int y1, int x2, int y2);
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

                bool playGame();

                void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);//, SDL_Rect* clip);
				void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
                void showGame(); // Função para começar o jogo

                void showScreen();

                bool testMove(); // Algoritmos que buscará as possível jogadas
                void changeLevel(); //  para mudança das fases

                SDL_Surface * carregar_imagem( std::string filename );

                void fillUndo();
                void undoPlay();

		};

#endif
