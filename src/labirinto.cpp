#include "labirinto.h"
#include <time.h>
//=================================================================================================================
//Funcoes internas, para facilitar a conversao.

char map_infoToChar(MAP_INFO m){
	switch(m){
		case FREE_SPACE:
			return '*';
		case WALL:
			return '-';
		case BEGIN:
			return '#';
		case END:
			return '$';
		default:
			return 0;
	}
}

MAP_INFO charToMap_info(char c){
	switch(c){
		case '*':
			return FREE_SPACE;
		case '-':
			return WALL;
		case '#':
			return BEGIN;
		case '$':
			return END;
		default:
			return ERROR;
	}
}

//=================================================================================================================
//implementacoes para a classe labirinto


labirinto::labirinto(int h, int w)
{
	resize(h,w);
}

labirinto::labirinto(char* filename){
	FILE* input;
	input = fopen(filename, "r");
	if(! input){
		printf("Unable to open file");
	}else{
		int w,h;
		char c;
		fscanf(input,"%d %d",&h,&w);
		resize(h,w);
		for(int i = 0; i<h; i++){
			for(int j = 0; j<w; j++){
				fscanf(input," %c",&c);
				map[i][j] = charToMap_info(c);
			}
		}
	}
}

void labirinto::resize(int h, int w){
	height = h;
	width = w;
	std::vector<MAP_INFO> tmp;
	map.resize(h);
	tmp.resize(w,FREE_SPACE);
	for(int i=0; i<h; i++){
		map[i] = tmp;
	}
}

void labirinto::print(){
	int i, j;
	for(i = 0; i<height; i++){
		for(j = 0; j<width; j++){
			printf("%c",map_infoToChar(map[i][j]));
		}
		printf("\n");
	}
}

void labirinto::write_labirinto(){
	FILE* arq;
}

int labirinto::check_num_wall(int column, int line){
	int wall = 0;
	wall += (column-1 >= 0 && (map[column-1][line] == WALL ||
			map[column-1][line] == BEGIN || 
			map[column-1][line] == END) );
	
	wall += (line-1 >= 0 && (map[column][line-1] == WALL ||
			map[column][line-1] == BEGIN || 
			map[column][line-1] == END) );

	wall += (column+1 >= 0 && (map[column+1][line] == WALL ||
			map[column+1][line] == BEGIN || 
			map[column+1][line] == END) );

	wall += (line+1 >= 0 && (map[column][line+1] == WALL ||
			map[column][line+1] == BEGIN || 
			map[column][line+1] == END) );

	return wall;
}

void labirinto::gera_labirinto_automatico(){
	int column, line;
	int numWall, numMaxWall = 10;

	srand(time(NULL));

	/* Pega um ponto aleatorio, verifica se tem como incluir paredes
	 * A partir dele. Se ocorrer de não poder */
	for(int count = 0; count < 5; ){
		column = rand() % height;
		line = rand() % width;

		if(check_num_wall(column, line) >= 1)
			count++;
		else{
			//Pega um numero aleatorio de paredes para tentar preencher
			numWall = rand()%numMaxWall;		
			for(int i = 0; i < numWall; i++){
				//fazer...
				//verificar posicao e preencher, mudando a linha e posicao...
			}
		}
	}
}

/* Le a entrada do usuario e desenha uma reta
 * no labirinto, que representa as paredes. Continua enquanto nao for digitado valor NEGATIVO no inicio.
 * Para desenhar a reta o usuario repassa 2 parametros: 
 * Posicao inicial da parede: <coluna> <linha>
 * Posicao final da parede: <coluna> <linha>
 * Restricao: Nao faz reta na diagonal*/
void labirinto::gera_labirinto_manual(){
	int cInitial, lInitial, cEnd, lEnd;
	int inicio, fim;
	printf("informe:  <coluna Inicial> <linha Inicial> <coluna final> <linha final>\n");

	while(scanf("%d", &cInitial) && cInitial >= 0){
		scanf("%d %d %d", &lInitial, &cEnd, &lEnd);
		if(cInitial >= height || cEnd >= height || lInitial >= width || lEnd >= width
				|| cEnd < 0 || lInitial < 0 || lEnd < 0){
			printf("Esses parametros violam as propriedades do labirinto.\n");
		}else if(cInitial == cEnd){
			if(lInitial < lEnd){
				inicio = lInitial; 
				fim = lEnd;
			}else{
				inicio = lEnd; 
				fim = lInitial;
			}

			for(int j = inicio; j <= fim; j++){
				map[cInitial][j] = WALL;
			}
		}else if(lInitial == lEnd){
			if(cInitial < cEnd){
				inicio = cInitial;
			       	fim = cEnd;
			}else{
				inicio = cEnd;
			       	fim =  cInitial;
			}

			for(int i = inicio; i <= fim; i++){
				map[i][lInitial] = WALL;
			}
		}
		print();
		printf("\n");
	}

	write_labirinto();
}

