#include "a_star.h"
#include "math.h"

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


//==========================================================================================================================
//Funcao auxiliar para inserir um elemento na lista

//Funcao para calcular a distancia euclidiana entre os pontos A e B
double distancia(pii A, pii B){
	double dist = (A.first - B.first) * (A.first - B.first);
	dist += (A.second - B.second) * (A.second - B.second);
	return sqrt(dist);
}

/*
 * A funcao insert tenta inserir elem em lst, inserindo em ordem crescente do primeiro elemento (valor da heuristica)
 * Se o valor for corretamente inserido na lista (a coordenada nao existia, ou estava com uma heuristica maior), retorna true
 * Se o valor nao pode ser inserido (ja tinha a coordenada com uma heuristica menor), retorna false
*/
bool insert(std::list<std::pair<double, pii > >& lst, std::pair<double, pii >& elem, pii goal){
	auto iter = lst.begin(), whereToInsert = lst.end(); //iterador para a lista, e onde inserir o novo elemento, se for necessario
	bool ins = true; //se vai ou nao ser inserido
	double heuristica = elem.first + distancia(elem.second, goal); //armazena a heuristica, para acelerar a busca
	//se for encontrado um elemento com a mesma coordenada com um valor menor, cancela a insercao do valor
	for(;iter != lst.end() && (iter->first + distancia(iter->second, goal)) < heuristica; iter++){
		if(iter->second == elem.second){
			ins = false;
			break;
		}
	}
	if(ins == false) return false; //se nao deve ser inserido, termina a funcao e sai
	//se deve ser inserido, iter determina a posicao a ser inserido
	if(iter == lst.end()){
		//Se iter eh o final do vetor, o valor da heuristica do elemento a ser inserido eh o maior presente, inserimos no final da lista
		lst.push_back(elem);
	}else{
		//Iter nao era o final do vetor, eh o primeiro valor com heuristica maior que elem.
		//elem deve ser inserido antes de iter e depois temos que procurar se a coordenada existe na lista
		lst.insert(iter, elem);
		for(;iter != lst.end(); iter++){
			if(iter -> second == elem.second){
				//se o elemento existia, removemos da lista e saimos do loop
				lst.erase(iter);
				break;
			}
		}
	}
	//independentemente de termos removido o valor ou nao, retornamos true
	return true;
}

