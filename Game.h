#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <SDL_ttf.h>
#include "Menu.h"
#include <vector>
#include "World.h"
#include <map>
#include <string>



class Game {
public:
	Game();
	virtual ~Game();
	int run(int, int, int, bool intro = false);
private:
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	Menu* _menu;
	std::vector<World*> _levels;
	std::vector<World*>::iterator _currentLevel;
	std::map<char, bool> _keys;
	int _mouseX, _mouseY;
	bool _mouseR, _mouseL;
	int _currtime = 0;
	
};

#endif
