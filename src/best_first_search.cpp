#include "best_first_search.h"

bool Best_first::check_start_end_wall(int column, int line){
	return (map[column][line] == END || map[column][line] == BEGIN || map[column][line] == WALL);
}

void inclui_proximo_vertice(int nextColumn, int nextLine, int pound, no_t* father,
		std::priority_queue<no_t*, std::vector<no_t*>, compare_best_first>& caminhos,
		std::vector<no_t*> enderecosUsados){
	no_t* nextVert = (no_t*)malloc(sizeof(no_t));
	nextVert->column = nextColumn;
	nextVert->line = nextLine;
	nextVert->pound = pound;
	nextVert->father = father;
	caminhos.push(nextVert);
	enderecosUsados.push_back(nextVert);
}

void Best_first::setMap(labirinto &map){
	this->map = map;
}

const std::deque<std::pair<int,int>>& Best_first::getSequenciaDeVisitados(){
	return seqVisitados;
}

void Best_first::reset(){
	map = labirinto(0,0);
	seqVisitados.clear();
}

void Best_first::setCaminhoLabirinto(no_t* origem){
	no_t* atual, *prox;
	atual = NULL;
	prox = origem;
	if(prox != NULL){
		do{
			atual = prox;
			prox = prox->father;
			this->percursoLabirinto.push_back(std::pair<int,int>(atual->column, atual->line));
			free(atual);
		}while(prox != NULL);
	}
}

void libera_Enderecos_Marca_visitados(std::deque<std::pair<int,int>>& seqVisitados, std::vector<no_t*>& enderecosUsados){
	for(int i = 0; i < enderecosUsados.size(); i++){
		seqVisitados.push_back(std::pair<int, int>(enderecosUsados[i]->column, enderecosUsados[i]->line));//Guarda os NO's visitados
		free(enderecosUsados[i]);//libera os enderecos
	}
}


std::vector<std::pair<int,int>> Best_first::executar(){ 
	std::priority_queue<no_t*, std::vector<no_t*>, compare_best_first> caminhos;
	std::vector<no_t*> enderecosUsados;
	labirinto mapVisited = map;

	double time;
	char flagUp, flagDown, flagLeft, flagRight;
	int height = map.getHeight(), width = map.getWidth();
	no_t* vert;

	inclui_proximo_vertice(map.getColumnBegin(), map.getLineBegin(), 0, NULL, caminhos, enderecosUsados);
	while(!caminhos.empty()){
		vert = caminhos.top();
		caminhos.pop();

		if(map[vert->column][vert->line] != END){
			flagUp = (vert->column+1 < height);
			flagDown = (vert->column-1 >= 0);
			flagLeft = (vert->line-1 >= 0);
			flagRight = (vert->line+1 < width);

			//Uso ERROR como posicao visitada
			if(flagUp && !check_start_end_wall(vert->column+1, vert->line) 
					&& mapVisited[vert->column+1][vert->line] != ERROR){
				inclui_proximo_vertice(vert->column+1, vert->line, 1, vert, caminhos, enderecosUsados);

				mapVisited[vert->column+1][vert->line] = ERROR;//Marca posicao como visitado
			}else if(flagDown && !check_start_end_wall(vert->column-1, vert->line) 
					&& mapVisited[vert->column-1][vert->line] != ERROR){
				inclui_proximo_vertice(vert->column-1, vert->line, 1, vert, caminhos, enderecosUsados);
				mapVisited[vert->column-1][vert->line] = ERROR;//Marca posicao como visitado
			}else if(flagRight && !check_start_end_wall(vert->column, vert->line+1)
					&& mapVisited[vert->column][vert->line+1] != ERROR){
				inclui_proximo_vertice(vert->column, vert->line+1, 1, vert, caminhos, enderecosUsados);
				mapVisited[vert->column][vert->line+1] = ERROR;
			}else if(flagLeft && !check_start_end_wall(vert->column, vert->line-1)
					&& mapVisited[vert->column][vert->line-1] != ERROR){
				inclui_proximo_vertice(vert->column, vert->line-1, 1, vert, caminhos, enderecosUsados);
				mapVisited[vert->column][vert->line-1] = ERROR;
			}else if(flagUp && flagRight && !check_start_end_wall(vert->column+1, vert->line+1)
					&& mapVisited[vert->column+1][vert->line+1] != ERROR){
				inclui_proximo_vertice(vert->column+1, vert->line+1, sqrt(2), vert, caminhos, enderecosUsados);
				mapVisited[vert->column+1][vert->line+1] = ERROR;
			}else if(flagUp && flagLeft && !check_start_end_wall(vert->column+1, vert->line-1)
					&& mapVisited[vert->column+1][vert->line-1] != ERROR){
				inclui_proximo_vertice(vert->column+1, vert->line-1, sqrt(2), vert, caminhos, enderecosUsados);
				mapVisited[vert->column+1][vert->line-1] = ERROR;
			}else if(flagDown && flagRight && !check_start_end_wall(vert->column-1, vert->line+1)
					&& mapVisited[vert->column-1][vert->line+1] != ERROR){
				inclui_proximo_vertice(vert->column-1, vert->line+1, sqrt(2), vert, caminhos, enderecosUsados);
				mapVisited[vert->column-1][vert->line+1] = ERROR;
			}else if(flagDown && flagLeft && !check_start_end_wall(vert->column-1, vert->line-1)
					&& mapVisited[vert->column-1][vert->line-1] != ERROR){
				inclui_proximo_vertice(vert->column-1, vert->line-1, sqrt(2), vert, caminhos, enderecosUsados);
				mapVisited[vert->column-1][vert->line-1] = ERROR;
			}
		}else if(map[vert->column][vert->line] == END){
			setCaminhoLabirinto(vert);//Coloca em percursoLabirinto o caminho ateh a saida
			libera_Enderecos_Marca_visitados(seqVisitados, enderecosUsados);
			return this->percursoLabirinto;
		}
	}
	libera_Enderecos_Marca_visitados(seqVisitados, enderecosUsados);
}