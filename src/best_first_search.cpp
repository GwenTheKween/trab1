#include "best_first_search.h"
#define VISITED 1
#define NOT_VISITED 0

bool Best_first::check_start_wall(int column, int line){
	return (map[column][line] == BEGIN || map[column][line] == WALL);
}

Best_first::~Best_first(){
	//libera as coisas que foram malocadas
	seqVisitados.clear();
	percursoLabirinto.clear();
}

void Best_first::inclui_proximo_vertice( no_t& children, double weight, std::pair<int,int>& father,
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

void Best_first::setCaminhoLabirinto(std::vector< std::vector<no_t> > way, no_t fim){
	no_t atual = fim;
	std::pair<int,int> pontoDeParada = {-1,-1};
	while(atual.father != pontoDeParada){//Ponto de parada, quando o ponto ver que o ponto de origem nao tem pai
		this->percursoLabirinto.push_back(atual.current);
		atual = way[atual.father.first][atual.father.second];
	}
	this->percursoLabirinto.push_back(atual.current);
}

double heuristic(std::pair<int,int> end, std::pair<int,int>current){
	double dx = abs(current.first - end.first);//columns
	double dy = abs(current.second - end.second);//lines
	return sqrt(dx*dx + dy*dy);
}

std::vector<std::pair<int,int>> Best_first::executar(){ 
	std::priority_queue<no_t, std::vector<no_t>, compare_best_first> caminhos;

	double time;
	char flagUp, flagDown, flagLeft, flagRight;
	int height = map.getHeight(), width = map.getWidth();
	char mapVisited[height][width];
	std::vector< std::vector<no_t> > way(height, std::vector<no_t>(width));
	std::pair<int,int> end = map.getEnd();
	no_t vert;

	std::pair<int,int> auxiliar = {-1,-1};
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			mapVisited[i][j] = NOT_VISITED;
			way[i][j].current = {i,j};
			way[i][j].father = auxiliar;
		}
	}

	inclui_proximo_vertice(way[map.getStart().first][map.getStart().second], heuristic(end, map.getStart()), auxiliar, caminhos);
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
				inclui_proximo_vertice(way[vert.current.first][vert.current.second+1],
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
			setCaminhoLabirinto(way, vert);//Coloca em percursoLabirinto o caminho ateh a saida
			return this->percursoLabirinto;
		}
	}
	return this->percursoLabirinto;
}
