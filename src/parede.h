#include <stdio.h>
#include <tuple>

#define VERTICAL 1
#define HORIZONTAL 2

class parede{
private:
	std::pair<int, int> start, end;
	int direction;
public:
	parede(std::pair<int,int> s, std::pair<int,int>e) : start(s), end(e){
		if(end < start){
			std::pair<int, int> tmp(end);
			end = start;
			start = tmp;
		}
		if(start.first== end.first){
			direction = VERTICAL;
		}else{
			direction = HORIZONTAL;
		}
	}
	parede(int xs, int ys, int xe, int ye): start(xs,ys), end(xe,ye){
		if(end < start){
			std::pair<int, int> tmp(end);
			end = start;
			start = tmp;
		}
		if(start.first== end.first){
			direction = VERTICAL;
		}else{
			direction = HORIZONTAL;
		}
	}

	std::pair<int, int> getStart(){return start;}
	std::pair<int, int> getEnd(){return end;}
	int getDirection() {return direction;}

	int getLength(){
		if(direction == HORIZONTAL){
			return end.first- start.first;
		}else{
			return end.second- start.second;
		}
	}

	void print(){
	}
};
