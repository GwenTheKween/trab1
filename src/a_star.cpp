#include "a_star.h"
#include "math.h"
#include <queue>

//acho que terminei o maldito arquivo

//define esta aqui para acelerar a escrita do programa, e possivelmente melhorar a legibilidade
#define pii std::pair<int, int>

//classe usada para fazer a comparacao na lista de prioridades
class comparator{
private:
	static pii goal;
public:
	//construtor da classe, recebe o fim do mapa para comparar distacia ate ele
	comparator(pii end){goal = end;}

	//quando for chamado, compara se a distancia do primeiro elemento eh menor que a distancia do segundo
	bool operator() (const std::pair<pii,double> lhs, const std::pair<pii, double> rhs){
		double d1 = distance(lhs), d2 = distance(rhs);
		return d1 > d2;
	}

	//metodo para calcular distancia entre o ponto passado e o fim
	double distance(std::pair<pii,double> val){
		pii A = val.first;
		double dist = (A.first - goal.first) * (A.first - goal.first) + (A.second - goal.second) * (A.second - goal.second);
		return sqrt(dist);
	}
};

//O membro estatico da classe deve ser explicitamente declarado em algum lugar, e a classe so armazena a referencia a variavel global
pii comparator::goal = std::make_pair(-1,-1);


A_star::A_star(labirinto &m):
	Search(),
	map(m){
	reset();
}

void A_star::reset(){
	std::vector<pii > temp;
	pii unvisited(-1,-1);
	temp.resize(map.getWidth(), unvisited);
	antecedentes.resize(map.getHeight(), temp);
}

//metodo que executa a busca pelo melhor caminho
//E retorna o caminho inverso
std::vector<pii > A_star::executar(){
	//retorno da funcao, melhor caminho encontrado pela busca
	std::vector<pii > path;
	//coordenadas a serem trabalhadas
	pii currCoord, goal = map.getEnd(), unvisited(-1,-1), temp;
	//esse pair, usado na fila de prioridades, armazena a coordenada e quanto andou-se ate esse valor
	std::pair<pii, double> pqItem(map.getStart(), 0);
	//fila de prioridades que eh a base do algoritmo
	std::priority_queue<std::pair<pii,double>, std::vector<std::pair<pii,double> >, comparator> toVisit(comparator(map.getEnd())); 
	//custo da movimentação ate o momento, e valor da raiz quadrada de 2, para evitar recalcular com frequencia
	double currCost, sq2 = sqrt(2);

	//Cuidando para que nao ocorra um loop infinito no final do algoritmo
	antecedentes[map.getStart().first][map.getStart().second] = map.getStart();



	//inicia o algoritmo colocando o inicio do mapa como proxima coordenada a visitar
	toVisit.push(pqItem);
	//enquanto a proxima coordenada nao for o final, precisamos continuar buscando
	while(toVisit.top().first != goal){
		currCoord = toVisit.top().first;
		currCost = toVisit.top().second;
		toVisit.pop();
		//se o vizinho ainda nao foi visitado, marca-lo como visitado setando seu antecedente, e adiciona-lo a fila
		//Primeiro tentamos reduzir X e adicionar os pontos
		if(currCoord.first > 0){ //se eh possivel reduzir o valor de X
			if(currCoord.second > 0){ //se eh possivel reduzir o valor de Y
				if(antecedentes[currCoord.first - 1][currCoord.second - 1] == unvisited && map[currCoord.first - 1][currCoord.second - 1] != WALL){
					antecedentes[currCoord.first - 1][currCoord.second - 1] = currCoord;
					temp = std::make_pair(currCoord.first - 1, currCoord.second - 1);
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(temp, currCost + sq2);
					toVisit.push(pqItem);
				}
			}

			if(currCoord.second < map.getWidth() - 1){ // se eh possivel aumentar o valor de Y
				if(antecedentes[currCoord.first - 1][currCoord.second + 1] == unvisited && map[currCoord.first - 1][currCoord.second + 1] != WALL){
					antecedentes[currCoord.first - 1][currCoord.second + 1] = currCoord;
					temp = std::make_pair(currCoord.first - 1, currCoord.second + 1);
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(temp, currCost + sq2);
					toVisit.push(pqItem);
				}
			}

			if(antecedentes[currCoord.first - 1][currCoord.second] == unvisited && map[currCoord.first - 1][currCoord.second] != WALL){
				antecedentes[currCoord.first - 1][currCoord.second] = currCoord;
				temp = std::make_pair(currCoord.first - 1, currCoord.second);
				pqItem = std::make_pair(temp, currCost + 1);
				toVisit.push(pqItem);
			}
		}

		//Depois tentamos aumentar o X e adicionar os pontos
		if(currCoord.first < map.getHeight() - 1){
			if(currCoord.second > 0){ //se eh possivel reduzir o valor de Y
				if(antecedentes[currCoord.first + 1][currCoord.second - 1] == unvisited && map[currCoord.first + 1][currCoord.second - 1] != WALL){
					antecedentes[currCoord.first + 1][currCoord.second - 1] = currCoord;
					temp = std::make_pair(currCoord.first + 1, currCoord.second - 1);
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(temp, currCost + sq2);
					toVisit.push(pqItem);
				}
			}

			if(currCoord.second < map.getWidth() - 1){ // se eh possivel aumentar o valor de Y
				if(antecedentes[currCoord.first + 1][currCoord.second + 1] == unvisited && map[currCoord.first + 1][currCoord.second + 1] != WALL){
					antecedentes[currCoord.first + 1][currCoord.second + 1] = currCoord;
					temp = std::make_pair(currCoord.first + 1, currCoord.second + 1);
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(temp, currCost + sq2);
					toVisit.push(pqItem);
				}
			}

			if(antecedentes[currCoord.first + 1][currCoord.second] == unvisited && map[currCoord.first + 1][currCoord.second] != WALL){
				antecedentes[currCoord.first + 1][currCoord.second] = currCoord;
				temp = std::make_pair(currCoord.first + 1, currCoord.second);
				pqItem = std::make_pair(temp, currCost + 1);
				toVisit.push(pqItem);
			}

			//por fim, tentamos sem mover no eixo X
			if(currCoord.second > 0){
				if(antecedentes[currCoord.first][currCoord.second - 1] == unvisited && map[currCoord.first][currCoord.second - 1] != WALL){
					antecedentes[currCoord.first][currCoord.second - 1] = currCoord;
					temp = std::make_pair(currCoord.first, currCoord.second - 1);
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(temp, currCost + 1);
					toVisit.push(pqItem);
				}
			}

			if(currCoord.second < map.getWidth()-1){
				if(antecedentes[currCoord.first][currCoord.second + 1] == unvisited && map[currCoord.first][currCoord.second + 1] != WALL){
					antecedentes[currCoord.first][currCoord.second + 1] = currCoord;
					temp = std::make_pair(currCoord.first, currCoord.second + 1);
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(temp, currCost + 1);
					toVisit.push(pqItem);
				}
			}
		}
	}

	//Agora, o final foi encontrado, basta adicionar as coordenadas e inverter o vetor
	path.push_back(goal);
	//chegamos no começo quando a coordenada atual for seu proprio antecedente
	while(currCoord != antecedentes[currCoord.first][currCoord.second]){
		path.push_back(currCoord);
		currCoord = antecedentes[currCoord.first][currCoord.second];
	}
	//adicionando o primeiro passo
	path.push_back(currCoord);
	return path;
}

