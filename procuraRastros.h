//
// Created by topau on 23/03/2025.
//

#ifndef RASTROS_PROCURARASTROS_H
#define RASTROS_PROCURARASTROS_H


#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include "Tabuleiro.h"
#include <fstream> // Required for file I/O

class procuraRastros {
public:
    Tabuleiro atual;
    explicit procuraRastros(const Tabuleiro &inicio, int maxProfundidade, bool heuristica, bool iterativo, int tempoLimite)
            : atual(inicio), maxProfundidade(maxProfundidade), heuristica(heuristica), iterativo(iterativo), tempoLimite(tempoLimite){
        start = std::chrono::high_resolution_clock::now();
    };
    std::map<int, int> jogadas; //jogadas possíves(nº da casa a jogar) com o valor do Minimax
    std::unordered_map<uint64_t, int> visitados={}; //registo dos estados visitados para evitar duplicação de análise
    //int vencedor1=0;
    //int vencedor2=0;
    int maxProfundidade;
    int jogadorMax=0;
    bool iterativo;
    bool heuristica;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    int tempoLimite;
    int profAtingida=0;


    void iniciarExpansao();



    /*
    Função Minimax com memória de estado visitados, e limite de profundidade
     estado: objeto tabuleiro de início do algoritmo
     visitados: mapa, com os estados visitados
     jogada: das jogadas válidas para o próximo estado, escolher um, e guardar o número na variável jogada passada por referência
     jogadorMax: o jogador para o qual o algoritmo determina o valor Max
    */
    int minimax(Tabuleiro estado, int profundidade);

    //escolhe o maior valor de cada jogada. Aleatório se tiver vários iguais
    int procuraMelhor();

    void injectaVisitados ();

};




#endif //RASTROS_PROCURARASTROS_H
