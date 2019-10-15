#ifndef __BFS__H__
#define __BFS__H__ value

#include "search.h"
#include "labirinto.h"

#include <queue>
#include <functional>

class bfsSearch : public Search{
    labirinto *map;
    std::deque<std::pair< int , int > > visitados;


    public:

        bfsSearch();
        ~bfsSearch();

        void setMap(labirinto &map);

        const std::deque<std::pair<int,int> > &getSequenciaDeVisitados() const;

        std::vector<std::pair<int,int> > executar();

        void reset();
};


#endif /* ifndef __BFS__H__ */
