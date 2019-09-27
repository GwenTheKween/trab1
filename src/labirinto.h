#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <stdio.h>
#include <vector>

enum{
	FREE_SPACE,
	WALL,
	BEGIN,
	END
};

class labirinto{
	int height, width;
	std::vector<std::vector<int> > map;
public:

	labirinto(int w, int h);
	~labirinto(){
		height = 0;
		width = 0;
	}

	std::vector<int>& operator [](int i){
		return map[i];
	}
};

#endif
