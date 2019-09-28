#include "labirinto.h"

int main(int argc, char **argv){
	if(argc < 2){
		printf("uso: %s <arquivo>",argv[0]);
		return 0;
	}
	if(argv[1][0] == '1'){//Opcao de criar labirinto manualmente
		if(argc < 4){
			printf("faltam parametros, use: %s 1 <altura matriz> <largura matriz>\n", argv[0]);
			return 0;
		}

		labirinto l( atoi(argv[2]), atoi(argv[3]));
		l.gera_labirinto_manual();
	}else if(argv[1][0] == '2'){//Opcao de criar labirinto automatico
		if(argc < 4){
			printf("faltam parametros, use: %s 1 <altura matriz> <largura matriz>\n", argv[0]);
			return 0;
		}

		labirinto l( atoi(argv[2]), atoi(argv[3]));
		l.gera_labirinto_automatico();
	}else if(argv[1][0] == '3'){//Opcao de abrir um labirinto e rodar um algoritimo sobre ele
		labirinto l(argv[2]);
		l.print();
	}
	return 0;
}
