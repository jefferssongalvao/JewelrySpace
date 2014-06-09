Bejeweled
=========
/ Jogo desenvolvido por Jeffersson Galvão, Raquel Oliveira e Rubem Kalebe/
Jewelry Space - Bejeweled
=========================


A mais nova versão do jogo Bejeweled com o tema: 'ESPACIAL'. Produzido na linguagem de programação C++ o projeto refere-se a nota para as disciplinas de ESTRUTURA DE DADOS BÁSICAS 1 e LINGUAGEM E PROGRAMAÇÃO 1. O projeto encontra-se na versão demo e desde já é possível perceber o quão eficiente ele é. Para a implementação do jogo foi usada a biblioteca SDL e apesar dela funcionar independente do Sistema Operacional, este jogo não apresenta o .exe para executar no Windows. Para o Linux é necessário o download da biblioteca SDL.
Para a distribuição Ubuntu digite no terminal o comando: "sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev" e para a distribuição Fedora digite "sudo yum install SDL*".
Após o download dos componentes a biblioteca estará instalada e configurada para a execução do jogo.
Par compilar digite:
    g++ *.cpp -o main -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -std=c++11
Para executar entre no terminal e no diretório do jogo, digite:
    ./nome-do-jogo

        
        *****OBS: Substitua "nome-do-jogo".
