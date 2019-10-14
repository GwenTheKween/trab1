#include "search.h"
#include "labirinto.h"

class A_star:public Search{
private:
	labirinto& map;
public:
	A_star();
	~A_star();

	//Metodos herdados da classe base
	void setMap(labirinto &map);
	const std::deque<std::pair<int, int> > &getSequenciaDeVisitados();
	std::vector<std::pair<int, int> > executar();
	void reset();

	//metodos proprios da classe
	//A distancia euclidiana sera usada como heuristica da busca
	double distance(std::pair<int, int> A, std::pair<int, int> B);
};
