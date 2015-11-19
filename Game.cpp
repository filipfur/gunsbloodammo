/*
 * Game.cpp
 *
 *  Created on: 29 okt 2015
 *      Author: filfu175
 */

#include "Game.h"
#include <iostream>
#include <chrono>

Game::Game() {


}

Game::~Game() {

}

int Game::run(int screenWidth, int screenHeight, int GAME_SPEED, bool intro){

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
	
	SDL_ShowCursor(SDL_DISABLE);

	std::vector<const char*> menuItems, helpItems;
	menuItems.push_back("Guns Blood N' Ammo");
	menuItems.push_back("New Game");
	menuItems.push_back("Help");
	menuItems.push_back("Options");
	menuItems.push_back("Exit");

	helpItems.push_back("Help");
	helpItems.push_back("This is a Top-Down-Shooter");
	helpItems.push_back("game developed for pc using");
	helpItems.push_back("C++ and SDL 2");
	helpItems.push_back("Press Space to return.");

	std::vector<const char*> optionItems = {"Options", "Crosshair Color: ", "Back"};

	_menu = new Menu(menuItems, helpItems, optionItems);

	SDL_Event input;
	char key;
	
	const static int MENU = 0;
	const static int GAMEPLAY = 1;
	const static int EXIT = 2;
	const static int GAMEOVER = 3;
	const static int NEXTLEVEL = 4;
	const static int WINNING = 5;

	if(intro){
	  SDL_Surface* image = IMG_Load("GBA.png");
	
	  SDL_Texture* image_ = SDL_CreateTextureFromSurface(_renderer, image);

	  SDL_RenderCopy(_renderer, image_, NULL, NULL);
	
	  SDL_RenderPresent(_renderer);

	  SDL_Delay(2000);

	  SDL_FreeSurface(image);
	  SDL_DestroyTexture(image_);
	}

	int gameState = 0;
	while(gameState != EXIT){
	  auto fps_start = std::chrono::high_resolution_clock::now();
	  auto refresh_start = std::chrono::high_resolution_clock::now();
	  int frames = 0;

	  if(_levels.empty()){
	    _levels= {new World(64, 64, "LEVEL1.TXT", "level1.png"), new World(128,128, "LEVEL1.TXT", "level2.png")};
	    _currentLevel = _levels.begin();
	  }
	  if(gameState == NEXTLEVEL){
	    ++_currentLevel;
	    if(_currentLevel == _levels.end()){
	      gameState = WINNING;
	    }
	    else
	      gameState = GAMEPLAY;
	  }

	  while(gameState == MENU){
	    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - fps_start;
	    if(elapsed.count() >= 1){
	      std::cout<<"FPS: "<<frames<<std::endl;
	      frames = 0;
	      fps_start = std::chrono::high_resolution_clock::now();
	    }
	    else{
	      frames++;
	    }
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
	    elapsed = std::chrono::duration_cast<chrono::milliseconds>(std::chrono::high_resolution_clock::now() - refresh_start);
	    if(elapsed.count()*1000 >= GAME_SPEED/10){
	      _menu->update();
	      refresh_start = std::chrono::high_resolution_clock::now();
	    }
	    _menu->draw(*_renderer);
	    SDL_RenderPresent(_renderer);
	  }
	  
	  while(gameState == GAMEPLAY){
	    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - fps_start;
	    if(elapsed.count() >= 1){
	      std::cout<<"FPS: "<<frames<<std::endl;
	      frames = 0;
	      fps_start = std::chrono::high_resolution_clock::now();
	    }
	    else{
	      frames++;
	    }
	    while(SDL_PollEvent(&input)){
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
	      case SDL_MOUSEMOTION:
		_mouseX = input.motion.x;
		_mouseY = input.motion.y;
		break;
	      }
	    }
	    if(gameState != EXIT)
	      gameState = (*_currentLevel)->input(_keys, _mouseX, _mouseY);
	    elapsed = std::chrono::duration_cast<chrono::milliseconds>(std::chrono::high_resolution_clock::now() - refresh_start);
	    if(elapsed.count()*1000 >= GAME_SPEED/10){
	      (*_currentLevel)->update();
	      refresh_start = std::chrono::high_resolution_clock::now();
	    }
	    (*_currentLevel)->draw(*_renderer);
	    SDL_RenderPresent(_renderer);
	  }
	  if(gameState == GAMEOVER){
	    SDL_Surface* image = IMG_Load("gameover.png");
	
	    SDL_Texture* image_ = SDL_CreateTextureFromSurface(_renderer, image);

	    SDL_RenderCopy(_renderer, image_, NULL, NULL);
	
	    SDL_RenderPresent(_renderer);

	    SDL_Delay(2000);

	    SDL_FreeSurface(image);
	    SDL_DestroyTexture(image_);

	    _levels.clear();
	    

	    gameState = 0;
	  }

	  if(gameState == WINNING){

	    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	    SDL_RenderClear(_renderer);
	    
	    
	    SDL_Color color = {255, 255, 255, 255};
	    TTF_Font* font = TTF_OpenFont("BloodLust.ttf", 72);
	    SDL_Surface* surface = NULL;
	    if(!(surface = TTF_RenderText_Solid(font, "Victory", color))){
	      std::cerr<<TTF_GetError()<<std::endl;
	    }
	    SDL_Texture* texture = NULL;
	    texture = SDL_CreateTextureFromSurface(_renderer, surface);
	    SDL_Rect pos = {640/2 - surface->w, 480/4, surface->w, surface->h};
	    SDL_RenderCopy(_renderer, texture, NULL, &pos);
	    SDL_DestroyTexture(texture);
	    
	    TTF_CloseFont(font);
	    font = TTF_OpenFont("BloodLust.ttf", 48);

	    double time = 114.1123;

	    char output[100];
	    strcpy(output,"Time: ");
	    strcat(output,std::to_string(time).c_str());
	    strcat(output," seconds.");
	    
	    const char* pointer = output;

	    if(!(surface = TTF_RenderText_Solid(font, pointer, color))){
	      std::cerr<<TTF_GetError()<<std::endl;
	    }

	    SDL_RenderPresent(_renderer);
	    
	    SDL_Delay(2000);

	  }

	}


	//Clean up
	SDL_DestroyWindow(_window);

	SDL_Quit();

	return 0;

}
