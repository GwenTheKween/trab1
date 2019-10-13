#ifndef _BEST_FIRST_SEARCH_H
#define _BEST_FIRST_SEARCH_H
#include "search.h"
#include "labirinto.h"
#include <queue>
#include <cmath>

typedef struct no no_t;

struct no{
	int line, column;
	int pound;
	no_t* father;
};

struct compare_best_first{
	bool operator()(const no_t* v1, const no_t* v2) const{
		return (v1->pound > v2->pound);
	}
};

class Best_first : public Search{
	labirinto map;
	std::deque<std::pair<int,int>> seqVisitados;
	std::vector<std::pair<int,int>> percursoLabirinto;
private:
	bool check_start_end_wall(int column, int line);
	void setCaminhoLabirinto(no_t* origem);
public:
	Best_first():map(0,0){}
	~Best_first();
	std::vector<std::pair<int,int>> executar();
	
	void setMap(labirinto &map);
    const std::deque<std::pair<int,int>> &getSequenciaDeVisitados() const;
    void reset();
};
#endif
