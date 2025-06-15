#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <limits> // Required for numeric_limits

// Assume Tabuleiro and procuraRastros classes are defined in these headers
#include "Tabuleiro.h"
#include "procuraRastros.h"

int jogadaAI(Tabuleiro& jogo, int dificuldade, bool iterativo, bool euristica, int tempoLimite);
void torneio();
int jogarContraPC();
int pvp();
int aiVsAi();


int jogadaSite(uint64_t input, int dificuldade) {
    Tabuleiro manual(input, 7, 7);
    int jogada=jogadaAI(manual, dificuldade,true, false, 1000);
    return jogada;
}

int jogarContraPC() {
    Tabuleiro jogo(7, 7, 18);
    int jogadorPC;
    int dificuldade;

    std::cout << "Jogar contra PC:" << std::endl;
    do {
        std::cout << "O PC sera o jogador 1 ou 2? (1/2): ";
        std::cin >> jogadorPC;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, digite 1 ou 2." << std::endl;
            continue;
        }
        if (jogadorPC != 1 && jogadorPC != 2) {
            std::cout << "Opcao invalida. Por favor, digite 1 ou 2." << std::endl;
        }
    } while (jogadorPC != 1 && jogadorPC != 2);

    do {
        std::cout << "Escolha a dificuldade do PC (1-9): ";
        std::cin >> dificuldade;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, digite um numero entre 1 e 50." << std::endl;
            continue;
        }
        if (dificuldade < 1 || dificuldade > 50) {
            std::cout << "Dificuldade invalida. Por favor, escolha um valor entre 1 e 50." << std::endl;
        }
    } while (dificuldade < 1 || dificuldade > 50);

    while (true) {
        jogo.imprimir();
        std::vector<int> jogadasValidas = jogo.jogadasValidas();

        if (jogo.ganhador() >= 0) {
            std::cout << "Fim de jogo. O ganhador foi o jogador " << jogo.ganhador() + 1 << std::endl;
            return 0;
        }

        if (jogo.jogo.isBitSet(57) + 1 == jogadorPC) {
            std::cout << "Turno do PC (Jogador " << jogadorPC << ")" << std::endl;
            jogo.jogar(jogadaAI(jogo, dificuldade, false, true, 99999999));
        } else {
            std::cout << "Jogadas validas: ";
            for (int jogada : jogadasValidas) {
                jogo.mostrarCoordenada(jogada);
            }
            int escolha;
            bool jogadaValida = false;
            std::cout << "\n Jogador " << jogo.jogo.isBitSet(57) + 1 << " >> Escolha uma jogada: ";
            std::cin >> escolha;
            std::cout << std::endl;

            for (int jogada : jogadasValidas) {
                if (escolha == jogada) {
                    jogadaValida = true;
                    jogo.jogar(escolha);
                    break;
                }
            }

            if (!jogadaValida) {
                std::cout << "Jogada invalida. Tente novamente." << std::endl;
            }
        }
    }
}

int pvp() {
    Tabuleiro jogo(7, 7, 18);

    while (true) {
        jogo.distanciaCanto(0);
        jogo.imprimir();
        std::vector<int> jogadasValidas = jogo.jogadasValidas();

        if (jogo.ganhador() >= 0) {
            std::cout << "Fim de jogo. O ganhador foi o jogador " << jogo.ganhador() + 1 << std::endl;
            return 0;
        }

        std::cout << "Jogadas validas: ";
        for (int jogada : jogadasValidas) {
            jogo.mostrarCoordenada(jogada);
        }
        int escolha;
        bool jogadaValida = false;
        std::cout << "\n Jogador " << jogo.jogo.isBitSet(57) + 1 << " >> Escolha uma jogada: ";
        std::cin >> escolha;
        std::cout << std::endl;

        for (int jogada : jogadasValidas) {
            if (escolha == jogada) {
                jogadaValida = true;
                jogo.jogar(escolha);
                break;
            }
        }

        if (!jogadaValida) {
            std::cout << "Jogada invalida. Tente novamente." << std::endl;
        }
    }
}

