#include "best_first_search.h"
#define VISITED 1
#define NOT_VISITED 0

bool Best_first::check_start_wall(int column, int line){
	return (map[column][line] == BEGIN || map[column][line] == WALL);
}

Best_first::~Best_first(){
	//libera as coisas que foram malocadas
	for(int i = 0; i < enderecosUsados.size(); i++){
		free(enderecosUsados[i]);//libera os enderecos
	}
	enderecosUsados.clear();
	seqVisitados.clear();
	percursoLabirinto.clear();
}

void Best_first::inclui_proximo_vertice( no_t& children, double weight, std::pair<int,int> father,
                std::priority_queue<no_t, std::vector<no_t>, compare_best_first>& caminhos){
        children.father = {father.first, father.second};
        children.weight = weight;
        caminhos.push(children);
        seqVisitados.push_back(children.current);//Guarda os NO's visitados
}

void Best_first::setMap(labirinto &map){
	this->map = map;
}

const std::deque<std::pair<int,int>>& Best_first::getSequenciaDeVisitados() const{
	return seqVisitados;
}

void Best_first::reset(){
	map = labirinto(0,0);
	seqVisitados.clear();
}

void Best_first::setCaminhoLabirinto(no_t way[][], no_t fim){
	no_t atual = fim;
	do{
		this->percursoLabirinto.push_back(fim.current);
		atual = way[fim.father.first][fim.father.second];
	}while(atual.father != {-1,-1});//Ponto de parada, quando o ponto ver que o ponto de origem nao tem pai
}

int heuristic(std::pair<int,int> end, std::pair<int,int>current){
	double dx = abs(current.first - end.first);//columns
	double dy = abs(current.second - end.second);//lines
	return sqrt(dx*dx + dy*dy);
}

std::vector<std::pair<int,int>> Best_first::executar(){ 
	std::priority_queue<no_t*, std::vector<no_t*>, compare_best_first> caminhos;

	double time;
	char flagUp, flagDown, flagLeft, flagRight;
	int height = map.getHeight(), width = map.getWidth();
	char mapVisited[height][width];
	no_t way[height][width];
	std::pair<int,int> end = map.getEnd();

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			mapVisited[i][j] = NOT_VISITED;
			way[i][j].current = {i,j}
			way[i][j].father = {-1,-1};
		}
	}

	inclui_proximo_vertice(way[getStart().first][map.getStart().second], heuristic(end, map.getStart()), caminhos);
	while(!caminhos.empty()){
		vert = caminhos.top();
		caminhos.pop();
		if(map[vert.current.first][vert.current.second] != END){
			flagUp = (vert.current.first+1 < height);
			flagDown = (vert.current.first-1 >= 0);
			flagLeft = (vert.current.second-1 >= 0);
			flagRight = (vert.current.second+1 < width);

			if(flagUp && !check_start_wall(vert.current.first+1, vert.current.second) 
					&& mapVisited[vert.current.first+1][vert.current.second] != VISITED){
				inclui_proximo_vertice(way[vert.current.first+1][vert.current.second], 
						heuristic(end, {vert.current.first+1,vert.current.second}), vert.current, caminhos);
				mapVisited[vert.current.first+1][vert.current.second] = VISITED;
			}
			if(flagDown && !check_start_wall(vert.current.first-1, vert.current.second) 
					&& mapVisited[vert.current.first-1][vert.current.second] != VISITED){
				inclui_proximo_vertice(way[vert.current.first-1][vert.current.second], 
						heuristic(end, {vert.current.first-1,vert.current.second}), vert.current, caminhos);
				mapVisited[vert.current.first-1][vert.current.second] = VISITED;
			}
			if(flagRight && !check_start_wall(vert.current.first, vert.current.second+1)
					&& mapVisited[vert.current.first][vert.current.second+1] != VISITED){
				inclui_proximo_vertice(map[vert.current.first][vert.current.second+1],
						heuristic(end, {vert.current.first, vert.current.second+1}), vert.current, caminhos);
				mapVisited[vert.current.first][vert.current.second+1] = VISITED;
			}
			if(flagLeft && !check_start_wall(vert.current.first, vert.current.second-1)
					&& mapVisited[vert.current.first][vert.current.second-1] != VISITED){
				inclui_proximo_vertice(way[vert.current.first][vert.current.second-1],
						heuristic(end, {vert.current.first, vert.current.second-1}), vert.current, caminhos);
				mapVisited[vert.current.first][vert.current.second-1] = VISITED;
			}
			if(flagUp && flagRight && !check_start_wall(vert.current.first+1, vert.current.second+1)
					&& mapVisited[vert.current.first+1][vert.current.second+1] != VISITED){
				inclui_proximo_vertice(way[vert.current.first+1][vert.current.second+1], 
						heuristic(end, {vert.current.first+1, vert.current.second+1}), vert.current, caminhos);
				mapVisited[vert.current.first+1][vert.current.second+1] = VISITED;
			}
			if(flagUp && flagLeft && !check_start_wall(vert.current.first+1, vert.current.second-1)
					&& mapVisited[vert.current.first+1][vert.current.second-1] != VISITED){
				inclui_proximo_vertice(way[vert.current.first+1][vert.current.second-1], 
						heuristic(end, {vert.current.first+1, vert.current.second-1}), vert.current, caminhos);
				mapVisited[vert.current.first+1][vert.current.second-1] = VISITED;
			}
			if(flagDown && flagRight && !check_start_wall(vert.current.first-1, vert.current.second+1)
					&& mapVisited[vert.current.first-1][vert.current.second+1] != VISITED){
				inclui_proximo_vertice(way[vert.current.first-1][vert.current.second+1], 
						heuristic(end, {vert.current.first-1, vert.current.second+1}), vert.current, caminhos);
				mapVisited[vert.current.first-1][vert.current.second+1] = VISITED;
			}
			if(flagDown && flagLeft && !check_start_wall(vert.current.first-1, vert.current.second-1)
					&& mapVisited[vert.current.first-1][vert.current.second-1] != VISITED){
				inclui_proximo_vertice(way[vert.current.first-1][vert.current.second-1], 
						heuristic(end, {vert.current.first-1, vert.current.second-1}), vert.current, caminhos);
				mapVisited[vert.current.first-1][vert.current.second-1] = VISITED;
			}
			mapVisited[vert.current.first][vert.current.second] = VISITED;
		}else if(map[vert.current.first][vert.current.second] == END){
			setCaminhoLabirinto(way, vert.current);//Coloca em percursoLabirinto o caminho ateh a saida
			return this->percursoLabirinto;
		}
	}
	return this->percursoLabirinto;
}
