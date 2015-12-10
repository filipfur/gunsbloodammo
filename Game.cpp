/*
 * Game.cpp
 *
 *  Created on: 29 okt 2015
 *      Author: filfu175
 */

#include "Game.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <algorithm>

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
	menuItems.push_back("Highscore");
	menuItems.push_back("Exit");

	helpItems.push_back("Help");
	helpItems.push_back("WASD to control the player");
	helpItems.push_back("Left mouse button to shoot");
	helpItems.push_back("Kill all enemies to proceed");
	helpItems.push_back("Press Space to return.");

	std::vector<const char*> optionItems = {"Options", "Crosshair Color: ", "Back"};

	std::vector<const char*> highscoreItems = {"Highscore"};
	
	ifstream ifs("highscore.txt");
	
	
	string time;
	int counter = 1;
	while(ifs>>time){
	  char* output0 = new char[100];
	  strcpy(output0, std::to_string(counter++).c_str());
	  strcat(output0, ". ");
	  strcat(output0, time.c_str());
	  strcat(output0, " s - ");
	  string str;
	  getline(ifs, str, '\n');
	  strcat(output0, str.c_str());
	  highscoreItems.push_back(output0);
	}
	ifs.close();
	_menu = new Menu(menuItems, helpItems, optionItems, highscoreItems);

	SDL_Event input;
	char key;
	
	const static int MENU = 0;
	const static int GAMEPLAY = 1;
	const static int EXIT = 2;
	const static int GAMEOVER = 3;
	const static int NEXTLEVEL = 4;
	const static int WINNING = 5;
	
	_mouseL = _mouseR = false;

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
		  vector<pair<int, int>> enemies = { make_pair(840, 200), make_pair(775, 500), make_pair(320, 800) };
		  vector<pair<int, int>> enemies2 = { make_pair(16*64, 5*64), make_pair(30*64, 10*64)};
		  vector<pair<int, int>> enemies3 = {make_pair(16*64, 19*64), make_pair(17*64, 19*64), make_pair(16*64, 20*64), make_pair(17*64, 20*64)};
		  _levels= {new World(256, 256, enemies, "LEVEL1.TXT", "level1.png"),
			    new World(128,128, enemies2, "LEVEL2.TXT", "level2.png"), 
			    new World(480+64,480+64, enemies3, "LEVEL3.TXT", "level3.png")};
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
	      _currtime += 1;
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
	      case SDL_MOUSEBUTTONDOWN:
		if(input.button.button == SDL_BUTTON_LEFT){
		  _mouseL = true;
		}
		if(input.button.button == SDL_BUTTON_RIGHT){
		  _mouseR = true;
		}
		break;
	      case SDL_MOUSEBUTTONUP:
		if(input.button.button == SDL_BUTTON_LEFT){
		  _mouseL = false;
		}
		if(input.button.button == SDL_BUTTON_RIGHT){
		  _mouseR = false;
		}
		break;
	      }
	    }
	    if(gameState != EXIT)
	      gameState = (*_currentLevel)->input(_keys, _mouseX, _mouseY, _mouseR, _mouseL);
	    elapsed = std::chrono::duration_cast<chrono::milliseconds>(std::chrono::high_resolution_clock::now() - refresh_start);
	    if(elapsed.count()*1000 >= GAME_SPEED/10){
	      (*_currentLevel)->update();
	      refresh_start = std::chrono::high_resolution_clock::now();
	    }
	    (*_currentLevel)->draw(*_renderer, _currtime);
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
	    SDL_Color bgColor = {0, 0, 0, 255};
	    TTF_Font* font = TTF_OpenFont("BloodLust.ttf", 72);
	    SDL_Surface* surface = NULL;
	    if(!(surface = TTF_RenderText_Shaded(font, "Victory", color, bgColor))){
	      std::cerr<<TTF_GetError()<<std::endl;
	    }
	    SDL_Texture* texture = NULL;
	    texture = SDL_CreateTextureFromSurface(_renderer, surface);
	    SDL_Rect pos = {640/2 - surface->w/2, 480/4, surface->w, surface->h};
	    SDL_RenderCopy(_renderer, texture, NULL, &pos);
	    SDL_FreeSurface(surface);
	    
	    TTF_CloseFont(font);
	    font = TTF_OpenFont("BloodLust.ttf", 48);

	    char output[100];
	    strcpy(output,"Time: ");
	    strcat(output,std::to_string(_currtime).c_str());
	    strcat(output," seconds.");
	    
	    const char* pointer = output;
	    SDL_Surface* text_surface = NULL;
	    SDL_Texture* text_texture = NULL;

	    if(!(text_surface = TTF_RenderText_Shaded(font, pointer, color, bgColor))){
	      std::cerr<<TTF_GetError()<<std::endl;
	    }

	    if((text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface)) == NULL){
	      std::cerr<<TTF_GetError()<<std::endl;
	    }
	    
	    SDL_Rect pos2 = {640/2 - text_surface->w/2, 480/4*2, text_surface->w, text_surface->h};

	    SDL_RenderCopy(_renderer, text_texture, NULL, &pos2);

	    SDL_FreeSurface(text_surface);

	    vector<pair<int, string>> v;
	    ifstream ifs("highscore.txt");
	    int i;
	    while(ifs>>i){
	      string str;
	      getline(ifs, str, '\n');
	      v.push_back(make_pair(i, str));
	    }
	    
	    if(_currtime <= v.at(v.size()-1).first){
	      SDL_StartTextInput();

	      SDL_Rect pos3 = {0, 0, 256, 32};

	      string text = "";
	      bool done = SDL_FALSE;
	      string tecken;
	      char output2[100];


	      SDL_SetTextInputRect(&pos3);

	      while (!done) {
		SDL_Event textInputEvent;
		if (SDL_PollEvent(&textInputEvent)) {
		  switch (textInputEvent.type) {
		  case SDL_QUIT:
		    /* Quit */
		    done = SDL_TRUE;
		    break;
		  case SDL_TEXTINPUT:
		    /* Add new text onto the end of our text */
		  
		    tecken.assign(textInputEvent.text.text, textInputEvent.text.text+1);
		    text += tecken;
		    std::cout<<text<<std::endl;
		    break;
		  case SDL_KEYDOWN:
		    if(textInputEvent.key.keysym.sym == SDLK_BACKSPACE){
		      text = text.substr(0, text.length() - 1);
		    }
		    if(textInputEvent.key.keysym.sym == SDLK_RETURN){
		      //write to file
		      done = SDL_TRUE;
		    }
		  
		    break;
		  }

		  SDL_RenderClear(_renderer);

		  SDL_RenderCopy(_renderer, texture, NULL, &pos);
		
		  SDL_RenderCopy(_renderer, text_texture, NULL, &pos2);

		
		  strcpy(output2,"Name: ");
		  strcat(output2,text.c_str());
	    
		  const char* pointer2 = output2;
		  SDL_Surface* text_surface2 = NULL;
		  SDL_Texture* text_texture2 = NULL;

		  if(!(text_surface2 = TTF_RenderText_Shaded(font, pointer2, color, bgColor))){
		    std::cerr<<TTF_GetError()<<std::endl;
		  }

		  if((text_texture2 = SDL_CreateTextureFromSurface(_renderer, text_surface2)) == NULL){
		    std::cerr<<TTF_GetError()<<std::endl;
		  }
	    
		  SDL_Rect pos4 = {640/2 - text_surface2->w/2, 480/4*3, text_surface2->w, text_surface2->h};

		  SDL_RenderCopy(_renderer, text_texture2, NULL, &pos4);

		  SDL_RenderPresent(_renderer);

		  SDL_FreeSurface(text_surface2);
		  SDL_DestroyTexture(text_texture2);
		
		}
	      
	      }
	      SDL_StopTextInput();
	    
	      SDL_DestroyTexture(texture);
	      SDL_DestroyTexture(text_texture);

	      v.at(v.size()-1).first = _currtime;
	      v.at(v.size()-1).second = text;

	      sort(v.begin(), v.end());

	      ofstream highscore;
	      highscore.open("highscore.txt");
	      for(auto it = v.cbegin(); it != v.cend(); ++it){
		highscore<<it->first<<' '<<it->second<<"\n";
	      }
	      highscore.close();

	      _menu->updateHighscore();
	    }
	    else{
	      SDL_RenderPresent(_renderer);
	      SDL_Delay(4000);
	    }

	    

	    _levels.clear();
	    
	    SDL_FlushEvents(SDL_QUIT, SDL_LASTEVENT);

	    gameState = MENU;
	    _currtime = 0;

	  }

	}


	//Clean up
	SDL_DestroyWindow(_window);

	SDL_Quit();

	return 0;

}
