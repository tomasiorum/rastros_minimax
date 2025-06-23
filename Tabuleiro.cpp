//
// Created by topau on 15/03/2025.
//


#include <fstream>
#include "Tabuleiro.h"


Tabuleiro::Tabuleiro(int a, int l, int inicio) {
    altura=a;
    largura=l;
    inicializar(a,l,inicio);
}

void Tabuleiro::testa() {
    for (std::set pre:preVitoria) {
        for (int x:pre) {
            std::cout<<x<<"\n";
        }
    }
}

Tabuleiro::~Tabuleiro() = default;

void Tabuleiro::inicializar(int a, int l, int inicio) {
    cursor=inicio;
    jogo.setMostSignificant6Bits(cursor);
    //jogo.setTamanho(a,l);
    //std::cout << "Altura:" <<jogo.getTamanhoA()<< std::endl;
    //std::cout << "Largura:" <<jogo.getTamanhoL()<< std::endl;
    casaObjetivo[0]= ordem(altura-1,0);
    casaObjetivo[1]= ordem(0,largura-1);

    //casas enconstadas à casa do objetivo
    preVitoria[0].insert(casaObjetivo[0]+1);
    preVitoria[0].insert(casaObjetivo[0]-largura);
    preVitoria[0].insert(casaObjetivo[0]-largura+1);
    preVitoria[1].insert(casaObjetivo[1]-1);
    preVitoria[1].insert(casaObjetivo[1]+largura);
    preVitoria[1].insert(casaObjetivo[1]+largura-1);
}

void Tabuleiro::imprimir() {

    std::cout<<std::endl;
    for (int i=0; i<altura;i++) {
        std::cout<<altura-i<<" :";
        for (int j=0; j<largura;j++) {
            if (ordem(i,j) == jogo.getMostSignificant6Bits())
                std::cout << " O ";

            else if (i==0 and j==largura-1) {
                std::cout<<" 2 ";
            }
            else if (i==altura-1 and j==0) {
                std::cout<<" 1 ";
            }

            else if (jogo.isBitSet(ordem(i,j) )) {
                std::cout << " # ";
            } else {
                std::cout << " . ";
            };

        }
        std::cout<<std::endl;
    }
    std::cout<<"   ";
    for (int i=0; i<largura; i++)
        std::cout<<" "<<letras[i]<<" ";
    std::cout<<std::endl;
}

std::vector<int> Tabuleiro::jogadasValidas() {
    std::vector<int> jogadas; //vetor com as casas com jogadas possíveis
    cursor=jogo.getMostSignificant6Bits();
    int linha_min=std::max(0,linha(cursor)-1);
    int linha_max=std::min(linha(cursor)+1,altura-1);
    int coluna_min=std::max(0,coluna(cursor)-1);
    int coluna_max=std::min(largura-1,coluna(cursor)+1);
    //std::cout<<"cursor:"<<cursor<<" Da linha "<<linha_min<< " a "<<linha_max;
    for (int i = linha_min; i <= linha_max; i++)
        for (int j = coluna_min; j <= coluna_max; j++) {
            if (jogo.isBitSet(ordem(i, j)) or ordem(i, j) == cursor)
                continue;
            jogadas.push_back(ordem(i, j));
        }


    return jogadas;
}

int Tabuleiro::linha(int casa) {
    return casa/largura;;
}

int Tabuleiro::coluna(int casa) {
    return (casa-(linha(casa)*largura));
}

int Tabuleiro::ordem(int linha, int coluna) {
    return linha*largura+coluna;
}

void Tabuleiro::jogar(int casa) {
    //std::cout<<" Vai jogar"<<casa<<std::endl;
    jogo.setBit(jogo.getMostSignificant6Bits());
    cursor=casa;
    jogo.setMostSignificant6Bits(casa);
    jogo.toggleBit(57);
}

Tabuleiro::Tabuleiro(uint64_t j, int altura, int largura) {
    atualiza(j);
    //jogo.setValue(j);
    //altura=jogo.getTamanhoA();
    //largura=jogo.getTamanhoL();
    this->altura=altura;
    this->largura=largura;
    inicializar(altura,largura,jogo.getMostSignificant6Bits());
}

int Tabuleiro::ganhador() {
    cursor=jogo.getMostSignificant6Bits();
    //if (linha(cursor)==altura-1 && coluna(cursor)==0) {
    if (cursor==casaObjetivo[0]) {
        return 0; //no canto inferior esquerdo ganha o jogador 1 independentemente de quem jogou
    }
    else if (cursor==casaObjetivo[1]) {//(linha(cursor)==0 && coluna(cursor)==largura-1) {
        return 1;
    }
    else if (jogadasValidas().empty()) {
        return !(jogo.isBitSet(57));
    }
    return -1;
}

int Tabuleiro::previtoria() {
    cursor=jogo.getMostSignificant6Bits();
    //verifica se está numa casa adjacente ao canto: 0 se for ao canto 1, 1, se for ao canto 2, e -1 não estiver
    if (preVitoria[0].find(cursor)!=preVitoria[0].end()) {
        return 0;
    }
    else if ((preVitoria[1].find(cursor)!=preVitoria[1].end())) {
        return 1;
    }
    else
        return -1;
}


void Tabuleiro::mostrarCoordenada(int jogada) {
    std::cout<<" "<<letras[coluna(jogada)]<<altura-linha(jogada)<<":"<<jogada;
}

