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
		fclose(input);
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

void labirinto::write_labirinto(char* filename){
	FILE* output;
	output = fopen(filename, "w");
	if(! output){
		printf("Unable to open file");
	}else {
		char c;
		fprintf(output, "%d %d\n", height, width);
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				c = map_infoToChar(map[i][j]);
				fprintf(output, "%c", c);
			}
			fprintf(output, "\n");
		}
		fclose(output);
	}
}

int labirinto::check_num_wall(int column, int line){
	int wall = 0;
	wall += (column-1 >= 0 && (map[column-1][line] == WALL ||
			map[column-1][line] == BEGIN || 
			map[column-1][line] == END) );
	
	wall += (line-1 >= 0 && (map[column][line-1] == WALL ||
			map[column][line-1] == BEGIN || 
			map[column][line-1] == END) );

	wall += (column+1 < height && (map[column+1][line] == WALL ||
			map[column+1][line] == BEGIN || 
			map[column+1][line] == END) );

	wall += (line+1 < width && (map[column][line+1] == WALL ||
			map[column][line+1] == BEGIN || 
			map[column][line+1] == END) );

	return wall;
}

bool labirinto::check_start_end(int column, int line){
	return (map[column][line] == END || map[column][line] == BEGIN);
}

void labirinto::gera_labirinto_automatico(char* filename){
	int column, line, direcao;
	int numWall, numMaxWall = height*width;

	/* Seleciona um ponto aleatorio, verifica se tem como incluir paredes
	 * A partir dele*/
	for(int count = 0; count < 9; ){
		column =  rand() % height;
		line = rand() % width;
		if(check_num_wall(column, line) >= 1 || check_start_end(column, line)){
			count++;
		}else{
			map[column][line] = WALL;

			//Pega um numero aleatorio de paredes para tentar preencher
			numWall = rand()%numMaxWall;
			for(int i = 0; i < numWall; i++){
				direcao = rand() % 4;

				//Verifica na nova posicao quantas paredes tem
				//Se tiver apenas uma(posicao anterior da parede)
				//Entao inclui a parede
				//A nova posicao nao vai ateh as bordas do labirinto
				if(direcao == 0 && column-1 > 0 && check_num_wall(column-1, line) <= 1){ //up
					column = column-1;
					map[column][line] = WALL;
				}else if(direcao == 1 && line-1 > 0 && check_num_wall(column, line-1) <= 1){//left
					line = line-1;
					map[column][line] = WALL;
				}else if(direcao == 2 && line+1 < width-1 && check_num_wall(column, line+1) <= 1){//right
					line = line+1;
					map[column][line] = WALL;
				}else if(direcao == 3 && column+1 < height-1 && check_num_wall(column+1, line) <= 1){//down
					column = column+1;
					map[column][line] = WALL;
				}
			}
		}
	}

	do{
		column = rand() % height;
		line = rand() % width;
		if(map[column][line] == FREE_SPACE)
			map[column][line] = BEGIN;
	}while(map[column][line] != BEGIN);

	do{
		column = rand() % height;
		line = rand() % width;
		if(map[column][line] == FREE_SPACE)
			map[column][line] = END;
	}while(map[column][line] != END);

	print();
	printf("\n");
	write_labirinto(filename);

}

/* Le a entrada do usuario e desenha uma reta
 * no labirinto, que representa as paredes. Continua enquanto nao for digitado valor NEGATIVO no inicio.
 * Para desenhar a reta o usuario repassa 2 parametros: 
 * Posicao inicial da parede: <coluna> <linha>
 * Posicao final da parede: <coluna> <linha>
 * Restricao: Nao faz reta na diagonal*/
void labirinto::gera_labirinto_manual(char* filename){
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

	write_labirinto(filename);
}

