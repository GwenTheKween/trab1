#include "labirinto.h"

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

void labirinto::gera_labirinto_automatico(){

}

void labirinto::gera_labirinto_manual(){

}
