#ifndef _BEST_FIRST_SEARCH_H
#define _BEST_FIRST_SEARCH_H
#include "search.h"
#include "labirinto.h"
#include <queue>
#include <cmath>
#include <vector>

typedef struct no no_t;

struct no{
	double weight;
	std::pair<int,int> father;
	std::pair<int,int> current;
};

struct compare_best_first{
	bool operator()(const no_t& v1, const no_t& v2) const{
		return (v1.weight > v2.weight);
	}
};

class Best_first : public Search{
	labirinto map;
	std::deque<std::pair<int,int>> seqVisitados;
	std::vector<std::pair<int,int>> percursoLabirinto;
private:
	void inclui_proximo_vertice( no_t& children, double weight, std::pair<int,int>& father,
                std::priority_queue<no_t, std::vector<no_t>, compare_best_first>& caminhos);


	//void inclui_proximo_vertice(int nextColumn, int nextLine, double weight, no_t* father,
	//	std::priority_queue<no_t*, std::vector<no_t*>, compare_best_first>& caminhos);
	bool check_start_wall(int column, int line);
	void setCaminhoLabirinto(std::vector< std::vector<no_t> > way, no_t fim);
public:
	Best_first():map(0,0){}
	~Best_first();
	std::vector<std::pair<int,int>> executar();
	
	void setMap(labirinto &map);
    const std::deque<std::pair<int,int>> &getSequenciaDeVisitados() const;
    void reset();
};
#endif
