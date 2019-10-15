#include "labirinto.h"
#include <iostream>
#include <string>

int main(int argc, char **argv){
	int height, width;
//	srand(time(NULL));
	if(argc == 1){
		//printf("uso: %s <arquivo>\n",argv[0]);
		//ESTA AQUI PARA DEBUG
		srand(0);
		int h,w;
		/*
		printf("height and width?");
		scanf(" %d %d",&h,&w);
		labirinto l(h,w);
		printf("how many walls? ");
		scanf(" %d",&h);
		l.nova_geracao(h);
		*/
		labirinto l(50,50);
		l.nova_geracao(30);
		l.print();
		l.write_labirinto("6.map");
		/*
		printf("would you like to print it? If so enter the name, otherwise, enter no\n");
		std::string name, no="no";
		std::cin >> name;
		if(name != no){
			name = "../mapas/" + name;
			l.write_labirinto(name.c_str());
		}
		*/
		return 0;
	}

	if(argc > 2){
		if(argv[1][0] == '1'){//Opcao de criar labirinto manualmente
			printf("digite numero de colunas e linhas\n");
			scanf("%d %d", &height, &width);
			labirinto l( height, width);
			l.gera_labirinto_manual(argv[2]);
			l.print();
		}else if(argv[1][0] == '2'){//Opcao de criar labirinto automatico
			int flag, numWall;
			srand(time(NULL));
			for(int i = 0; i < 20; i++){
				char filename[20];
				sprintf(filename, "%d.map", i);

				printf("Digite o numero de paredes:\n");
				scanf("%d", &numWall);
				labirinto l( 10, 10);
				l.nova_geracao(numWall);
				l.print();
				printf("1:Escreve no arquivo, 0: criar outro\n");
				if(scanf("%d",&flag) != EOF && flag == 1){//escreve o labirinto na saida de arquivo
					l.write_labirinto(filename);
				}else if(flag == 0){
					i--;
				}
			}
		}else if(argv[1][0] == '3'){//Opcao de abrir um labirinto e rodar um algoritimo sobre ele
			labirinto l(argv[2]);
			l.print();
		}
	}
	return 0;
}