void Tabuleiro::atualiza(uint64_t j) {
    jogo.setValue(j);
    cursor=jogo.getMostSignificant6Bits();
}

void Tabuleiro::mostrarJogadasValidas() {
    for (int jogada: jogadasValidas()) { // Imprime as jogadas válidas
        mostrarCoordenada(jogada);
    }
    std::cout << std::endl;

}

std::vector<int> Tabuleiro::jogadasUteis(int jogadorA) {
    std::vector<int> resultado;

    for (int jogada: jogadasValidas()) {
        // se for o jogadorA a jogar, e tiver vitória disponível, o vetor fica só com essa jogada.
        if(jogo.isBitSet(57)==jogadorA && ganhador()==jogadorA) {
            resultado.push_back(jogada);
            std::cout<<"A vitoria";
            return resultado;
        }
        //se for para avaliar a jogada do jogadorB, caso haja algum vitória do jogadorB, deve retornar vazio.
        if(jogo.isBitSet(57)==!jogadorA && ganhador()==!jogadorA) {
            std::cout<<"B vitoria";
            return resultado;
        }
    }
    return jogadasValidas();
}

int Tabuleiro::distanciaCanto(int canto) {
    int inicio=jogo.getMostSignificant6Bits();
    int fim=casaObjetivo[canto]; // o fim é a casa objetivo
    /*
     * ...vetor casas[]
     * Vetor com as 56 casas, inicializadas com -1
     */
    int casas[56];
    for (int & casa : casas) {
        casa=-1;
    }
    casas[inicio]=0;
    int visitadas=0;
     /*
      * começa no local do caracol
      *
      * expande uma linha e uma coluna:
      *     por cada um livre, procura todos os livre agarrados, assume x+1 (mínimo entre o valor que tiver e x+1)
      *     repete para os livre que estavam agarrados
      */
    int minTeorico=std::max(abs(linha(inicio)-linha(fim)),abs(coluna(fim)- coluna(inicio))); //distância mínima ao canto. Se atingida não precisa de procurar mais
    int distMin=56;//distãncia mínima encontrada até agora
    adjacentes(inicio, casas, distMin, fim, minTeorico);

    //std::cout<<"Visitadas: "<<visitadas<<"\n";
    //se atinge o objetivo devolve a distância. Se não atinge devolve a distância ao objetivo inimigo. Se não atinge este também verifica se está num grupo com casas livres pares ou ímpares
    // melhor: atingir e estar perto
    // mau: não atingir o próprio e estar perto do obj. do adversário (para já não calcula esta)
    // pior: estar num grupo fechado com casas ímpares (se for grande é menos mau porque o adversário humano pode jogar mal
    // ótimo: estar num grupo fechado com casas pares

    if (distMin==56){ //zona sem acesso ao objetivo
        //imprimir();
        if (casas[casaObjetivo[!canto]]!=-1) { //se o outro canto  estiver acessível é mau
            return -50;
        }
        else { //não está nenhum canto acessível
            //contagem das casas no espaço encurralado
            for (int & casa : casas) {
                if (casa!=-1)
                    visitadas++;
            }
            //Avaliação da possibilidade de encurralamento
            if (visitadas%2!=0) //se é ímpar
                return -100; //este jogador vai perder
            else
                return 100; //este jogador vai ganhar//

        }
    }
    else
        return 0;// H1: 100-distMin; //quanto mais perto melhor
}

void Tabuleiro::adjacentes(int origem, int *casas, int &distMin, int &destino, int &minTeorico) {

    if (distMin==minTeorico)  {//se é a menor distância possível não vale a pena procurar mais (mais eficiente se a procura começar por ir para o lado do destino
        return;
    }
    //ciclos for para testar a casa adjacente em todas as direções
    for (int i = std::max(0,linha(origem)-1); i <=std::min(linha(origem)+1,altura-1); i++) {
        for (int j = std::max(0,coluna(origem)-1); j <= std::min(largura-1,coluna(origem)+1); j++) {
            if (ordem(i,j)==destino) { //encontrou a casa destino
                //H2: para fazer heuristica só a contar com espaços fechados, e neste caso ignora a distância, já que só interessa se a casa não estiver acessível

                distMin=minTeorico; //para não ser interpretado como espaço fechado

                return;
                //H1: -- Para a heurística considerando a distância ao ponto
                distMin=std::min(distMin, casas[origem]+1);
            }
            else if (ordem(i, j) != origem && not(jogo.isBitSet(ordem(i, j)))) //não é a casa atual e não está ocupada
                //H2
                if (casas[ordem(i, j)] == -1) {
                    casas[ordem(i, j)] = casas[origem] + 1;
                    adjacentes(ordem(i, j), casas, distMin, destino, minTeorico); //versão só para analisar a quantidade de casas livres
                }

                /* H1 versão para heurística da menor distância
                if (casas[ordem(i, j)] == -1 || casas[origem] + 1 < casas[ordem(i, j)]) { //não está ocupada ou tem um valor mais alto que esta opção
                    casas[ordem(i, j)] = casas[origem] + 1; //a distância da casa analisada é a distância da anterior + 1
                    adjacentes(ordem(i, j), casas, distMin, destino, minTeorico);
                }
                 */
        }
    }

}




