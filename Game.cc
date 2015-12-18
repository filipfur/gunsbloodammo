#include "Game.h"

Game::Game() {}
Game::~Game() {}

int Game::run(int screenWidth, int screenHeight, int GAME_SPEED, bool intro){
  
  if(init_sdlstuff(screenWidth, screenHeight) != 0)
  {
    //cerr messages is made inside init_sdlstuff if something goes wrong
    return 1;
  }

  init_menu();
  _game_speed = GAME_SPEED;
  _mouseL = _mouseR = false;
  
  //Program starts here
  
  if(intro){
    run_intro();
  }
  
  //main loop that keeps running until the game should end.
  //gameState = Menu in first iteration (initialized in Game.h)
  while(gameState != EXIT){
    fps_start = std::chrono::high_resolution_clock::now();
    refresh_start = std::chrono::high_resolution_clock::now();

    if(_levels.empty()){
      init_levels();
    }
    if(gameState == NEXTLEVEL){
      ++_currentLevel;
      if(_currentLevel == _levels.end()){
	gameState = WINNING;
      }
      else
      {
	Player currentplayer = (*(_currentLevel - 1))->getPlayer();
	(*_currentLevel)->setPlayer(currentplayer);
	gameState = GAMEPLAY;
      }
    }
    while(gameState == MENU){
      run_menu();
      _game_speed = GAME_SPEED - _menu->get_difficulty();
    }

    while(gameState == GAMEPLAY){
      run_gameplay();
    }
    if(gameState == GAMEOVER){
      run_gameover();
      gameState = MENU;
    }
    if(gameState == WINNING){
      run_winning();
      gameState = MENU;
    }
  }
  
  //Clean up
  SDL_DestroyWindow(_window);
  
  SDL_Quit();
  
  return 0;
  
}

void Game::set_highscoreItems(std::vector<const char*> & highscoreItems){
  ifstream ifs("highscore.txt");
  
  string time;
  int place_no = 1;
  while(ifs>>time){
    char* output0 = new char[100];
    strcpy(output0, std::to_string(place_no++).c_str());
    strcat(output0, ". ");
    strcat(output0, time.c_str());
    strcat(output0, " s - ");
    string str;
    getline(ifs, str, '\n');
    strcat(output0, str.c_str());
    highscoreItems.push_back(output0);
  }
  ifs.close();
}

void Game::run_intro(){
  SDL_Surface* image = IMG_Load("GBA.png");
  
  SDL_Texture* image_ = SDL_CreateTextureFromSurface(_renderer, image);
  
  SDL_RenderCopy(_renderer, image_, NULL, NULL);
  
  SDL_RenderPresent(_renderer);
  
  SDL_Delay(2000);
  
  SDL_FreeSurface(image);
  SDL_DestroyTexture(image_);
}

void Game::init_levels(){
  vector<pair<int, int>> enemies = { make_pair(840, 200),
				     make_pair(775, 500),
				     make_pair(320, 800) };
  vector<pair<int, int>> enemies2 = { make_pair(16*64, 5*64),
				      make_pair(30*64, 10*64)};
  vector<pair<int, int>> enemies3 = {make_pair(16*64, 19*64),
				     make_pair(17*64, 19*64),
				     make_pair(16*64, 20*64),
				     make_pair(17*64, 20*64)};
  _levels= {new World(256, 256, enemies, "LEVEL1.TXT", "level1.png"),
	    new World(128,128, enemies2, "LEVEL2.TXT", "level2.png"), 
	    new World(480+64,480+64, enemies3, "LEVEL3.TXT",
		      "level3.png")};
  _currentLevel = _levels.begin();
}

void Game::run_gameplay(){
  
  std::chrono::duration<double> elapsed =
    std::chrono::high_resolution_clock::now() - fps_start;
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
    gameState = (*_currentLevel)->input(_keys, _mouseX,
					_mouseY, _mouseR, _mouseL);
  elapsed = std::chrono::duration_cast<chrono::milliseconds>(
    std::chrono::high_resolution_clock::now() - refresh_start);
  if(elapsed.count()*1000 >= _game_speed){
    (*_currentLevel)->update();
    refresh_start = std::chrono::high_resolution_clock::now();
  }
  (*_currentLevel)->draw(*_renderer, _currtime);
  SDL_RenderPresent(_renderer);
}

