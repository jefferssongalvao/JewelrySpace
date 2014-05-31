#include "Tela.h" // Inclusão da Biblioteca da Classe

// Construtor Padrão
	Tela::Tela() {

		int elemento, rep;

		qtdElementos = 5;

		srand(time(NULL));

        set_clips();

		pontos = new Pilha();
		for(int i = 0; i < linhasMatriz; i++) {
			rep = 0;
			for(int j = 0; j < colunasMatriz; j++) {
				elemento = (rand() % qtdElementos) + 1;
				if(rep == 0) {
					if(i > 1) {
                        while((matriz[i-1][j].elemento == elemento) && (matriz[i-2][j].elemento == elemento))
							elemento = (rand() % qtdElementos) + 1;
					}
                    if(j > 0 && matriz[i][j-1].elemento == elemento) rep++;
				} else {
					if(i > 1) {
                        while(matriz[i-1][j].elemento == elemento && matriz[i-2][j].elemento == elemento || matriz[i][j-1].elemento == elemento)
							elemento = (rand() % qtdElementos) + 1;
					} else {
                        while(matriz[i][j-1].elemento == elemento)
							elemento = (rand() % qtdElementos) + 1;
					}
					rep = 0;
				}
                initializeGem(i, j, elemento);
			}
		}
	}

// Construtor com Parâmetros
	Tela::Tela(int qtd) {

		int elemento, rep;

		qtdElementos = qtd;
		
		pontos = new Pilha();

		srand(time(NULL));

        set_clips();

		for(int i = 0; i < linhasMatriz; i++) {
			rep = 0;
			for(int j = 0; j < colunasMatriz; j++) {
				elemento = (rand() % qtdElementos) + 1;
				if(rep == 0) {
					if(i > 1) {
                        while(matriz[i-1][j].elemento == elemento && matriz[i-2][j].elemento == elemento)
							elemento = (rand() % qtdElementos) + 1;
					}
                    if(j > 0 && matriz[i][j-1].elemento == elemento) rep++;
				} else {
					if(i > 1) {
                        while(matriz[i-1][j].elemento == elemento && matriz[i-2][j].elemento == elemento || matriz[i][j-1].elemento == elemento)
							elemento = (rand() % qtdElementos) + 1;
					} else {
                        while(matriz[i][j-1].elemento == elemento)
							elemento = (rand() % qtdElementos) + 1;
					}
					rep = 0;
				}
                initializeGem(i, j, elemento);
			}
		}
	}

// metódo GET
    int Tela::getElement(int x, int y) const { return matriz[x][y].elemento; }
    int Tela::getPontuacao() const { return user->getPontuacao(); }
// metódo SET
    void Tela::setElement(int x, int y, int element) { setClip(x, y, element); }
	void Tela::setUsuario(string str) { user = new Usuario(str); }

 // troca elementos de posição
	void Tela::switchElements(int x1, int y1, int x2, int y2) {
		int aux = getElement(x1, y1);
		setElement(x1, y1, getElement(x2, y2));
		setElement(x2, y2, aux);
	}

// Movimento de elementos após pontuar
	void Tela::moveElement(Ponto ponto) {
		int elemento;

		if(ponto.x == 0) {
			elemento = (rand() % qtdElementos) + 1;
			setElement(ponto.x, ponto.y, elemento);	
			return;
		}

		elemento = getElement(ponto.x-1, ponto.y);
		setElement(ponto.x--, ponto.y, elemento);
		moveElement(ponto);
	}

// Sistema de pontuação
	int Tela::point() {
		int maiorX = 0, cols[8], i = 0, pontuacao = 0;
		bool dif, check = true;
		Ponto ponto;

		while(check){
			// cout << "\nAntes de pontuar: \n"; print();
			while(pontos->getSize()) {
				pontuacao += 5;
				ponto = pontos->pop();
				if(ponto.x > maiorX) maiorX = ponto.x;
				dif = true;
				for(int j = 0; j < i; j++) {
					if(cols[j] == ponto.y) dif = false;
				}
				if(dif) cols[i++] = ponto.y;
				moveElement(ponto);
			}
			showScreen();
			SDL_Delay(1000);
			// cout << "\nDepois de pontuar: \n"; print();
			check = checkAfter(maiorX, cols, i);
		}

		return pontuacao;

	}

