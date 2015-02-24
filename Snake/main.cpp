#include <iostream>
#include <time.h>

#include "SnakeGame.h"

int main(int argc,char** argv){
	srand((unsigned)time(NULL));
	SnakeGame myGame(30,20,640,480,5,2,1);
	myGame.start_game(argc, argv);

	return 0;
}