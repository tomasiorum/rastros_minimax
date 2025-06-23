//
// Created by topau on 23/03/2025.
//

#include <limits>
#include <random>
#include <chrono>
#include "procuraRastros.h"



void procuraRastros::iniciarExpansao() {

    jogadorMax=atual.jogo.isBitSet(57);

    int auxProfundidade=maxProfundidade;

    for (auto possivelJogada:atual.jogadasValidas()) {
        jogadas.insert({possivelJogada,0});
        //std::cout<<"Jogada possivel inicial:"<<possivelJogada<<"\n";

    }

    if (iterativo) {
        for (int i=2; i<=auxProfundidade;i++) {

            for (auto it = visitados.begin(); it != visitados.end();) {
                if (abs(it->second) <1000) {
                    it = visitados.erase(it); // 'it' now points to the next valid element
                } else {
                    ++it; // Only increment if we didn't erase
                }
            }

            maxProfundidade=i;
            minimax(atual,0);
        }
    }
    else {
        minimax(atual,0);
    }
}

int procuraRastros::minimax(Tabuleiro estado, int profundidade) {

    auto stop = std::chrono::high_resolution_clock::now();
    auto duracao=std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    if (duracao.count()>tempoLimite) {
        //std::cout<< "Fim do iterativo com" << duracao.count()<<" Profundidade:"<<profundidade<<"\n";
        return 0;
    };

    // Verifica se já foi avaliado este estado
    auto it = visitados.find(estado.jogo.getValue());


    if (it != visitados.end()) {
        // A chave existe, então it devolve o valor
        return it->second;
    }

    int pontosMinimax;
    if (profundidade==0)
        pontosMinimax=0;

    if (estado.jogo.isBitSet(57) == jogadorMax) {
        pontosMinimax = std::numeric_limits<int>::min(); // Initialize to -infinity for maximizing
    } else {
        pontosMinimax = std::numeric_limits<int>::max(); // Initialize to +infinity for minimizing
    }
    /*
     * Cálculo da pontuação:
     * - se é estado final, será 1000 ou -1000, conforme seja o jogador Max ou Min.
     *  -Se atingiu a profundidade e não é estado final, será 0
     *  - Se é antes de atingir a profundidade e não é estado final, é o MiniMax dos sucessores
     *
     */
    if (profundidade==maxProfundidade||estado.ganhador()!=-1) {

        if (estado.ganhador()==-1) {

            pontosMinimax=0;
            if (estado.jogo.isBitSet(57)==jogadorMax && estado.previtoria()==jogadorMax ) {
                pontosMinimax=1000;
                //std::cout<<"Levou com 1000"<<"\n";
                //estado.imprimir();
            }
                //se estiver nas casas adjacentes ao objetivo inimigo e não for o max a jogar, perde
            else if(estado.jogo.isBitSet(57)==!jogadorMax && estado.previtoria()==!jogadorMax) {
                pontosMinimax=-1000;
                //std::cout<<"Levou com -1000"<<"\n";
                //estado.imprimir();
            }

            else if (heuristica) {
                int heuristicaDistancia =estado.distanciaCanto(estado.jogo.isBitSet(57));
                if (estado.jogo.isBitSet(57)==jogadorMax) {
                    pontosMinimax=heuristicaDistancia;
                }
                else pontosMinimax=-heuristicaDistancia;
            }
        }
        else if (estado.ganhador()==jogadorMax) {
            pontosMinimax=1000;
        }
        else {
            pontosMinimax=-1000;
        }
    }

    else {

        //corre as jogadas possíveis e obtem a respetiva pontuação

        for (int novaJogada: estado.jogadasValidas()) {
            //std::cout<<"Testa de:"<<estado.cursor<<" para "<<novaJogada<<"\n";
            profAtingida=std::max(profAtingida,profundidade);
            Tabuleiro novoEstado=estado;
            novoEstado.jogar(novaJogada); //avança uma jogada
            //novoEstado.imprimir();
            int pontosFilhos= minimax(novoEstado,profundidade+1); //verifica o resultado da jogada

            if (estado.jogo.isBitSet(57)==jogadorMax) {
                pontosMinimax=std::max(pontosMinimax,pontosFilhos);
                if (pontosMinimax==1000) {
                    break;
                }

            }
            else {
                pontosMinimax=std::min(pontosMinimax,pontosFilhos);
                if (pontosMinimax==-1000) {
                    break;
                }

            }
        }
    }

   // limpa mapa dos estados para libertar memória
    if (visitados.size()>1000000) {
        for (auto it = visitados.begin(); it != visitados.end(); /* no increment here */) {
            if (it->second == 0) {
                it = visitados.erase(it); // 'it' now points to the next valid element
            } else {
                ++it; // Only increment if we didn't erase
            }
        }
        //std::cout << "Limpou visitados. Ficaram " << visitados.size() << std::endl;
    }

        // Adiciona aos estados já vistos
    visitados.insert({estado.jogo.getValue(), pontosMinimax});


    /*
    * se o nível é o nível 1, adiciona ao vetor jogadas, com a respetiva pontuação, para ser escolhido
    */
    if (profundidade==1) {
        //std::cout<<"Guarda a jogada :"<<estado.jogo.getMostSignificant6Bits()<<" com pontos :"<<pontosMinimax<<"\n";
        auto it = jogadas.find(estado.jogo.getMostSignificant6Bits());
        if (it == jogadas.end()) {
            // Key doesn't exist, so insert the new key-value pair
            jogadas.insert({estado.jogo.getMostSignificant6Bits(), pontosMinimax});
        } else {
            // Key already exists, so update its value
            it->second = pontosMinimax;
        }
    }

    //std::cout<<"Devolve os pontos :"<<pontosMinimax<<"\n";
    return pontosMinimax;
}

int procuraRastros::procuraMelhor() {
    if (jogadas.empty()) {
        return -1;
    }

    int maxValue = jogadas.begin()->second;
    std::vector<int> maxKeys;
    maxKeys.push_back(jogadas.begin()->first);

    for (auto it = jogadas.begin(); it != jogadas.end(); ++it) {
        //std::cout<<"Jogada possível:"<<it->first<<"-"<<it->second<<"\n";
        if (it->second > maxValue) {
            maxValue = it->second;
            maxKeys.clear();
            maxKeys.push_back(it->first);
        } else if (it->second == maxValue) {
            maxKeys.push_back(it->first);
        }
    }

    if (maxKeys.empty()) {
        return -1;
    }

    // Generate a random index using rand()
    int randomIndex = rand() % maxKeys.size();
    //std::cout<<"Vai jogar:"<<maxKeys[randomIndex]<<"\n";
    return maxKeys[randomIndex];
}