// Verifica se tem combinações (3 ou mais peças) possíveis
	// Verifica Linha
		bool Tela::checkLine(int x) {
			
			int elemento = getElement(x, 0), cont = 1;
			bool flag = false;
			Ponto ponto;

			ponto.x = x;
			ponto.y = 0;

			pontos->push(ponto);

			for (int i = 1; i <= linhasMatriz; ++i) {
				if(i == linhasMatriz){
					if(cont > 2)
						flag = true;
					else {
						pontos->setSize(cont);
					}
				} else {
					if(elemento == getElement(x, i)) {
						ponto.x = x;
						ponto.y = i;

						pontos->push(ponto);

						cont++;
					} else {
						if(cont > 2)
							flag = true;
						else {
							pontos->setSize(cont);
						}
						ponto.x = x;
						ponto.y = i;
						pontos->push(ponto);

						elemento = getElement(x, i);
						cont = 1;
					}					
				}
			}
			return flag;
		}
	// Verifica Coluna
		bool Tela::checkColumn(int y) {
			int elemento = getElement(linhasMatriz-1, y), cont = 1;
			bool flag = false;
			Ponto ponto;

			ponto.x = linhasMatriz-1;
			ponto.y = y;
			pontos->push(ponto);

			for (int i = linhasMatriz-2; i >= -1; --i) {
				if(i < 0){
					if(cont > 2)
						flag = true;
					else {
						pontos->setSize(cont);
					}
				} else {
					if(elemento == getElement(i, y)) {
						ponto.x = i;
						ponto.y = y;

						pontos->push(ponto);

						cont++;
					} else {
						if(cont > 2)
							flag = true;
						else {
							pontos->setSize(cont);
						}
						ponto.x = i;
						ponto.y = y;
						pontos->push(ponto);

						elemento = getElement(i, y);
						cont = 1;
					}
				}
			}
			return flag;
		}

	//Checa se duas células são adjacentes
		bool Tela::saoAdjacentes(int x1, int y1, int x2, int y2) {
			return (((x1 - x2 == 0) || (y1 - y2 == 0)) && ((abs(x1 - x2) == 1) || (abs(y1 - y2) == 1)));
		}

	// Verifica a troca
		bool Tela::checkSwitch(int x1, int y1, int x2, int y2) {	
				bool flag = false;

				switchElements(x1, y1, x2, y2);
				apply_surface(x1, y1, gems, screen);
                SDL_UpdateRect(screen, matriz[x1][y1].celula.x, matriz[x1][y1].celula.y, matriz[x1][y1].celula.w, matriz[x1][y1].celula.h);
                apply_surface(x2, y2, gems, screen);
                SDL_UpdateRect(screen, matriz[x2][y2].celula.x, matriz[x2][y2].celula.y, matriz[x2][y2].celula.w, matriz[x2][y2].celula.h);
				SDL_Delay(1000);

				if(checkLine(x1)) flag = true;
				if(checkColumn(y1)) flag = true;
				if(x1 != x2 && checkLine(x2)) flag = true;
				if(y1 != y2 && checkColumn(y2)) flag = true;
				
				if(flag) {
					int novosPontos = point();
					
					cout << "Marcou " << novosPontos << " pontos.\n"; // Monta a pontuação

					user->setPontuacao(novosPontos);

					return true;
				}

				switchElements(x2, y2, x1, y1);
				
                apply_surface(x2, y2, gems, screen);
                SDL_UpdateRect(screen, matriz[x2][y2].celula.x, matriz[x2][y2].celula.y, matriz[x2][y2].celula.w, matriz[x2][y2].celula.h);
				apply_surface(x1, y1, gems, screen);
                SDL_UpdateRect(screen, matriz[x1][y1].celula.x, matriz[x1][y1].celula.y, matriz[x1][y1].celula.w, matriz[x1][y1].celula.h);
				SDL_Delay(250);

				return false;
		}
	// Verifica após a troca
		bool Tela::checkAfter(int maxX, int * v, int n) {
			bool flag = false;
			for (int i = 0; i <= maxX; ++i)
				if(checkLine(i)) flag = true;
			for (int i = 0; i < n; ++i)
				if(checkColumn(v[i])) flag = true;
			return flag;
		}

        void Tela::initializeGem(int x, int y, int codigo) {
            //Define os atributos de uma celulas (posição e tamanho)
            matriz[x][y].celula.x = MAT_INITIAL_POINT_X + (y * CELULA_WIDHT);
            matriz[x][y].celula.y = MAT_INITIAL_POINT_Y + (x * CELULA_HEIGHT);
            matriz[x][y].celula.w = CELULA_WIDHT;
            matriz[x][y].celula.h = CELULA_HEIGHT;
            matriz[x][y].elemento = codigo;
            setClip(x, y, codigo);
        }

        void Tela::setClip(int x, int y, int cod) {
            switch(cod) {
                case 1:
                    matriz[x][y].clip = &clips[ RED ];
                    matriz[x][y].elemento = cod;
                    break;
                case 2:
                    matriz[x][y].clip = &clips[ WHITE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 3:
                    matriz[x][y].clip = &clips[ GREEN ];
                    matriz[x][y].elemento = cod;
                    break;
                case 4:
                    matriz[x][y].clip = &clips[ BLUE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 5:
                    matriz[x][y].clip = &clips[ GRAY ];
                    matriz[x][y].elemento = cod;
                    break;
                case 6:
                    matriz[x][y].clip = &clips[ PURPLE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 7:
                    matriz[x][y].clip = &clips[ YELLOW ];
                    matriz[x][y].elemento = cod;
                    break;
                case 8:
                    matriz[x][y].clip = &clips[ ORANGE ];
                    matriz[x][y].elemento = cod;
            }
        }

        SDL_Surface* Tela::load_image(string filename) {
            //The image that's loaded
            SDL_Surface* loadedImage = NULL;

            //The optimized surface that will be used
            SDL_Surface* optimizedImage = NULL;

            //Load the image
            loadedImage = IMG_Load( filename.c_str() );

            //If the image loaded
            if( loadedImage != NULL )
            {
                //Create an optimized surface
                optimizedImage = SDL_DisplayFormat( loadedImage );

                //Free the old surface
                SDL_FreeSurface( loadedImage );

                //If the surface was optimized
                if( optimizedImage != NULL )
                {
                    //Color key surface
                    SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
                }
            }

            //Return the optimized surface
            return optimizedImage;
        }

        bool Tela::load_files() {
            //Load the button sprite sheet
            gems = load_image( "gems.png" );

            //If there was a problem in loading the button sprite sheet
            if( gems == NULL )
            {
                return false;
            }

            //If everything loaded fine
            return true;
        }

        void Tela::clean_up() {
            //Free the surface
            SDL_FreeSurface( gems );

            //Quit SDL
            SDL_Quit();
        }

        bool Tela::init() {
            //Initialize all SDL subsystems
            if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return false;

            //Set up the screen
            screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

            //If there was an error in setting up the screen
            if( screen == NULL ) return false;

            //Set the window caption
            SDL_WM_SetCaption( "Bejeweled", NULL );

            //If everything initialized fine
            return true;
        }

        void Tela::set_clips() {

            //Clip the sprite sheet
            clips[ RED ].x = 0;
            clips[ RED ].y = 0;
            clips[ RED ].w = CELULA_WIDHT;
            clips[ RED ].h = CELULA_HEIGHT;

            clips[ WHITE ].x = 65;
            clips[ WHITE ].y = 0;
            clips[ WHITE ].w = CELULA_WIDHT;
            clips[ WHITE ].h = CELULA_HEIGHT;

            clips[ GREEN ].x = 130;
            clips[ GREEN ].y = 0;
            clips[ GREEN ].w = CELULA_WIDHT;
            clips[ GREEN ].h = CELULA_HEIGHT;

            clips[ BLUE ].x = 0;
            clips[ BLUE ].y = 60;
            clips[ BLUE ].w = CELULA_WIDHT;
            clips[ BLUE ].h = CELULA_HEIGHT;

            clips[ GRAY ].x = 65;
            clips[ GRAY ].y = 60;
            clips[ GRAY ].w = CELULA_WIDHT;
            clips[ GRAY ].h = CELULA_HEIGHT;

            clips[ PURPLE ].x = 130;
            clips[ PURPLE ].y = 60;
            clips[ PURPLE ].w = CELULA_WIDHT;
            clips[ PURPLE ].h = CELULA_HEIGHT;

            clips[ YELLOW ].x = 0;
            clips[ YELLOW ].y = 120;
            clips[ YELLOW ].w = CELULA_WIDHT;
            clips[ YELLOW ].h = CELULA_HEIGHT;

            clips[ ORANGE ].x = 65;
            clips[ ORANGE ].y = 120;
            clips[ ORANGE ].w = CELULA_WIDHT;
            clips[ ORANGE ].h = CELULA_HEIGHT;
        }

        void Tela::handle_events() {
		    Ponto p1 = {-1, -1}, p2 = {-1, -1};
		    bool quit = false;
		    showGame();
		    while( (quit == false) ) {
		        if( SDL_PollEvent( &event ) ) {

		            Ponto tmp;

		            //If a mouse button was pressed
		            if( event.type == SDL_MOUSEBUTTONDOWN ) {
		                //If the left mouse button was pressed
		                if( event.button.button == SDL_BUTTON_LEFT ) {
		                    //Get the mouse offsets
		                    tmp.x = event.button.x;
		                    tmp.y = event.button.y;
		                    if((tmp.x >= MAT_INITIAL_POINT_X && tmp.x <= MAT_INITIAL_POINT_X + 480) && (tmp.y >= MAT_INITIAL_POINT_Y && tmp.y <= MAT_INITIAL_POINT_Y + 480)) {
			                    tmp.x = (tmp.x - MAT_INITIAL_POINT_X) / 60;
			                    tmp.y = (tmp.y - MAT_INITIAL_POINT_Y) / 60;
				                if(p1.x < 0) {
				                    p1.x = tmp.y; //Precisa ser invertido
				                    p1.y = tmp.x;
				                } else if(p2.x < 0) {
				                	if(saoAdjacentes(p1.x, p1.y, tmp.y, tmp.x)) {
					                    p2.x = tmp.y; //Precisa ser invertido
					                    p2.y = tmp.x;
				                	} else {
				                		//Ignora selecao
				                		p1.x = tmp.y;
						                p1.y = tmp.x;
				                	}
				                }
		                    }
		                }
		            } else if( event.type == SDL_QUIT ) {
		                //Quit the program
		                quit = true;
	            	}
		    	}
            	if((p1.x >= 0) && (p2.x >= 0)) {
		            if(checkSwitch(p1.x, p1.y, p2.x, p2.y)) {
		                cout << "Pontos marcados!\n";
		                p1.x = -1;
		                p1.y = -1;
		                p2.x = -1;
		                p2.y = -1;
		            } else {
		            	cout << "Movimento inválido\n";
		            	p1.x = -1;
		                p1.y = -1;
		                p2.x = -1;
		                p2.y = -1;
		            }
		        }
			}
		}

        void Tela::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
            SDL_Rect offset;
            offset.x = matriz[x][y].celula.x;
            offset.y = matriz[x][y].celula.y;
            SDL_BlitSurface( source, matriz[x][y].clip, destination, &offset ); //Blitagem
        }

        // Função para começar o jogo
            void Tela::showGame() {
                SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
                //Mostra a tela do jogo
                for(int i = 0; i < linhasMatriz; i++)
                    for(int j = 0; j < colunasMatriz; j++) {
                        apply_surface(i, j, gems, screen);
                        if( SDL_Flip( screen ) == -1 )
                            return;
                        SDL_Delay(25);
                    }
            }

            void Tela::showScreen() {
                SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
                //Mostra a tela do jogo
                for(int i = 0; i < linhasMatriz; i++)
                    for(int j = 0; j < colunasMatriz; j++) {
                        apply_surface(i, j, gems, screen);
                        if( SDL_Flip( screen ) == -1 )
                            return;
                    }
            }