/*
 * Game.h
 *
 *  Created on: 29 okt 2015
 *      Author: filfu175
 */

#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <SDL_ttf.h>
#include "Menu.h"
#include <vector>
#include "World.h"
#include <map>

struct Camera{
	double x;
	double y;
};

class Game {
public:
	Game();
	virtual ~Game();
	int run(int, int);
private:
	void draw();
	void update();
	Camera _cam;
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	Menu* _menu;
	std::vector<World*> _levels;
	World* _currentLevel;
	std::map<char, bool> _keys;
	
};

#endif
//-static-libstdc++ -lSDL2_image -lSDL2_mixer -lSDL2_ttf `sdl2-config --cflags` `sdl2-config --libs` -Isrc -Isrc/layers -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL2main -lSDL2
