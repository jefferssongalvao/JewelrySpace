#include "Tela.h" // Inclusão da Biblioteca da Classe
#include "quickSort.h" // Inclusão da Biblioteca da Classe

// Construtor Padrão
	Tela::Tela() {
        audio = true;
        textColor = { 255, 255, 255 };
        set_clips(clipsGems);
        set_clips(clipsGems_dica);
        pontos = new Pilha();
        level = 1;
        changedLevel = true;
        fillMatriz(4);
        /*
        ISSO VAI PARA USUARIO
        string str; // para o nome do usuario
        do {
            std::cout << "Digite o seu nome: ";
            getline(std::cin, str);
            if(str.length() > 16) {
                std::cout << "ERRO!\nO seu nome deve conter NO MAXIMO 16 caracteres!\n";
                continue;
            }
            else
                break;
        } while(true);
        setUsuario(str);
        */
        setUsuario("str");
    }

    bool Tela::showTelaInicial() {
        bool quit = false, execute = true;

        while( execute && (quit == false) ) {

        applySurface( 0, 0, telaInicial, screen );
        SDL_Flip( screen );

            if( SDL_PollEvent( &event ) ) {

                Ponto tmp;

                //If the left mouse button was pressed
                if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    //Get the mouse offsets
                    tmp.x = event.button.x;
                    tmp.y = event.button.y;
                    if((tmp.x >= 50 && tmp.x <= 175) && (tmp.y >= 400 && tmp.y <= 530)) {
                        if(showIDscreen())
                            quit = true;
                        else
                            if(playGame())
                                quit = true;
                            else
                                execute = false;
                    } else if((tmp.x >= 50 && tmp.x <= 180) && (tmp.y >= 115 && tmp.y <= 355)) {
                        if(showInstrucoes())
                            quit = true;
                    } else if((tmp.x >= 65 && tmp.x <= 150) && (tmp.y >= 545 && tmp.y <= 623)) {
                        if(showConfScreen())
                            quit = true;
                    }
                } else if( (event.type == SDL_QUIT)  || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                    //Quit the program
                    quit = true;
                }
            }
        }
    if(quit) {
        clean_up();
        return execute;
    } else {
        return quit;
    }
}

    bool Tela::showConfScreen() {
        bool quit = false, execute = true;

        if(audio) {
            applySurface( 0, 0, telaConfigSound_ON, screen );
            SDL_Flip( screen );
        } else {
            applySurface( 0, 0, telaConfigSound_OFF, screen );
            SDL_Flip( screen );
        }

        while( execute ) {

            if( SDL_PollEvent( &event ) ) {
                Ponto tmp;

                //If the left mouse button was pressed
                if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    //Get the mouse offsets
                    tmp.x = event.button.x;
                    tmp.y = event.button.y;
                    if((tmp.x >= 590 && tmp.x <= 645) && (tmp.y >= 100 && tmp.y <= 160)) {
                        execute = false;
                    } else if((tmp.x >= 140 && tmp.x <= 660) && (tmp.y >= 60 && tmp.y <= 580)) {
                        if(audio) {
                            applySurface( 0, 0, telaConfigSound_OFF, screen );
                            SDL_Flip( screen );
                            audio = false;
                            Mix_PauseMusic();
                        } else {
                            applySurface( 0, 0, telaConfigSound_ON, screen );
                            SDL_Flip( screen );
                            audio = true;
                            Mix_ResumeMusic();
                        }
                    }
                } else if( (event.type == SDL_QUIT)  || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                    //Quit the program
                    quit = true;
                    return quit;
                }
            }
        }
        return execute;
    }

    bool Tela::showInstrucoes() {
        bool quit = false, execute = true;

        applySurface( 0, 0, telaInstrucoes, screen );
        SDL_Flip( screen );

        while( execute ) {

            if( SDL_PollEvent( &event ) ) {
                Ponto tmp;

                //If the left mouse button was pressed
                if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    //Get the mouse offsets
                    tmp.x = event.button.x;
                    tmp.y = event.button.y;
                    if((tmp.x >= 590 && tmp.x <= 645) && (tmp.y >= 100 && tmp.y <= 160)) {
                        execute = false;
                    }
                } else if( (event.type == SDL_QUIT)  || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                    //Quit the program
                    quit = true;
                    return quit;
                }
            }
        }
        return execute;
    }

    bool Tela::showIDscreen() {
        bool quit = false, execute = true;

        applySurface( 0, 0, telaIdentificacao, screen );
        SDL_Flip( screen );

        while( execute ) {

            if( SDL_PollEvent( &event ) ) {
                Ponto tmp;

                //If the left mouse button was pressed
                if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    //Get the mouse offsets
                    tmp.x = event.button.x;
                    tmp.y = event.button.y;
                    if((tmp.x >= 660 && tmp.x <= 730) && (tmp.y >= 520 && tmp.y <= 600)) {
                        execute = false;
                    }
                } else if( (event.type == SDL_QUIT)  || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                    //Quit the program
                    quit = true;
                    return quit;
                }
            }
        }
        return execute;
    }

    void Tela::showLevelUp() {
        applySurface( 0, 0, telaLevelUp, screen );
        SDL_Flip( screen );
        SDL_Delay(3000);
    }

    bool Tela::showGameOver() {
        bool quit = false, execute = true;
        char pontVetor[6];

        applySurface( 0, 0, telaGameOver, screen );
        sprintf(pontVetor,"%d",user->getPontuacao());
        pontosJogador = TTF_RenderText_Solid( font, pontVetor, textColor );
        applySurface( 330, 260, pontosJogador, screen );
        SDL_Flip( screen );

        while( execute ) {

            if( SDL_PollEvent( &event ) ) {
                Ponto tmp;

                //If the left mouse button was pressed
                if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                    //Get the mouse offsets
                    tmp.x = event.button.x;
                    tmp.y = event.button.y;
                    if((tmp.x >= 660 && tmp.x <= 730) && (tmp.y >= 520 && tmp.y <= 600)) {
                        execute = false; //Play again
                    } else if((tmp.x >= 90 && tmp.x <= 175) && (tmp.y >= 490 && tmp.y <= 575)) {
                        quit = true;
                        return quit;
                    }
                } else if( (event.type == SDL_QUIT)  || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                    //Quit the program
                    quit = true;
                    return quit;
                }
            }
        }
        return execute;
    }

	void Tela::setrects(SDL_Rect * rects, int x, int y) {
    	for (int i = 0; i < 8; ++i) {
            rects[ i ].x = i*x;
            rects[ i ].y = y;
            rects[ i ].w = CELULA_WIDHT;
            rects[ i ].h = CELULA_HEIGHT;
        }
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
    void Tela::getBonus() {
    	switch(bonus) {
    		case YELLOW:
    			applySurface( 720, 30, gemYellow, screen );
    			break;
    		case WHITE:
    			applySurface( 720, 30, gemWhite, screen );
    			break;
    		case BLUE:
    			applySurface( 720, 30, gemBlue, screen );
    			break;
    		case RED:
    			applySurface( 720, 30, gemRed, screen );
    			break;
    		case PURPLE:
    			applySurface( 720, 30, gemPurple, screen );
    			break;
    		case ORANGE:
    			applySurface( 720, 30, gemOrange, screen );
    			break;
    		case GREEN:
    			applySurface( 720, 30, gemGreen, screen );
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
	void Tela::moveElement(int * cols, int n) {
		SDL_Rect my_rects[64];
		int elemento, cont, qtd = 0, j, lin;
		quickSort(cols, 0, n-1);
		for (int i = 0; i < n; ++i) {
			j = 0;
			while(j < linhasMatriz) {
				elemento = getElement(j, cols[i]);
				if(elemento == 8) {
					lin = j;
					while(lin > 0) {
						elemento = getElement(lin-1, cols[i]);
						setElement(lin, cols[i], elemento);
		                apply_surface(lin, cols[i], gems, screen);
		                my_rects[qtd].x = matriz[lin][cols[i]].celula.x;
		                my_rects[qtd].y = matriz[lin][cols[i]].celula.y;
		                my_rects[qtd].w = matriz[lin][cols[i]].celula.w;
		                my_rects[qtd].h = matriz[lin][cols[i]].celula.h;
		                lin--;
		                qtd++;
					}
					elemento = (rand() % qtdElementos) + 1;
					setElement(lin, cols[i], elemento);
	                apply_surface(lin, cols[i], gems, screen);
	                my_rects[qtd].x = matriz[lin][cols[i]].celula.x;
	                my_rects[qtd].y = matriz[lin][cols[i]].celula.y;
	                my_rects[qtd].w = matriz[lin][cols[i]].celula.w;
	                my_rects[qtd].h = matriz[lin][cols[i]].celula.h;
	                qtd++;
				}
				j++;
				SDL_UpdateRects(screen, qtd, my_rects);
		        SDL_Delay(20);
			}
		}
	}

// Sistema de pontuação
	int Tela::point() {
		int maiorX = 0, cols[8], i = 0, pontuacao = 0, elemento, qtd, tam;
		bool dif, check = true;
		Ponto ponto;

		while(check){
			qtd = 0;
			tam = pontos->getSize();
			SDL_Rect my_rects[tam];
			Ponto coord[tam];
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
                setElement(ponto.x, ponto.y, 8);
                apply_surface(ponto.x, ponto.y, gems, screen);
                my_rects[qtd].x = matriz[ponto.x][ponto.y].celula.x;
                my_rects[qtd].y = matriz[ponto.x][ponto.y].celula.y;
                my_rects[qtd].w = matriz[ponto.x][ponto.y].celula.w;
                my_rects[qtd++].h = matriz[ponto.x][ponto.y].celula.h;
            }
            SDL_Delay(300);
            SDL_UpdateRects(screen, tam, my_rects);
            SDL_Delay(300);
			moveElement(cols, i);
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
                fillUndo(); // guarda as telas em um pilha para uso da função Undo
				bool flag = false;
                char pontVetor[6];

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

					user->setPontuacao(user->getPontuacao()+novosPontos);

                    sprintf(pontVetor,"%d",user->getPontuacao());
                    pontosJogador = TTF_RenderText_Solid( font, pontVetor, textColor );
                    
                    showPontuacao();

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
                    matriz[x][y].clip = &clipsGems[ YELLOW ];
                    matriz[x][y].elemento = cod;
                    break;
                case 2:
                    matriz[x][y].clip = &clipsGems[ WHITE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 3:
                    matriz[x][y].clip = &clipsGems[ BLUE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 4:
                    matriz[x][y].clip = &clipsGems[ RED ];
                    matriz[x][y].elemento = cod;
                    break;
                case 5:
                    matriz[x][y].clip = &clipsGems[ PURPLE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 6:
                    matriz[x][y].clip = &clipsGems[ ORANGE ];
                    matriz[x][y].elemento = cod;
                    break;
                case 7:
                    matriz[x][y].clip = &clipsGems[ GREEN ];
                    matriz[x][y].elemento = cod;
                    break;
                case 8:
                    matriz[x][y].clip = &clipsGems[ BLANK ];
                    matriz[x][y].elemento = cod;
            }
        }

        void Tela::contrastItem(int x, int y, int cod) {
            switch(cod) {
                case 1:
                    matriz[x][y].clip = &clipsGems_dica[ YELLOW ];
                    break;
                case 2:
                    matriz[x][y].clip = &clipsGems_dica[ WHITE ];
                    break;
                case 3:
                    matriz[x][y].clip = &clipsGems_dica[ BLUE ];
                    break;
                case 4:
                    matriz[x][y].clip = &clipsGems_dica[ RED ];
                    break;
                case 5:
                    matriz[x][y].clip = &clipsGems_dica[ PURPLE ];
                    break;
                case 6:
                    matriz[x][y].clip = &clipsGems_dica[ ORANGE ];
                    break;
                case 7:
                    matriz[x][y].clip = &clipsGems_dica[ GREEN ];
                    break;
                case 9:
                    matriz[x][y].clip = &clipsGems_dica[ BLANK ];
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

            //Telas
            telaInicial = load_image( "Images/tela_inicial.png" );
            telaIdentificacao = load_image( "Images/tela_identificacao.png" );
            telaInstrucoes = load_image( "Images/tela_instrucoes.png" );
            telaConfigSound_ON = load_image( "Images/tela_conf_som_on.png" );
            telaConfigSound_OFF = load_image( "Images/tela_conf_som_off.png" );;
            telaLevelUp = load_image( "Images/tela_levelup.png" );
            telaGameOver = load_image( "Images/tela_gameover.png" );

            //Load the button sprite sheet
            gems = load_image( "Images/new_gems.png" );

            gems_dica = load_image( "Images/dica.png" );

            fundo = load_image( "Images/bg.png" );

            // Bonus
            gemYellow = load_image( "Images/yellow.png" );
            gemWhite = load_image( "Images/white.png" );
            gemBlue = load_image( "Images/blue.png" );
            gemRed = load_image( "Images/red.png" );
            gemPurple = load_image( "Images/purple.png" );
            gemOrange = load_image( "Images/orange.png" );
            gemGreen = load_image( "Images/green.png" );

            fase1 = load_image( "Images/fase1.png" );
            fase2 = load_image( "Images/fase2.png" );
            fase3 = load_image( "Images/fase3.png" );
            fase4 = load_image( "Images/fase4.png" );

            hint = load_image( "Images/hint.png" );

            //Open the font
            font = TTF_OpenFont( "Fonts/ARDARLING.ttf", 30 );

            //If there was a problem in loading the button sprite sheet
            if( (gems == NULL) || (gems_dica == NULL))
            {
                return false;
            }

            //If everything loaded fine
            return true;
        }

        void Tela::clean_up() { //LIBERAR TUDO!!
            //Free the surface
            SDL_FreeSurface( gems );

            //Libera ficheiro de audio da memoria
            Mix_FreeMusic(music);

            //Close the font that was used
            TTF_CloseFont( font );

            //Quit SDL_ttf
            TTF_Quit();

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

            //Initialize SDL_ttf
            if( TTF_Init() == -1 ) return false;

            //Set the window caption
            SDL_WM_SetCaption( "Bejeweled", NULL );

            //Inicializa musica
            if( Mix_OpenAudio(AUDIO_RATE, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) == -1 ) return false;
            music = Mix_LoadMUS("Sounds/music.mp3");
            if( music == NULL )	return false;
			//Toca musica (-1 para indefinidamente)
            Mix_PlayMusic(music, -1);

            //If everything initialized fine
            return true;
        }

        void Tela::set_clips(SDL_Rect *clips) {

            //Clip the sprite sheet
            clips[ YELLOW ].x = 0;
            clips[ YELLOW ].y = 0;
            clips[ YELLOW ].w = CELULA_WIDHT;
            clips[ YELLOW ].h = CELULA_HEIGHT;

            clips[ WHITE ].x = 0;
            clips[ WHITE ].y = 70;
            clips[ WHITE ].w = CELULA_WIDHT;
            clips[ WHITE ].h = CELULA_HEIGHT;

            clips[ BLUE ].x = 0;
            clips[ BLUE ].y = 140;
            clips[ BLUE ].w = CELULA_WIDHT;
            clips[ BLUE ].h = CELULA_HEIGHT;

            clips[ RED ].x = 0;
            clips[ RED ].y = 210;
            clips[ RED ].w = CELULA_WIDHT;
            clips[ RED ].h = CELULA_HEIGHT;

            clips[ PURPLE ].x = 0;
            clips[ PURPLE ].y = 280;
            clips[ PURPLE ].w = CELULA_WIDHT;
            clips[ PURPLE ].h = CELULA_HEIGHT;

            clips[ ORANGE ].x = 0;
            clips[ ORANGE ].y = 350;
            clips[ ORANGE ].w = CELULA_WIDHT;
            clips[ ORANGE ].h = CELULA_HEIGHT;

            clips[ GREEN ].x = 0;
            clips[ GREEN ].y = 420;
            clips[ GREEN ].w = CELULA_WIDHT;
            clips[ GREEN ].h = CELULA_HEIGHT;

            clips[ BLANK ].x = 0;
            clips[ BLANK ].y = 490;
            clips[ BLANK ].w = CELULA_WIDHT;
            clips[ BLANK ].h = CELULA_HEIGHT;
        }

        bool Tela::playGame() {
		    Ponto p1 = {-1, -1}, p2 = {-1, -1}, pDica = {-1, -1};
		    bool quit = false, execute = true, hintFlag = false;
		    showGame();
            if(testMove() == false) quit = true;
			float frame = 0;
    		Uint32 start;
			SDL_Rect rect0[20], rect1[20], rect2[20], rect3[20], rect4[20], rect5[20], rect6[20];
		    setrects(rect0, 60, 0);
		    setrects(rect1, 62, 70);
		    setrects(rect2, 58, 140);
		    setrects(rect3, 58, 210);
		    setrects(rect4, 60, 280);
		    setrects(rect5, 64, 350);
		    setrects(rect6, 64, 420);

		    while( execute ) {
		    	changeLevel();
                if( level == 5 ) {
                    execute = false;
                    return execute;
                }

		        if( SDL_PollEvent( &event ) ) {

		            Ponto tmp;

		            //If the left mouse button was pressed
		            if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
	                    //Get the mouse offsets
	                    tmp.x = event.button.x;
	                    tmp.y = event.button.y;
                        if((tmp.x >= 135 && tmp.x <= 250) && (tmp.y >= 480 && tmp.y <= 595)) {
                            undoPlay();
                            SDL_Flip( screen );
	                    } else if((tmp.x >= 45 && tmp.x <= 160) && (tmp.y >= 395 && tmp.y <= 505)){
	                    	pDica = getDica();
	        				apply_surface(pDica.x, pDica.y, gems_dica, screen);
        					SDL_UpdateRect(screen, matriz[pDica.x][pDica.y].celula.x, matriz[pDica.x][pDica.y].celula.y, matriz[pDica.x][pDica.y].celula.w, matriz[pDica.x][pDica.y].celula.h);
	                    } else if((tmp.x >= 30 && tmp.x <= 115) && (tmp.y >= 525 && tmp.y <= 605)){
                            if(showConfScreen()) {
                                quit = true;
                                return quit;
                            } else {
                                showGame();
                            }
                        } else if((tmp.x >= 175 && tmp.x <= 265) && (tmp.y >= 380 && tmp.y <= 465)){
                            if(showInstrucoes()) {
                                quit = true;
                                return quit;
                            } else {
                                showGame();
                            }
                        } else if((tmp.x >= MAT_INITIAL_POINT_X && tmp.x <= MAT_INITIAL_POINT_X + 480) && (tmp.y >= MAT_INITIAL_POINT_Y && tmp.y <= MAT_INITIAL_POINT_Y + 480)) {
	                    	if(pDica.x >= 0) {
		        				apply_surface(pDica.x, pDica.y, gems, screen);
	        					SDL_UpdateRect(screen, matriz[pDica.x][pDica.y].celula.x, matriz[pDica.x][pDica.y].celula.y, matriz[pDica.x][pDica.y].celula.w, matriz[pDica.x][pDica.y].celula.h);
	                    	}
		                    tmp.x = (tmp.x - MAT_INITIAL_POINT_X) / 60;
		                    tmp.y = (tmp.y - MAT_INITIAL_POINT_Y) / 60;
			                if(p1.x < 0) {
			                    p1.x = tmp.y; //Precisa ser invertido
			                    p1.y = tmp.x;
			                    //Destaca a nova joia selecionada
			                } else if(p2.x < 0) {
			                	if(saoAdjacentes(p1.x, p1.y, tmp.y, tmp.x)) {
				                    p2.x = tmp.y; //Precisa ser invertido
				                    p2.y = tmp.x;
			                	} else {
			                		//Ignora selecao
			                		//Tira o destaque da joia que tinha sido selecionada
			        				apply_surface(p1.x, p1.y, gems, screen);
                					SDL_UpdateRect(screen, matriz[p1.x][p1.y].celula.x, matriz[p1.x][p1.y].celula.y, matriz[p1.x][p1.y].celula.w, matriz[p1.x][p1.y].celula.h);
			                		p1.x = tmp.y;
					                p1.y = tmp.x;
			                	}
			                }
	                    }
	                //Se o usuario fechar a janela ou apertar a tecla ESC
		            } else if( (event.type == SDL_QUIT)  || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
		                //Quit the program
		                quit = true;
                        return quit;
	            	} else if( (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ) {
	            		if(audio == true) {
							// pause music playback
							Mix_PauseMusic();
	            			audio = false;
	            		} else {
							// resume music playback
							Mix_ResumeMusic();
	            			audio = true;
	            		}
	            	}
		    	}
	            SDL_Rect offset;
	            offset.x = matriz[p1.x][p1.y].celula.x;
	            offset.y = matriz[p1.x][p1.y].celula.y;
	            switch(getElement(p1.x, p1.y)) {
	            	case 1:
						SDL_BlitSurface( gems, &rect0[static_cast<int>(frame)], screen, &offset );
	            		break;
	            	case 2:
						SDL_BlitSurface( gems, &rect1[static_cast<int>(frame)], screen, &offset );
	            		break;
	            	case 3:
						SDL_BlitSurface( gems, &rect2[static_cast<int>(frame)], screen, &offset );
	            		break;
	            	case 4:
						SDL_BlitSurface( gems, &rect3[static_cast<int>(frame)], screen, &offset );
	            		break;
	            	case 5:
						SDL_BlitSurface( gems, &rect4[static_cast<int>(frame)], screen, &offset );
	            		break;
	            	case 6:
						SDL_BlitSurface( gems, &rect5[static_cast<int>(frame)], screen, &offset );
	            		break;
	            	case 7:
						SDL_BlitSurface( gems, &rect6[static_cast<int>(frame)], screen, &offset );
	            		break;
	            }
				SDL_UpdateRect(screen, matriz[p1.x][p1.y].celula.x, matriz[p1.x][p1.y].celula.y, matriz[p1.x][p1.y].celula.w, matriz[p1.x][p1.y].celula.h);
				//Velocidade de transição entre frames
				frame += 0.5;
		 
		        if(frame > 7) {
		        	frame = 0;
		        }
		 
				if(1000/FPS > SDL_GetTicks()-start) 
				{
					SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
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
		        }
			}
            return execute;
		}

        void Tela::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
            SDL_Rect offset;
            offset.x = matriz[x][y].celula.x;
            offset.y = matriz[x][y].celula.y;
            SDL_BlitSurface( source, matriz[x][y].clip, destination, &offset ); //Blitagem
        }
		void Tela::applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) {
		   SDL_Rect offset;
		   offset.x = x;
		   offset.y = y; 
		   SDL_BlitSurface( source, NULL, destination, &offset );
		}

        void Tela::showPontuacao() {
            char pontVetor[6];

            sprintf(pontVetor,"%d",user->getPontuacao());
            pontosJogador = TTF_RenderText_Solid( font, pontVetor, textColor );
                
            switch(level) {
                case 1:
                    applySurface( 57.938, 184.812, fase1, screen );
                    applySurface( 115, 254.812, pontosJogador, screen );
                    break;                  
                case 2:
                    applySurface( 57.938, 184.812, fase2, screen );
                    applySurface( 115, 254.812, pontosJogador, screen );
                    break;                  
                case 3:
                    applySurface( 57.938, 184.812, fase3, screen );
                    applySurface( 115, 254.812, pontosJogador, screen );
                    break;                  
                case 4:
                    applySurface( 57.938, 184.812, fase4, screen );
                    applySurface( 115, 254.812, pontosJogador, screen );
            }
        }

        // Função para começar o jogo
            void Tela::showGame() {
                fillUndo(); // guarda as telas em um pilha para uso da função Undo
    		    applySurface( 0, 0, fundo, screen );
                if( SDL_Flip( screen ) == -1 )
                    return;
                std::string str = user->getNome();
                const char *c = str.c_str(); //Transforma a string em um vetor de char

                switch(level) {
                	case 1:
						applySurface( 57.938, 184.812, fase1, screen );
                        nomeJogador = TTF_RenderText_Solid( font, c, textColor );
                        applySurface( 20, 120, nomeJogador, screen );
                        showPontuacao();
						break;                	
                	case 2:
						applySurface( 57.938, 184.812, fase2, screen );
                        nomeJogador = TTF_RenderText_Solid( font, c, textColor );
                        applySurface( 20, 120, nomeJogador, screen );
                        showPontuacao();
						break;                	
                	case 3:
						applySurface( 57.938, 184.812, fase3, screen );
                        nomeJogador = TTF_RenderText_Solid( font, c, textColor );
                        applySurface( 20, 120, nomeJogador, screen );
                        showPontuacao();
						break;                	
                	case 4:
						applySurface( 57.938, 184.812, fase4, screen );
                        nomeJogador = TTF_RenderText_Solid( font, c, textColor );
                        applySurface( 20, 120, nomeJogador, screen );
                        showPontuacao();
                }
				if( SDL_Flip( screen ) == -1 ) return;
                SDL_Rect my_rects[8];
                int qtd;
                for(int i = 0; i < linhasMatriz; i++) {
                    qtd = 0;
                    for(int j = 0; j < colunasMatriz; j++) {
                        apply_surface(i, j, gems, screen);
                        my_rects[qtd].x = matriz[i][j].celula.x;
                        my_rects[qtd].y = matriz[i][j].celula.y;
                        my_rects[qtd].w = matriz[i][j].celula.w;
                        my_rects[qtd++].h = matriz[i][j].celula.h;
                    }
                    SDL_UpdateRects(screen, 8, my_rects);
                    SDL_Delay(100);
                }
	            getBonus();
                if( SDL_Flip( screen ) == -1 )
                    return;
            }

            void Tela::showScreen() {
                // SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
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

		void Tela::changeLevel() {

			//if(changedLevel && user->getPontuacao() > 1000 && user->getPontuacao() < 3000) {
            if(changedLevel && user->getPontuacao() > 100 && user->getPontuacao() < 150) {
				level = 2;
				fillMatriz(5);
                changedLevel = false;
				showLevelUp();
                showGame();
			//} else if(!changedLevel && user->getPontuacao() >= 3000 && user->getPontuacao() < 6000) {
            } else if(!changedLevel && user->getPontuacao() >= 150 && user->getPontuacao() < 200) {
				level = 3;
				fillMatriz(6);
                changedLevel = true;
				showLevelUp();
                showGame();
			//} else if(changedLevel && user->getPontuacao() >= 6000 && user->getPontuacao() < 10000) {
            } else if(changedLevel && user->getPontuacao() >= 250 && user->getPontuacao() < 300) {
				level = 4;
				fillMatriz(7);
                changedLevel = false;
				showLevelUp();
                showGame();
			//} else if(!changedLevel && user->getPontuacao() >= 10000) { // esse é o zerar do jogo
            } else if(!changedLevel && user->getPontuacao() >= 300) { // esse é o zerar do jogo
                /*SHOW GAME OVER*/
                level = 5;
			}
		}

		SDL_Surface * Tela::carregar_imagem( std::string filename ) {
			SDL_Surface* imagemcarregada = NULL;
			SDL_Surface* imagemotimizada = NULL;
			imagemcarregada = SDL_LoadBMP( filename.c_str() );
			if( imagemcarregada != NULL ) {
				imagemotimizada = SDL_DisplayFormat( imagemcarregada );
				SDL_FreeSurface( imagemcarregada );
			}
			return imagemotimizada;
		}
        void Tela::fillUndo() {
            Undo telaInicial;
            for(int i = 0; i < linhasMatriz; i++) {
                for(int j = 0; j < colunasMatriz; j++) {
                    telaInicial.mat[i][j] = matriz[i][j];
                }
            }
            telaInicial.pontosAnterior = user->getPontuacao();
            telasAnt.push(telaInicial);
        }
        void Tela::undoPlay() {
            SDL_Rect my_rects[8];
            int qtd;
            for(int i = 0; i < linhasMatriz; i++) {
                qtd = 0;
                for(int j = 0; j < colunasMatriz; j++) {
                    matriz[i][j] = telasAnt.top().mat[i][j];
                    apply_surface(i, j, gems, screen);
                    my_rects[qtd].x = matriz[i][j].celula.x;
                    my_rects[qtd].y = matriz[i][j].celula.y;
                    my_rects[qtd].w = matriz[i][j].celula.w;
                    my_rects[qtd++].h = matriz[i][j].celula.h;
                }
                SDL_UpdateRects(screen, 8, my_rects);
                SDL_Delay(100);
            }
            user->setPontuacao(telasAnt.top().pontosAnterior);
            showPontuacao();
            if(telasAnt.size() > 1) telasAnt.pop();
        }