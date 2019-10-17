#include "interface_geral.h"
#include "interface_labirinto.h"
#include "labirinto.h"
#include "search.h"
#include "a_star.h"
#include "best_first_search.h"
#include "dfs.h"
#include "bfs.h"

#include <ncurses.h>
#include <functional>

#define MENU_LARGURA 15
#define COMANDOS_ALTURA 1


interfaceGeral::interfaceGeral(){};
interfaceGeral::~interfaceGeral(){};


void interfaceGeral::operator()(){
    // janela que contem o menu e suas configurações para teclas e echo de teclas digitadas.
    WINDOW *menu = newwin(LINES - COMANDOS_ALTURA , MENU_LARGURA , 0 , COLS - MENU_LARGURA);
    keypad(menu , TRUE);
    noecho();

    // variavel para saber se a o mapa foi definido.
    bool labirintoIsSet = false;
    //textos dos menus
    std::array<std::string , 7> itens{"gera mapa" , "A*" , "best first" , "BFS" , "DFS" , "Andar" , "Sair"};

    // janela para entrada de comandos e saida de texto
    WINDOW *comandos = newwin(COMANDOS_ALTURA , COLS , LINES -COMANDOS_ALTURA , 0);

    labirinto *l = new labirinto(0,0);
    InterfaceLabirinto *iLab = new InterfaceLabirinto({0,0} ,LINES -COMANDOS_ALTURA , COLS -MENU_LARGURA , *l);

    //função da busca
    auto executaLabirinto = [&] (Search *busca) -> void {
        bool para = true;
        auto caminhoFinal = busca->executar();
        auto caminhoPercorrido = busca->getSequenciaDeVisitados();
        iLab->reset();
        wprintw(comandos , "aperte qualquer tecla para dar mais um passo no algoritmo ou s para rodar todos os passos");
        wrefresh(comandos);
        for(auto &it : caminhoPercorrido){
            iLab->definiPosicao(it , RED_BLACK);
            iLab->refresh();
            if(para){
                wrefresh(comandos);
                para = wgetch(comandos) != 's';
            }
        }
        for(auto &it : caminhoFinal){
            iLab->definiPosicao(it , BLUE_BLACK);
            iLab->refresh();
        }
        wmove(comandos , 0,0);
        wclrtoeol(comandos );
        wrefresh(comandos);
    };
    // função para gerar labirintos.
    auto geraLabirinto = [&] () -> void {
        int w, h , wallCount;
        echo();
        wprintw(comandos , "informe o tamanho do labirinto (<num> <num>): ");
        wscanw(comandos , "%d  %d" , &w , &h);
        mvwprintw(comandos , 0,0 ,"informe a quantidade de paredes: ");
        wclrtoeol(comandos);
        wscanw(comandos , "%d" , &wallCount);
        noecho();
        wmove(comandos , 0 , 0);
        wclrtoeol(comandos);
        wrefresh(comandos);
        // aqui gera o labirinto
        delete l;
        l = new labirinto(h ,w );
        l->nova_geracao(wallCount < 10 + 2*h/10 ? wallCount : 10 + 2*h/10);
        delete iLab;
        labirintoIsSet = true;
        iLab = new InterfaceLabirinto({0,0} ,LINES -1 , COLS -10 , *l);
        iLab->refresh();
    };

    // funções para executar as buscas
    auto executaA_star = [&] () -> void {
        if(labirintoIsSet){
            A_star a(*l);
            executaLabirinto(&a);
        }
    };
    auto executaBestFirstSearch = [&] () -> void {
        if(labirintoIsSet){
            Best_first bf;
            bf.setMap(*l);
            executaLabirinto(&bf);
        }
    };
    auto executaBFS = [&] () -> void {
        if(labirintoIsSet){
            bfsSearch bfs;
            bfs.setMap(*l);
            executaLabirinto(&bfs);
        }
    };
    auto executaDFS = [&] () -> void {
        if(labirintoIsSet){
            dfsSearch dfs;
            dfs.setMap(*l);
            executaLabirinto(&dfs);
        }
    };


    // código para escrever o menu, pela posicao_atual é definido qual menu está selecionado
    // então ele é pintado diferente dos outros.
    int posicao_atual = 0;
    {
        auto &str = itens[posicao_atual];
        wmove(menu,(LINES -COMANDOS_ALTURA)/2-2+posicao_atual , (MENU_LARGURA - str.size())/2 );
        wattron(menu , COLOR_PAIR(BLACK_WHITE));
        wprintw(menu,"%s" , itens[posicao_atual].c_str());
        wattroff(menu , COLOR_PAIR(BLACK_WHITE));
    }
    bool continua = true;
    for(unsigned int i = 1 ; i < itens.size() ; i++){
        auto &str = itens[i];
        wmove(menu,(LINES -COMANDOS_ALTURA)/2-2+i , (MENU_LARGURA - str.size())/2 );
        wprintw(menu,"%s" , itens[i].c_str());
    }
    while(continua){
        int caracter = wgetch(menu);
        {
            auto &str = itens[posicao_atual];
            wmove(menu,(LINES -COMANDOS_ALTURA)/2-2+posicao_atual , (MENU_LARGURA - str.size())/2 );
            wprintw(menu,"%s" , itens[posicao_atual].c_str());
        }
        // aqui é definido o que cada tecla vai fazer no menu.
        if(KEY_DOWN == caracter){
            if(posicao_atual < 6)
                posicao_atual++;
        }else if(KEY_UP == caracter){
            if(posicao_atual > 0)
                posicao_atual--;
        }else if(caracter == 10 || caracter == KEY_ENTER){// enter indica que um item do menu foi selecionado
            // escolhe qual item do menu foi selecionado
            if(posicao_atual == 0){
                geraLabirinto();
            }else if(posicao_atual == 1){
                executaA_star();
            }else if(posicao_atual == 2){
                executaBestFirstSearch();
            }else if(posicao_atual == 3){
                executaBFS();
            }else if(posicao_atual == 4){
                executaDFS();
            }else if(posicao_atual == 5){
                wprintw(comandos , "Aperte esc para voltar ao menu");
                wrefresh(comandos);
                iLab->andarPeloLabirinto();
                wmove(comandos , 0,0);
                wclrtoeol(comandos);
                wrefresh(comandos);
            }else if(posicao_atual == 6){
                continua = false;
            }
        }
        {
            auto &str = itens[posicao_atual];
            wmove(menu,(LINES -COMANDOS_ALTURA)/2-2+posicao_atual , (MENU_LARGURA - str.size())/2 );
            wattron(menu , COLOR_PAIR(BLACK_WHITE));
            wprintw(menu,"%s" , itens[posicao_atual].c_str());
            wattroff(menu , COLOR_PAIR(BLACK_WHITE));
        }
        wrefresh(menu);
    }
};
