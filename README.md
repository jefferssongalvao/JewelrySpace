Bejeweled
=========

Jewelry Space - Bejeweled


A mais nova versão do jogo bejeweled com o tema 'ESPACIAL'. Produzido na linguagem de programação C++ o projeto refere-se a nota para as disciplinas de ESTRUTURA DE DADOS BÁSICAS 1 e LINGUAGEM E PROGRAMAÇÃO 1. O projeto encontra-se na versão demo e desde já é possível perceber o quão eficiente ele é. Para a implementação do jogo foi usada a biblioteca SDL e apesar dela funcionar independente do Sistema Operacional, o jogo não apresenta o .exe para executar no windows. Para o Linux é necessário o download da biblioteca SDL.
Para a distribuição Ubuntu digite no terminal o comando: "apt-get install" e para a distribuição Fedora digite "yum install" os componente necessários.
Após o download dos componentes a biblioteca estará instala e configurada para a execução do jogo.
Par compilar digite:
    g++ *.cpp -o main -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -std=c++11
Para executar entre no terminal e no diretório do jogo, digite:
    ./nome-do-jogo
Caso não possua o arquivo "nome-do-jogo", digite:
    g++ *.cpp -o nome-do-jogo -lSDL -lSDL_image
    
    
        
        *****OBS: Substitua "nome-do-jogo".
