#include "labirinto.h"

int main(int argc, char **argv){
	int height, width;
	if(argc < 2){
		printf("uso: %s <arquivo>",argv[0]);
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
		printf("digite numero de colunas e linhas\n");
		scanf("%d %d", &height, &width);
		labirinto l( height, width);
		l.gera_labirinto_automatico(argv[2]);
	}else if(argv[1][0] == '3'){//Opcao de abrir um labirinto e rodar um algoritimo sobre ele
		labirinto l(argv[2]);
		l.print();
	}
	return 0;
}
