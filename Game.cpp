/*
 * Game.cpp
 *
 *  Created on: 29 okt 2015
 *      Author: filfu175
 */

#include "Game.h"
#include <iostream>

Game::Game() {


}

Game::~Game() {

}

int Game::run(int screenWidth, int screenHeight){

	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cerr<<"SDL_Init failed: "<<SDL_GetError()<<std::endl;
		return 1;
	}

	//Create a Window
	_window = SDL_CreateWindow("Guns Blood N' Ammo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	if(_window == NULL){
		std::cerr<<"Failed to create a SDL_Window: "<<SDL_GetError()<<std::endl;
		return 2;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if(_renderer == NULL){
	  std::cerr<<"Failed to create a SDL_Renderer: "<<SDL_GetError()<<std::endl;
	  return 3;
	}

	if(TTF_Init() != 0){
	  std::cerr<<"TTF_Init failed: "<<SDL_GetError()<<std::endl;
	  return 4;
	}

	std::vector<const char*> menuItems, optionItems;
	menuItems.push_back("Guns Blood N' Ammo");
	menuItems.push_back("New Game");
	menuItems.push_back("Help");
	menuItems.push_back("Options");
	menuItems.push_back("Exit");

	optionItems.push_back("Help");
	optionItems.push_back("This is a Top-Down-Shooter");
	optionItems.push_back("game developed for pc using");
	optionItems.push_back("C++ and SDL 2");
	optionItems.push_back("Press Space to return.");

	_cam.x = 0;
	_cam.y = 0;

	_menu = new Menu(menuItems, optionItems, "BloodLust.ttf");
	World* _level1 = new World();
	_levels.push_back(_level1);
	_currentLevel = _levels.at(0);


	SDL_Event input;
	char key;
	
	const static int MENU = 0;
	const static int GAMEPLAY = 1;
	const static int EXIT = 2;

	int gameState = 0;

	while(gameState != EXIT){

	  while(gameState == MENU){
	    if(SDL_PollEvent(&input)){
	      switch(input.type){
	      case SDL_QUIT:
		gameState = EXIT;
		break;
	      case SDL_KEYDOWN:
		key = input.key.keysym.sym;
		if(isalpha(key))
		  key = toupper(input.key.keysym.sym);
		_keys[key] = true;
		break;
	      case SDL_KEYUP:
		key = input.key.keysym.sym;
		if(isalpha(key))
		  key = toupper(input.key.keysym.sym);
		_keys[key] = false;
		break;
	      }
	    }
	    if(gameState != EXIT)
	      gameState = _menu->input(_keys);
	    _menu->draw(*_renderer);
	    SDL_RenderPresent(_renderer);
	  }
	  while(gameState == GAMEPLAY){
	    if(SDL_PollEvent(&input)){
	      switch(input.type){
	      case SDL_QUIT:
		gameState = EXIT;
		break;
	      case SDL_KEYDOWN:
		key = input.key.keysym.sym;
		if(isalpha(key))
		  key = toupper(input.key.keysym.sym);
		_keys[key] = true;
		break;
	      case SDL_KEYUP:
		key = input.key.keysym.sym;
		if(isalpha(key))
		  key = toupper(input.key.keysym.sym);
		_keys[key] = false;
		break;
	      }
	    }
	    if(gameState != EXIT)
	      gameState = _currentLevel->input(_keys);
	    _currentLevel->update();
	    _currentLevel->draw(*_renderer, _cam.x, _cam.y);
	    SDL_RenderPresent(_renderer);
	    
	  }
	}


	//Clean up
	SDL_DestroyWindow(_window);

	SDL_Quit();

	return 0;

}

void Game::draw(){
	
}

void Game::update(){
  
}