void labirinto::nova_geracao(int wallCount){
	//o inicio sempre estara no topo a esquerda, e o final no canto inferior esquerdo
	std::pair<int,int> start(rand()%(width/5), rand()%(height/5)), end(rand()%(width/5) + 4*width/5, rand()%(height/5) + 4*height/5);

	std::vector<parede> walls;

	map[start.first][start.second] = BEGIN;
	map[end.first][end.second] = END;

	//gera 4 paredes para o contorno do mapa, das colunas -1 e w/h
	//parede superior do mapa
	walls.push_back(parede(-1,-1,width,-1));
	//parede direita do mapa
	walls.push_back(parede(width, -1, width, height));
	//parede inferior do mapa
	walls.push_back(parede(width, height, -1, height));
	//parede esquerda do mapa
	walls.push_back(parede(-1, height, -1, -1));

	while(wallCount--){
		/*
		 *Outline do algoritmo: Escolha uma parede existente, e um ponto nessa parede. 
		 *A partir desse ponto, escolhe outro aleatorio e cria uma parede entre esses 2
		 */

		//de qual parede a nova sera criada
		int wallOriginIndex = rand() % walls.size();
		parede wallOrigin = walls[wallOriginIndex];

		//decide para qual direção a nova parede sera criada
		int whereInWall = rand() % wallOrigin.getLength();//a qual altura a nova parede sera criada
		std::pair<int, int> newCoord;
		if(wallOrigin.getDirection() == VERTICAL){
			newCoord = std::make_pair(	wallOrigin.getStart().first, 
										whereInWall + wallOrigin.getStart().second);
			int dir[2];
			//A parede nova sera horizontal
			//Primeiro checa se eh possivel criar uma parede para a esquerda
			if(newCoord.first > 0){
				//calcula qual o tamanho maximo da parede nessa direcao. se for 1, nao eh possivel fazer a parede.
				for(dir[0] = 1; isFree(newCoord.first - dir[0], newCoord.second); dir[0]++);
			}else dir[0] = 0;
			//depois, checa se eh possivel criar uma parede para a direita;
			if(newCoord.first < width){
				//calcula qual o tamanho maximo da parede nessa direcao. se for 1, nao eh possivel fazer a parede.
				for(dir[1] = 1; isFree(newCoord.first + dir[0], newCoord.second); dir[1]++);
			}else dir[1] = 0;

			int d;
			//escolhe uma direcao para a nova parede
			if((dir[0] <2) && (dir[1] < 2)){ //nenhuma direcao eh possivel
				wallCount++;
				continue;
			}else if(dir[0] < 2){ // nao pode ir para esquerda
				d = 1;
			}else if(dir[1] < 2){ //nao pode ir para direita
				d = 0;
			}else{
				d = rand()%2;
			}

			if(d == 0){
				int l = rand()%(dir[0] - 1) + 1;//garante que a parede tera tamanho pelo menos 1
				std::pair<int,int> wallEnd(newCoord.first - l, newCoord.second);
				walls.push_back(create_wall(newCoord,wallEnd));
			}
			else{
				int l = rand() % (dir[1] - 1) + 1;//garante que a parede tera tamanho pelo menos 1
				std::pair<int,int> wallEnd(newCoord.first + l, newCoord.second);
				walls.push_back(create_wall(newCoord, wallEnd));
			}
		}else{
			newCoord = std::make_pair(	wallOrigin.getStart().first + whereInWall,
										wallOrigin.getStart().second);
			//A parede nvoa sera horizontal
			int dir[2];
			//primeiro checa se eh possivel criar uma parede para cima
			if(newCoord.second > 0){
				//calcula o tamanho maximo da parede nessa direção. O tamanho maximo deve ser maior que 1
				for(dir[0] = 1; isFree(newCoord.first, newCoord.second - dir[0]); dir[0]++);
			}else dir[0] = 0;
			//depois checa se eh possivel criar a parede para baixo
			if(newCoord.second < height){
				for(dir[1] = 1; isFree(newCoord.first, newCoord.second + dir[1]); dir[1]++);
			}else dir[1] = 0;

			int d;
			//analisa quais opcoes de parede sao viaveis, e escolhe uma delas aleatoriamente (se possivel)
			if((dir[0] < 2) && (dir[1] < 2)){//nenhuma direcao eh possivel, ABORT
				wallCount ++;
				continue;
			}else if(dir[0] < 2){//nao pode ir para cima
				d = 1;
			}else if(dir[1] < 2){//nao pode ir para baixo
				d = 0;
			}else{
				d = rand()%2;
			}

			if(d == 0){
				int l = rand()%(dir[0] - 1) + 1; //garante um tamanho de pelo menos 1
				std::pair<int, int> wallEnd(newCoord.first, newCoord.second - l);
				walls.push_back(create_wall(newCoord, wallEnd));
			}else{
				int l = rand()%(dir[1] - 1) + 1;
				std::pair<int, int> wallEnd(newCoord.first, newCoord.second + l);
				walls.push_back(create_wall(newCoord,wallEnd));
			}
		}
	}
}

int labirinto::getWidth(){
    return this->width;
}

int labirinto::getHeight(){
    return this->height;
}

bool labirinto::isFree(int x, int y){
	if((x < 0) || (y < 0) || (x >= width) || (y >= height)) return false;
	return ((*this)[std::make_pair(x,y)] == FREE_SPACE);
}

parede labirinto::create_wall(std::pair<int, int> start, std::pair<int, int> end){
	parede newWall(start,end);

	if(newWall.getDirection()== VERTICAL){
		for(int y = newWall.getStart().second + 1; y < newWall.getEnd().second; y++){ //comeca com +1 pq se for +0 ja vai ter parede, ou out_of_bounds exception
			map[start.first][y] = WALL;
		}
	}else{
		for(int x = newWall.getStart().first + 1; x < newWall.getEnd().first; x++){
			map[x][start.second] = WALL;
		}
	}
	return parede(start,end);
}
