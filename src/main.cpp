#include "labirinto.h"
#include "interface_init.h"
#include "interface_labirinto.h"


int main(int argc, char **argv){


	if(argc < 2){
		printf("uso: %s <arquivo>",argv[0]);
        return 1;
	}
    InterfaceInit inicializador;
    WINDOW *aux = newwin(1, COLS , LINES-1,0);
	labirinto l(argv[1]);
    InterfaceLabirinto lab({0,0} , LINES-5 , COLS, l); // cria o labirinto.
    lab.refresh(); // escreve na tela.
    wgetch(aux);
    lab.definiPosicao({47,3} , GREEN_BLUE); // define uma nova posição no lab
    lab.refresh();// escreve na tela.
    wrefresh(aux); // sem esse ele não tira o cursor do lab. Vou dar uma olhada nas confs do ncurses deve ser o echo da letra na tela
    wgetch(aux);

	l.print();
	return 0;
}
