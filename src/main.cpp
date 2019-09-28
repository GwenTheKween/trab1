#include "labirinto.h"

int main(int argc, char **argv){
	if(argc < 2){
		printf("uso: %s <arquivo>",argv[0]);
		return 0;
	}
	if(argv[1][0] == '1'){//Opcao de criar labirinto manualmente
		
	
	}else if(argv[1][0] == '2'){//Opcao de criar labirinto automaticamente


	}else if(argv[1][0] == '3'){//Opcao de abrir um labirinto e rodar um algoritimo sobre ele
		labirinto l(argv[2]);
		l.print();
	}
	return 0;
}