void Game::run_gameover(){

  SDL_Surface* image = IMG_Load("gameover.png");
  
  SDL_Texture* image_ = SDL_CreateTextureFromSurface(_renderer, image);
  
  SDL_RenderCopy(_renderer, image_, NULL, NULL);
  
  SDL_RenderPresent(_renderer);
  
  SDL_Delay(2000);
  
  SDL_FreeSurface(image);
  SDL_DestroyTexture(image_);
  
  _levels.clear();
  _currtime = 0;
  
}

void Game:: run_menu(){
  
  std::chrono::duration<double> elapsed =
    std::chrono::high_resolution_clock::now() - fps_start;
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
    
    if(gameState != EXIT)
      gameState = _menu->input(_keys);
      elapsed = std::chrono::duration_cast<chrono::milliseconds>(
	std::chrono::high_resolution_clock::now() - refresh_start);
      if(elapsed.count()*1000 >= _game_speed/10){
	_menu->update();
	refresh_start = std::chrono::high_resolution_clock::now();
      }
      _menu->draw(*_renderer);
      SDL_RenderPresent(_renderer);
  }
  
  
}


void Game:: run_winning(){
  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderClear(_renderer);
  
  
  SDL_Color color = {255, 255, 255, 255};
  SDL_Color bgColor = {0, 0, 0, 255};
  TTF_Font* font = TTF_OpenFont("BloodLust.ttf", 72);
  SDL_Surface* surface = NULL;
  if(!(surface = TTF_RenderText_Shaded(font, "Victory",
				       color, bgColor))){
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
  
  if(!(text_surface = TTF_RenderText_Shaded(font, pointer,
					    color, bgColor))){
    std::cerr<<TTF_GetError()<<std::endl;
  }
  
  if((text_texture = SDL_CreateTextureFromSurface(
	_renderer, text_surface)) == NULL){
    std::cerr<<TTF_GetError()<<std::endl;
  }
  
  SDL_Rect pos2 = {640/2 - text_surface->w/2, 480/4*2,
		   text_surface->w, text_surface->h};
  
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
	  
	  tecken.assign(textInputEvent.text.text,
			textInputEvent.text.text+1);
	  text += tecken;
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
	
	if(!(text_surface2 = TTF_RenderText_Shaded(
	       font, pointer2, color, bgColor))){
	  std::cerr<<TTF_GetError()<<std::endl;
	}
	
	if((text_texture2 = SDL_CreateTextureFromSurface(
	      _renderer, text_surface2)) == NULL){
	  std::cerr<<TTF_GetError()<<std::endl;
	}
	
	SDL_Rect pos4 = {640/2 - text_surface2->w/2, 480/4*3,
			 text_surface2->w, text_surface2->h};
	
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
  
  _currtime = 0;
}

void Game::init_menu(){
  std::vector<const char*> menuItems{"Guns blood N' Ammo",
      "New Game", "Help", "Options", "Highscore", "Exit"};
  
  std::vector<const char*> helpItems{"Help",
      "WASD to control the player", "Left mouse button to shoot",
      "Kill all enemies to proceed", "Press space to return."};
  
  std::vector<const char*> optionItems = {"Options",
					  "Crosshair Color: ",
					  "Difficulty", "Back"};
  
  std::vector<const char*> highscoreItems = {"Highscore"};
  
  
  set_highscoreItems(highscoreItems); //reads from highscore.txt and
  //sets highscoreItems

  _menu = new Menu(menuItems, helpItems, optionItems, highscoreItems);
}

int Game:: init_sdlstuff(int screenWidth, int screenHeight){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cerr<<"SDL_Init failed: "<<SDL_GetError()<<std::endl;
    return 1;
  }
  
  //Create a Window
  _window = SDL_CreateWindow("Guns Blood N' Ammo",
			     SDL_WINDOWPOS_CENTERED,
			     SDL_WINDOWPOS_CENTERED,
			     screenWidth, screenHeight,
			     SDL_WINDOW_OPENGL);
  if(_window == NULL){
    std::cerr << "Failed to create a SDL_Window: "
	      << SDL_GetError() << std::endl;
    return 2;
  }
  
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  if(_renderer == NULL){
    std::cerr << "Failed to create a SDL_Renderer: "
	      << SDL_GetError() << std::endl;
    return 3;
  }
  
  if(TTF_Init() != 0){
    std::cerr<<"TTF_Init failed: " << SDL_GetError()<<std::endl;
    return 4;
  }
  
  SDL_ShowCursor(SDL_DISABLE);
  return 0;
}
