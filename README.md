Bejeweled
=========

Jewelry Space - Bejeweled

Para a implementação do jogo foi usada a biblioteca SDL e apesar dela funcionar independente do Sistema Operacional, o jogo não apresenta o .exe para executar no windows. Para o Linux é necessário o download da biblioteca SDL.
Para a distribuição Ubuntu digite no terminal o comando: "apt-get install" e para a distribuição Fedora digite "yum install" os componente necessários.
Após o download dos componentes a biblioteca estará instala e configurada para a execução do jogo.
Par compilar digite:
    g++ *.cpp -o main -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -std=c++11
Para executar entre no terminal e no diretório do jogo, digite:
    ./nome-do-jogo
Caso não possua o arquivo "nome-do-jogo", digite:
    g++ *.cpp -o nome-do-jogo -lSDL -lSDL_image
    
    
        
        *****OBS: Substitua "nome-do-jogo".
