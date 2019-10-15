#include "labirinto.h"
#include "interface_init.h"
#include "interface_geral.h"

#include <iostream>
#include <string>

int main(int argc, char **argv){
	int height, width;
//	srand(time(NULL));
	if(argc == 1){
        char aux;
        std::cout << "por favor coloque o terminal em tela cheia e aperte uma tecla\n";
        std::cin.read(&aux , 1);
        InterfaceInit initNcurses;
        interfaceGeral geral;
        geral();
	}

	if(argc > 2){
		if(argv[1][0] == '1'){//Opcao de criar labirinto manualmente
			printf("digite numero de colunas e linhas\n");
			scanf("%d %d", &height, &width);
			labirinto l( height, width);
			l.gera_labirinto_manual(argv[2]);
			l.print();
		}else if(argv[1][0] == '2'){//Opcao de criar labirinto automatico
	//  	printf("digite numero de colunas e linhas\n");
	//  	scanf("%d %d", &height, &width);
			labirinto l( 50, 50);
			l.nova_geracao(atoi(argv[2]));
			l.print();
		}else if(argv[1][0] == '3'){//Opcao de abrir um labirinto e rodar um algoritimo sobre ele
			labirinto l(argv[2]);
			l.print();
		}
	}
	return 0;
}
