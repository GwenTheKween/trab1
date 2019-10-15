#include "labirinto.h"
#include "interface_init.h"
#include "interface_labirinto.h"
#include "a_star.h"
#include "best_first_search.h"

#include <iostream>
#include <string>

void solve(labirinto& m){
	A_star searcher(m);
	std::vector<std::pair<int, int> >v;
	v = searcher.executar();
	for(auto it = v.rbegin(); it != v.rend(); it++){
		printf("(%d,%d) ",it->first, it->second);
	}
	printf("\n");
}

int main(int argc, char **argv){
	int height, width;
//	srand(time(NULL));
	if(argc == 1){
		//ESTA AQUI PARA DEBUG
		/*
		srand(0);
		int h,w;
		labirinto l(50,50);
		l.nova_geracao(30);
		l.print();
		*/
		labirinto m("../mapas/1.map");
		m.print();
		solve(m);
		return 0;
	}
	else if(argc == 2){
		labirinto m(argv[1]);
		m.print();
		solve(m);
	}else{
		if(argv[1][0] == '1'){//Opcao de criar labirinto manualmente
			printf("digite numero de colunas e linhas\n");
			scanf("%d %d", &height, &width);
			labirinto l( height, width);
			l.gera_labirinto_manual(argv[2]);
			l.print();
		}else if(argv[1][0] == '2'){//Opcao de criar labirinto automatico
		  //	printf("digite numero de colunas e linhas o\n");
		  //	scanf("%d %d", &height, &width);
			labirinto l( height, width);
			l.nova_geracao(atoi(argv[2]));
			l.print();
		}else if(argv[1][0] == '3'){//Opcao de abrir um labirinto e rodar um algoritimo sobre ele
			labirinto l(argv[2]);
			l.print();
		}else if(argv[1][0] == '4'){
			Best_first a;
			labirinto l(argv[2]);
			a.setMap(l);
			l.print();
			a.executar();
		}
	}
	return 0;
}
