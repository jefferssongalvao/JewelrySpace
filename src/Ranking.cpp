#include "Ranking.h"

Ranking::Ranking() {
    loadRecords();
}

void Ranking::loadRecords() {
    int p;
    string str;
    ifstream in;
    in.open(recordsFilePath);
    if(in.is_open()) {
        while(in >> p >> str) {
            ranking.insert(pair<int, string>(p, str));
        }
        in.close();
    }
}

bool Ranking::newRecord(int points) {
    auto it = ranking.end();
    it--;
    if((points > it->first) || (ranking.size() < rankLimit)) {
        return true;
    } else {
        return false;
    }
}

void Ranking::addScore(int points, string name) {
    if(newRecord(points)) {
        ranking.insert(pair<int, string>(points, name));
    }
}

void Ranking::saveRanking() {
    ofstream out;
    out.open(recordsFilePath);
    if(out.is_open()) {
        int i = 0;
        for(auto it = ranking.begin(); (it != ranking.end()) && (i < rankLimit);
            ++it, i++) {
            out << it->first << endl;
            out << it->second << endl;
        }
        out.close();
    }
}

map<int, string, ScoreComp>& Ranking::getRanking() const {
    return ranking;
}
