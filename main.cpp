
#include "Game.h"

int main(int argc, char* argv[]){

	Game game;
	//run(screenWidth, screenHeight, GAME_SPEED_HZ, intro)
	int error = game.run(640, 480, 100, true);

	return error;
}




