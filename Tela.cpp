#include "Tela.h" // Inclusão da Biblioteca da Classe

// Construtor Padrão
	Tela::Tela() {
        //load_files();
        set_clips(clipsGems);
        set_clips(clipsGems_on);
		pontos = new Pilha();
		level = 1;
		changedLevel = true;
		fillMatriz(5);
	}

	void Tela::fillMatriz(int n) {
		int elemento, rep;
		srand(time(NULL));
		qtdElementos = n;
		bonus = (rand() % qtdElementos);
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

// metódo GET
    int Tela::getElement(int x, int y) const { return matriz[x][y].elemento; }
    int Tela::getPontuacao() const { return user->getPontuacao(); }
    Ponto Tela::getDica() const { return dica; }
    void Tela::getBonus() const {
    	switch(bonus) {
    		case RED:
	            cout << "O bonus é a peça Vermelha.\n";
    			break;
    		case WHITE:
	            cout << "O bonus é a peça Branca.\n";
    			break;
    		case GREEN:
	            cout << "O bonus é a peça Verde.\n";
    			break;
    		case BLUE:
	            cout << "O bonus é a peça Azul.\n";
    			break;
    		case GRAY:
	            cout << "O bonus é a peça Cinza.\n";
    			break;
    		case PURPLE:
	            cout << "O bonus é a peça Roxa.\n";
    			break;
    		case YELLOW:
	            cout << "O bonus é a peça Amarela.\n";
    			break;
    		case ORANGE:
	            cout << "O bonus é a peça Laranja.\n";
    			break;
    	}
    }
    int Tela::getLevel() const { return level; }
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
		int maiorX = 0, cols[8], i = 0, pontuacao = 0, elemento;
		bool dif, check = true;
		Ponto ponto;

		while(check){
			while(pontos->getSize()) {
				ponto = pontos->pop();
				elemento = getElement(ponto.x, ponto.y);
				if(elemento-1 == bonus) 
					pontuacao += 10;
				else
					pontuacao += 5;
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
                    matriz[x][y].clip = &clipsGems[ RED ];
                    matriz[x][y].elemento = cod;
                    break;
                case 2:
                    matriz[x][y].clip = &clipsGems[ WHITE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 3:
                    matriz[x][y].clip = &clipsGems[ GREEN ];
                    matriz[x][y].elemento = cod;
                    break;
                case 4:
                    matriz[x][y].clip = &clipsGems[ BLUE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 5:
                    matriz[x][y].clip = &clipsGems[ GRAY ];
                    matriz[x][y].elemento = cod;
                    break;
                case 6:
                    matriz[x][y].clip = &clipsGems[ PURPLE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 7:
                    matriz[x][y].clip = &clipsGems[ YELLOW ];
                    matriz[x][y].elemento = cod;
                    break;
                case 8:
                    matriz[x][y].clip = &clipsGems[ ORANGE ];
                    matriz[x][y].elemento = cod;
            }
        }

        void Tela::contrastItem(int x, int y, int cod) {
            switch(cod) {
                case 1:
                    matriz[x][y].clip = &clipsGems_on[ RED ];
                    break;
                case 2:
                    matriz[x][y].clip = &clipsGems_on[ WHITE ];
                    break;
                case 3:
                    matriz[x][y].clip = &clipsGems_on[ GREEN ];
                    break;
                case 4:
                    matriz[x][y].clip = &clipsGems_on[ BLUE ];
                    break;
                case 5:
                    matriz[x][y].clip = &clipsGems_on[ GRAY ];
                    break;
                case 6:
                    matriz[x][y].clip = &clipsGems_on[ PURPLE ];
                    break;
                case 7:
                    matriz[x][y].clip = &clipsGems_on[ YELLOW ];
                    break;
                case 8:
                    matriz[x][y].clip = &clipsGems_on[ ORANGE ];
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

            gems_on = load_image( "gems_on.png" );

            //If there was a problem in loading the button sprite sheet
            if( (gems == NULL) || (gems_on == NULL))
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

        void Tela::set_clips(SDL_Rect *clips) {

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
            if(testMove() == false) quit = true;
		    while( (quit == false) ) {
		    	if(changeLevel())
		    		cout << "Você acabou de mudar para a fase " << getLevel() << ".\n";
		        if( SDL_PollEvent( &event ) ) {

		            Ponto tmp;

		            //If the left mouse button was pressed
		            if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
	                    //Get the mouse offsets
	                    tmp.x = event.button.x;
	                    tmp.y = event.button.y;
	                    if((tmp.x >= MAT_INITIAL_POINT_X && tmp.x <= MAT_INITIAL_POINT_X + 480) && (tmp.y >= MAT_INITIAL_POINT_Y && tmp.y <= MAT_INITIAL_POINT_Y + 480)) {
		                    tmp.x = (tmp.x - MAT_INITIAL_POINT_X) / 60;
		                    tmp.y = (tmp.y - MAT_INITIAL_POINT_Y) / 60;
			                if(p1.x < 0) {
			                    p1.x = tmp.y; //Precisa ser invertido
			                    p1.y = tmp.x;
			                    contrastItem(p1.x, p1.y, matriz[p1.x][p1.y].elemento);
			                    apply_surface(p1.x, p1.y, gems_on, screen);
                				SDL_UpdateRect(screen, matriz[p1.x][p1.y].celula.x, matriz[p1.x][p1.y].celula.y, matriz[p1.x][p1.y].celula.w, matriz[p1.x][p1.y].celula.h);
			                } else if(p2.x < 0) {
			                	if(saoAdjacentes(p1.x, p1.y, tmp.y, tmp.x)) {
				                    p2.x = tmp.y; //Precisa ser invertido
				                    p2.y = tmp.x;
			                	} else {
			                		//Ignora selecao
			                		//Tira o destaque da joia que tinha sido selecionada
			                		contrastItem(p1.x, p1.y, matriz[p1.x][p1.y].elemento);
			        				apply_surface(p1.x, p1.y, gems, screen);
                					SDL_UpdateRect(screen, matriz[p1.x][p1.y].celula.x, matriz[p1.x][p1.y].celula.y, matriz[p1.x][p1.y].celula.w, matriz[p1.x][p1.y].celula.h);
			                		p1.x = tmp.y;
					                p1.y = tmp.x;
					                //Destaca a nova joia selecionada
					                contrastItem(p1.x, p1.y, matriz[p1.x][p1.y].elemento);
			                    	apply_surface(p1.x, p1.y, gems_on, screen);
                					SDL_UpdateRect(screen, matriz[p1.x][p1.y].celula.x, matriz[p1.x][p1.y].celula.y, matriz[p1.x][p1.y].celula.w, matriz[p1.x][p1.y].celula.h);
			                	}
			                }
	                    }
	                //Se o usuario fechar a janela ou apertar a tecla ESC
		            } else if( (event.type == SDL_QUIT)  || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
		                //Quit the program
		                quit = true;
	            	}
		    	}
            	if((p1.x >= 0) && (p2.x >= 0)) {
		            if(checkSwitch(p1.x, p1.y, p2.x, p2.y)) {
		                cout << "Pontos marcados!\n";
		            } else {
		            	cout << "Movimento inválido\n";
		            }
		            contrastItem(p1.x, p1.y, matriz[p1.x][p1.y].elemento);
			        apply_surface(p1.x, p1.y, gems, screen);
                	SDL_UpdateRect(screen, matriz[p1.x][p1.y].celula.x, matriz[p1.x][p1.y].celula.y, matriz[p1.x][p1.y].celula.w, matriz[p1.x][p1.y].celula.h);
	                p1.x = -1;
	                p1.y = -1;
	                p2.x = -1;
	                p2.y = -1;
		            if(testMove() == false) 
		            	cout << "Sem mais movimentos possíveis!\n";
		            else {
		            	Ponto p = getDica();
		            	// mostra uma dica temporário no código, será acionado ao apertar um botão
		            		cout << "Dica: (" << p.x << "," << p.y << ")\n";
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
	            getBonus();
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
    // Algoritmos que buscará as possível jogadas, ele também guarda uma coordenada de dica de ponto.
		bool Tela::testMove() {
			for(int i = 0; i < linhasMatriz; i++) {
				for(int j = 0; j < colunasMatriz; j++) {
					for(int k = 1; k <= 4; k++) {
						switch(k) {
							case 1:
								if(i > 0) {
									switchElements(i, j, i-1, j);
									if(checkLine(i) || checkLine(i-1) || checkColumn(j)) {
										switchElements(i-1, j, i, j);
										dica.x = i;
										dica.y = j;
										pontos->clearStack();
										return true;
									}
									switchElements(i-1, j, i, j);
								}
								break;
							case 2:
								if(i < linhasMatriz-1) {
									switchElements(i, j, i+1, j);
									if(checkLine(i) || checkLine(i+1) || checkColumn(j)) {
										switchElements(i+1, j, i, j);
										dica.x = i;
										dica.y = j;
										pontos->clearStack();
										return true;
									}
									switchElements(i+1, j, i, j);
								}
								break;
							case 3:
								if(j > 0) {
									switchElements(i, j, i, j-1);
									if(checkLine(i) || checkColumn(j) || checkColumn(j-1)) {
										switchElements(i, j-1, i, j);
										dica.x = i;
										dica.y = j;
										pontos->clearStack();
										return true;
									}
									switchElements(i, j-1, i, j);
								}
								break;
							case 4:
								if(j < colunasMatriz-1) {
									switchElements(i, j, i, j+1);
									if(checkLine(i) || checkColumn(j) || checkColumn(j+1)) {
										switchElements(i, j+1, i, j);
										dica.x = i;
										dica.y = j;
										pontos->clearStack();
										return true;
									}
									switchElements(i, j+1, i, j);
								}
								break;
						}
					}
				}
			}
			return false;
		}
		bool Tela::changeLevel() {
			if(changedLevel && user->getPontuacao() > 5000 && user->getPontuacao() < 15000) {
				level = 2;
				fillMatriz(6);
				showGame();
				changedLevel = false;
			} else if(!changedLevel && user->getPontuacao() >= 15000 && user->getPontuacao() < 30000) {
				level = 3;
				fillMatriz(7);
				showGame();
				changedLevel = true;
			} else if(changedLevel && user->getPontuacao() >= 30000 && user->getPontuacao() < 50000) {
				level = 4;
				fillMatriz(8);
				showGame();
				changedLevel = false;
			} else if(!changedLevel && user->getPontuacao() >= 50000) { // esse é o zerar do jogo
				level = 5;
				fillMatriz(8);
				showGame();
				changedLevel = true;
			}
		}