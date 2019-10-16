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

void Best_first::inclui_proximo_vertice(int nextColumn, int nextLine, double weight, no_t* father,
		std::priority_queue<no_t*, std::vector<no_t*>, compare_best_first>& caminhos){
	no_t* nextVert = (no_t*)malloc(sizeof(no_t));
	nextVert->column = nextColumn;
	nextVert->line = nextLine;
	nextVert->weight = weight;
	nextVert->father = father;
	caminhos.push(nextVert);
	enderecosUsados.push_back(nextVert);
	seqVisitados.push_back(std::pair<int, int>(nextColumn, nextLine));//Guarda os NO's visitados
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

void Best_first::setCaminhoLabirinto(no_t* origem){
	no_t* atual = origem;
	while(atual != NULL){
		this->percursoLabirinto.push_back(std::pair<int,int>(atual->column, atual->line));
		atual = atual->father;
	}
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
	no_t* vert;
	std::pair<int,int> end = map.getEnd();

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			mapVisited[i][j] = NOT_VISITED;
		}
	}


	inclui_proximo_vertice(map.getStart().first, map.getStart().second, heuristic(end, map.getStart()), NULL, caminhos);
	while(!caminhos.empty()){
		vert = caminhos.top();
		caminhos.pop();
		if(map[vert->column][vert->line] != END){
			flagUp = (vert->column+1 < height);
			flagDown = (vert->column-1 >= 0);
			flagLeft = (vert->line-1 >= 0);
			flagRight = (vert->line+1 < width);

			if(flagUp && !check_start_wall(vert->column+1, vert->line) 
					&& mapVisited[vert->column+1][vert->line] != VISITED){
				inclui_proximo_vertice(vert->column+1, vert->line, heuristic(end, {vert->column+1,vert->line}), vert, caminhos);
				mapVisited[vert->column+1][vert->line] = VISITED;
			}
			if(flagDown && !check_start_wall(vert->column-1, vert->line) 
					&& mapVisited[vert->column-1][vert->line] != VISITED){
				inclui_proximo_vertice(vert->column-1, vert->line, heuristic(end, {vert->column-1,vert->line}), vert, caminhos);
				mapVisited[vert->column-1][vert->line] = VISITED;
			}
			if(flagRight && !check_start_wall(vert->column, vert->line+1)
					&& mapVisited[vert->column][vert->line+1] != VISITED){
				inclui_proximo_vertice(vert->column, vert->line+1, heuristic(end, {vert->column, vert->line+1}), vert, caminhos);
				mapVisited[vert->column][vert->line+1] = VISITED;
			}
			if(flagLeft && !check_start_wall(vert->column, vert->line-1)
					&& mapVisited[vert->column][vert->line-1] != VISITED){
				inclui_proximo_vertice(vert->column, vert->line-1, heuristic(end, {vert->column, vert->line-1}), vert, caminhos);
				mapVisited[vert->column][vert->line-1] = VISITED;
			}
			if(flagUp && flagRight && !check_start_wall(vert->column+1, vert->line+1)
					&& mapVisited[vert->column+1][vert->line+1] != VISITED){
				inclui_proximo_vertice(vert->column+1, vert->line+1, heuristic(end, {vert->column+1, vert->line+1}), vert, caminhos);
				mapVisited[vert->column+1][vert->line+1] = VISITED;
			}
			if(flagUp && flagLeft && !check_start_wall(vert->column+1, vert->line-1)
					&& mapVisited[vert->column+1][vert->line-1] != VISITED){
				inclui_proximo_vertice(vert->column+1, vert->line-1, heuristic(end, {vert->column+1, vert->line-1}), vert, caminhos);
				mapVisited[vert->column+1][vert->line-1] = VISITED;
			}
			if(flagDown && flagRight && !check_start_wall(vert->column-1, vert->line+1)
					&& mapVisited[vert->column-1][vert->line+1] != VISITED){
				inclui_proximo_vertice(vert->column-1, vert->line+1, heuristic(end, {vert->column-1, vert->line+1}), vert, caminhos);
				mapVisited[vert->column-1][vert->line+1] = VISITED;
			}
			if(flagDown && flagLeft && !check_start_wall(vert->column-1, vert->line-1)
					&& mapVisited[vert->column-1][vert->line-1] != VISITED){
				inclui_proximo_vertice(vert->column-1, vert->line-1, heuristic(end, {vert->column-1, vert->line-1}), vert, caminhos);
				mapVisited[vert->column-1][vert->line-1] = VISITED;
			}
			mapVisited[vert->column][vert->line] = VISITED;
		}else if(map[vert->column][vert->line] == END){
			setCaminhoLabirinto(vert);//Coloca em percursoLabirinto o caminho ateh a saida
			return this->percursoLabirinto;
		}
	}
	return this->percursoLabirinto;
}
