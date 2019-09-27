#include "labirinto.h"

int main(int argc, char **argv){
	if(argc < 2){
		printf("uso: %s <arquivo>",argv[0]);
	}
	labirinto l(argv[1]);
	l.print();
	return 0;
}
