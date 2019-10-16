#include "search.h"
#include "labirinto.h"

class A_star:public Search{
private:
	labirinto& map;

	std::vector<std::vector<std::pair<int, int> > > antecedentes;

	std::deque<std::pair<int, int> > fixing_stupid_bad_idea;
public:
	A_star(labirinto& m);
	~A_star(){}

	//Metodos herdados da classe base
	void setMap(labirinto &map){}
	//Nao tenho certeza do que fazer aqui
	const std::deque<std::pair<int, int> > &getSequenciaDeVisitados()const {return fixing_stupid_bad_idea;}
	std::vector<std::pair<int, int> > executar();
	void reset();

	//metodos proprios da classe
	//A distancia euclidiana sera usada como heuristica da busca
	double distance(std::pair<int, int> A, std::pair<int, int> B);
};
