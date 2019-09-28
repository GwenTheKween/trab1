#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <stdio.h>
#include <vector>
#include <stdlib.h>

enum MAP_INFO{
	FREE_SPACE,
	WALL,
	BEGIN,
	END,
	ERROR
};

class labirinto{
	int height, width;
	std::vector<std::vector<MAP_INFO> > map;
private:
	void resize(int h,int w);
public:

	labirinto(int h, int w);
	labirinto(char* filename);
	~labirinto(){
		height = 0;
		width = 0;
	}

	std::vector<MAP_INFO>& operator [](int i){
		return map[i];
	}
	void gera_labirinto_manual();
	void gera_labirinto_automatico();
	void print();
};

#endif