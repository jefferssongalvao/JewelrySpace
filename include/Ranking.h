#ifndef RANKING_H
#define RANKING_H

#include <iostream>
#include <fstream>
#include <map>

using std::map;
using std::pair;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;

/*
 * Estrutura responsavel pela comparacao de elementos no map
*/
struct ScoreComp {
    bool operator()(const int& a, const int& b) const {
        return a > b;
    }
};

class Ranking {

private:

    // Limite maximo de recordes
    const int rankLimit = 5;

    // Caminho do arquivo contendo os recordes
    const string recordsFilePath = "resources/Records";

    // Arvore Binaria de Busca para armazenar os recordes
    map<int, string, ScoreComp> ranking;

private:

    // Metodo responsavel por carregar os recordes do arquivo para o map
    void loadRecords();

public:

    // Construtor -- apenas carrega os recordes do arquivo
    Ranking();

    // Se o score for um novo recorde, adiciona no map
    void addScore(int points, string name);

    // Verifica se o placar eh um novo recorde
    bool newRecord(int points);

    // Salva o ranking (os scores armazenados no map) para o arquivo
    void saveRanking();

    map<int, string, ScoreComp>& getRanking() const;

};

#endif // RANKING_H