//==========================================================================================================================


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
	std::pair<double, pii > pqItem(0, map.getStart());
	//fila de prioridades que eh a base do algoritmo
	std::list<std::pair<double, pii > > toVisit; 
	//Mapa de coordenadas que ja foram visitadas 
	std::set<pii > finished;
	//custo da movimentação ate o momento, e valor da raiz quadrada de 2, para evitar recalcular com frequencia
	double currCost, sq2 = sqrt(2);

	//Cuidando para que nao ocorra um loop infinito no final do algoritmo
	antecedentes[map.getStart().first][map.getStart().second] = map.getStart();



	//inicia o algoritmo colocando o inicio do mapa como proxima coordenada a visitar
	toVisit.push_front(pqItem);
	//enquanto a proxima coordenada nao for o final, precisamos continuar buscando
	while(!toVisit.empty() && toVisit.front().second != goal){
		currCost = toVisit.front().first;
		currCoord = toVisit.front().second;
        //isso é para poder ver por onde o algoritmo está andando
        this->fixing_stupid_bad_idea.push_back(currCoord);
		toVisit.pop_front();
		finished.insert(currCoord); //impede que coordenadas ja terminadas sejam exploradas de novo
		//se o vizinho ainda nao foi visitado, marca-lo como visitado setando seu antecedente, e adiciona-lo a fila
		//Primeiro tentamos reduzir X e adicionar os pontos
		if(currCoord.first > 0){ //se eh possivel reduzir o valor de X
			if(currCoord.second > 0){ //se eh possivel reduzir o valor de Y
				temp = std::make_pair(currCoord.first - 1, currCoord.second - 1);
				if(!finished.count(temp) && map[currCoord.first - 1][currCoord.second - 1] != WALL){//se podemos mover para essa coordenada e ela nao foi terminada ainda
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(currCost + sq2, temp);
					if(insert(toVisit, pqItem, goal)){ //se conseguimos inserir na lista, mudamos o antecedente da coordenada
						antecedentes[currCoord.first - 1][currCoord.second - 1] = currCoord;
					}
				}
			}

			if(currCoord.second < map.getWidth() - 1){ // se eh possivel aumentar o valor de Y
				temp = std::make_pair(currCoord.first - 1, currCoord.second + 1);
				if(!finished.count(temp) && map[currCoord.first - 1][currCoord.second + 1] != WALL){
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(currCost + sq2, temp);
					if(insert(toVisit, pqItem, goal)){ //se conseguimos inserir na lista, mudamos o antecedente da coordenada
						antecedentes[currCoord.first - 1][currCoord.second + 1] = currCoord;
					}
				}
			}

			temp = std::make_pair(currCoord.first - 1, currCoord.second);
			if(!finished.count(temp) &&map[currCoord.first - 1][currCoord.second] != WALL){//tentamos andar sem mudar o Y
				//como o movimento nao eh diagonal, o custo do movimento eh 1
				pqItem = std::make_pair(currCost + 1, temp);
				if(insert(toVisit, pqItem, goal)){
					antecedentes[currCoord.first - 1][currCoord.second] = currCoord;
				}
			}
		}

		//Depois tentamos aumentar o X e adicionar os pontos
		if(currCoord.first < map.getHeight() - 1){
			if(currCoord.second > 0){ //se eh possivel reduzir o valor de Y
				temp = std::make_pair(currCoord.first + 1, currCoord.second - 1);
				if(!finished.count(temp) &&map[currCoord.first + 1][currCoord.second - 1] != WALL){
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(currCost + sq2, temp);
					if(insert(toVisit, pqItem, goal)){
						antecedentes[currCoord.first + 1][currCoord.second - 1] = currCoord;
					}
				}
			}

			if(currCoord.second < map.getWidth() - 1){ // se eh possivel aumentar o valor de Y
				temp = std::make_pair(currCoord.first + 1, currCoord.second + 1);
				if(!finished.count(temp) &&map[currCoord.first + 1][currCoord.second + 1] != WALL){
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(currCost + sq2, temp);
					if(insert(toVisit, pqItem, goal)){
						antecedentes[currCoord.first + 1][currCoord.second + 1] = currCoord;
					}
				}
			}

			temp = std::make_pair(currCoord.first + 1, currCoord.second);
			if(!finished.count(temp) &&map[currCoord.first + 1][currCoord.second] != WALL){
				pqItem = std::make_pair(currCost + 1, temp);
				if(insert(toVisit, pqItem, goal)){
					antecedentes[currCoord.first + 1][currCoord.second] = currCoord;
				}
			}

			//por fim, tentamos sem mover no eixo X
			if(currCoord.second > 0){
				temp = std::make_pair(currCoord.first, currCoord.second - 1);
				if(!finished.count(temp) &&map[currCoord.first][currCoord.second - 1] != WALL){
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(currCost + 1, temp);
					if(insert(toVisit, pqItem, goal)){
						antecedentes[currCoord.first][currCoord.second - 1] = currCoord;
					}
				}
			}

			if(currCoord.second < map.getWidth()-1){
				temp = std::make_pair(currCoord.first, currCoord.second + 1);
				if(!finished.count(temp) &&map[currCoord.first][currCoord.second + 1] != WALL){
					//cria o novo item a ser inserido na lista; como o movimento eh diagonal, o custo eh sq2
					pqItem = std::make_pair(currCost + 1, temp);
					if(insert(toVisit, pqItem, goal)){
						antecedentes[currCoord.first][currCoord.second + 1] = currCoord;
					}
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

