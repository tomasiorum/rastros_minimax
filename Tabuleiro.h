//
// Created by topau on 15/03/2025.
//

#ifndef RASTROS_TABULEIRO_H
#define RASTROS_TABULEIRO_H
#include <iostream>
#include <vector>
#include <set>
#include "BitStorage.h"
#include "vector"

class Tabuleiro {
private:

    std::string letras[10]={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
public:
    int altura;
    int largura;
    int cursor{};
    int casaObjetivo[2]{};
    std::set<int> preVitoria[2];

    //teste
    //std::vector <uint64_t> historico;
    /*
     * Objeto que contem o nº de 64bits
     */
    BitStorage jogo;

    /*
     * Construtor para um tabuleiro inicial
     */
    explicit Tabuleiro(int a, int l, int inicio);

    /*
     * Construtor da classe baeseado num jogo já em curso
     */
    explicit Tabuleiro (uint64_t j, int altura, int largura);


    ~Tabuleiro();

    void inicializar(int a, int l, int inicio);
    /*
     * Devolve um vetor com as casas para jogadas válidas (nº de ordem na variável)
     */
    std::vector<int> jogadasValidas();

    /*
     * Baseado no jogador a jogar, sendo o jogadorA o que pretendemos que seja vitorioso, e na avaliação de estado final devolve as jogadas que são relevantes
     */
    std::vector<int> jogadasUteis(int jogadorA);

    /*
     * Devove a que linha pertence uma determidada casa (nº de ordem na variável) considerando o tamanho do tabuleiro
     */
    int linha(int casa);

    /*
    * Devove a que coluna pertence uma determidada casa (nº de ordem na variável) considerando o tamanho do tabuleiro
    */
    int coluna(int casa);

    /*
     * Devolve a posiçáo, (o número de ordem na variável) para uma coordenada linha/coluna
     */
    int ordem (int linha, int coluna);




    /*
     * Joga o cursor para uma casa
     */
    void jogar (int casa);

    void imprimir ();

    int ganhador();

    /*
     * mostra uma casa com as respetivas coordenadas letra+numero
     */
    void mostrarCoordenada (int jogada);

    void mostrarJogadasValidas();

    /*
     * Atualiza o objeto com nova variável de jogo, para poder efetuar as jogadas
     */
    void atualiza (uint64_t j);

    /*
     * Calcula a distancia do jogador a jogar à casa objetivo, contando só as casas jogáveis
     */
    int distanciaCanto(int canto);

    /*
     * procura casas adjacentes livres, para calcular a distancia á origem (para usar recursivamente)
     */
    void adjacentes (int origem, int *casas, int &distMax, int &fim, int &minTeorico);

    /*
     * escreve as jogadas num ficheiro
     */
    bool writeHistoricoToCsv(const std::string& filename, const std::string& prefix1, const std::string& prefix2);

    int previtoria();

    void testa();
};


#endif //RASTROS_TABULEIRO_H