int aiVsAi() {
    Tabuleiro jogo(7, 7, 18);
    int dificuldade1, dificuldade2;

    std::cout << "AI vs AI:" << std::endl;
    do {
        std::cout << "Escolha a dificuldade da AI para o Jogador 1 (1-10): ";
        std::cin >> dificuldade1;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, digite um numero entre 1 e 50." << std::endl;
            continue;
        }
        if (dificuldade1 < 1 || dificuldade1 > 50) {
            std::cout << "Dificuldade invalida. Por favor, escolha um valor entre 1 e 50." << std::endl;
        }
    } while (dificuldade1 < 1 || dificuldade1 > 50);

    do {
        std::cout << "Escolha a dificuldade da AI para o Jogador 2 (1-50): ";
        std::cin >> dificuldade2;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, digite um numero entre 1 e 50." << std::endl;
            continue;
        }
        if (dificuldade2 < 1 || dificuldade2 > 50) {
            std::cout << "Dificuldade invalida. Por favor, escolha um valor entre 1 e 10." << std::endl;
        }
    } while (dificuldade2 < 1 || dificuldade2 > 50);

    while (true) {
        jogo.imprimir();

        if (jogo.ganhador() >= 0) {
            std::cout << "Fim de jogo. O ganhador foi o jogador " << jogo.ganhador() + 1 << std::endl;
            return 0;
        }

        std::cout << "Turno da AI Jogador " << jogo.jogo.isBitSet(57) + 1 << std::endl;
        if (jogo.jogo.isBitSet(57) == 0) {
            jogo.jogar(jogadaAI(jogo, dificuldade1, true, true,1000));
        } else {
            jogo.jogar(jogadaAI(jogo, dificuldade2, false, false,99000));
        }
    }
}

void torneio() {
    int vencedor[]={0,0};

    int dificuldade1=50 , dificuldade2=50;
    for (int i=0; i<100;i++) {
        std::cout<<i<<"\n";
        std::cout << "1:"<<vencedor[0]<<"\n";
        std::cout << "2:"<<vencedor[1]<<"\n";
        Tabuleiro jogo(8, 7, 18);
        //jogo.historico.push_back(jogo.jogo.getValue());
        while (true) {
            jogo.imprimir();

            if (jogo.ganhador() >= 0) {
                vencedor[jogo.ganhador()]++;
                break;//sair do ciclo while;
            }

            //std::cout << "Turno da AI Jogador " << jogo.jogo.isBitSet(57) + 1 << std::endl;
            if (jogo.jogo.isBitSet(57) == 0) {
                jogo.jogar(jogadaAI(jogo, dificuldade1, true, false,1000));
                std::cout << "JOga 1:"<<"\n";
            } else {
                jogo.jogar(jogadaAI(jogo, dificuldade2, true, false,1000));
                std::cout << "JOga 2:"<<"\n";
            }
            //jogo.historico.push_back(jogo.jogo.getValue());
        }
        //jogo.writeHistoricoToCsv("torneio.csv",std::to_string(i), std::to_string(jogo.ganhador()));
    }
    std::cout << "Ganhos de 1:"<<vencedor[0]<<"\n";
    std::cout << "Ganhos de 2:"<<vencedor[1]<<"\n";

}

int jogadaAI( Tabuleiro& jogo, int dificuldade, bool iterativo, bool euristica, int tempoLimite) {

    int profundidade = dificuldade; // A dificuldade diretamente define a profundidade


    auto start = std::chrono::high_resolution_clock::now();
    procuraRastros solver(jogo, profundidade, euristica, iterativo, tempoLimite);
    solver.iniciarExpansao();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    //std::cout << "Tempo de execucao da AI: " << duration.count() << " milissegundos" << std::endl;
    //std::cout<< "Estados guardados: "<<solver.visitados.size()<<"\n";
    /* para mastrar as jogadas avaliadas e respetivo valor minimax
    for (const auto& pair : solver.jogadas) {
        std::cout << "Chave: " << pair.first << ", Valor: " << pair.second << std::endl;
    }
     */
    // std::cout << "Profundiade: "<<solver.profAtingida+1<<"\n";
    return solver.procuraMelhor();
}


int main() {
    // Fazer um campeonato com variação de dificuldade, iterativo, euristica e tempo limite

    Tabuleiro manual(static_cast<uint64_t>(1873497444986126337),5,5);
    std::cout << "altura: "<<manual.altura<<"\n";
    //Tabuleiro manual(5, 5, 12);
    manual.imprimir();
    //jogadaAI(manual, 5,true, false, 1000);
    return 0;
    torneio();
    return 0;
    //Tabuleiro jogo(7, 7, 18);
    //std::cout<<"Codigo:"<<jogo.jogo.getVa1lue();
    //jogo.imprimir();
    //jogo.testa();
    //jogo.imprimir();
    //jogo.distanciaCanto();
    //jogadaAI(jogo,8);
    //jogadaAImemoic(jogo,8);
    return 0;


    int escolha;

    do {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1 - Jogar contra PC" << std::endl;
        std::cout << "2 - Jogar com outro jogador" << std::endl;
        std::cout << "3 - AI vs AI" << std::endl;
        std::cout << "0 - sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> escolha;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor, digite um numero." << std::endl;
            continue;
        }

        switch (escolha) {
            case 1:
                jogarContraPC();
                break;
            case 2:
                pvp();
                break;
            case 3:
                aiVsAi();
                break;
            case 0:
                std::cout << "Saindo do jogo." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
        }
    } while (escolha != 0);

    return 0;
}