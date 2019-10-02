#include "labirinto.h"

int main(int argc, char **argv){
	int height, width;
	if(argc < 2){
		//printf("uso: %s <arquivo>\n",argv[0]);
		//ESTA AQUI PARA DEBUG
		labirinto l(10,10);
		l.nova_geracao(2);
		l.print();
		return 0;
	}

	if(argv[1][0] == '1'){//Opcao de criar labirinto manualmente
		printf("digite numero de colunas e linhas\n");
		scanf("%d %d", &height, &width);
		labirinto l( height, width);
		l.gera_labirinto_manual(argv[2]);
		l.print();
	}else if(argv[1][0] == '2'){//Opcao de criar labirinto automatico
		srand(time(NULL));
//  	printf("digite numero de colunas e linhas\n");
//  	scanf("%d %d", &height, &width);
		labirinto l( 50, 50);
		l.nova_geracao(atoi(argv[2]));
		l.print();
	}else if(argv[1][0] == '3'){//Opcao de abrir um labirinto e rodar um algoritimo sobre ele
		labirinto l(argv[2]);
		l.print();
	}
	return 0;
}
