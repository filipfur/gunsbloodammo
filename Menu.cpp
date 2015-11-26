#include "Menu.h"

Menu::Menu(std::vector<const char*> menuItems, std::vector<const char*> helpItems, std::vector<const char*> optionItems, std::vector<const char*> highscoreItems, const char* fontStyle){

  _currentItems = _menuItems = menuItems;
  _helpItems = helpItems;
  _optionItems = optionItems;
  _highscoreItems = highscoreItems;
  _titleFont = TTF_OpenFont(fontStyle, 72);
  _breadFont = TTF_OpenFont(fontStyle, 48);
  _highlightFont = TTF_OpenFont(fontStyle, 56);
  if(!_titleFont){
    std::cerr<<TTF_GetError()<<std::endl;
  }
  if(!_breadFont){
    std::cerr<<TTF_GetError()<<std::endl;
  }
  if(!_highlightFont){
    std::cerr<<TTF_GetError()<<std::endl;
  }
  _titleColor1 = {154, 255, 72, 255};
  _titleColor2 = {255, 255, 255 , 255};
  _breadColor = {128, 128, 128, 255};
  _highlightColor = {255, 0, 0, 255};
  _bgColor = {0, 0, 0, 255};
  _currentSelection = 1;
  _subMenu = 0;
  _currentCrosshairColor = 0;

}

Menu::~Menu(){

}

void Menu::update(){

  //Crosshair colors
  switch(_currentCrosshairColor){
  case 0:
    _crosshairColor = {255, 255, 0, 255};
    break;
  case 1:
    _crosshairColor = {255, 0, 0, 255};
    break;
  case 2:
    _crosshairColor = {0, 255, 0, 255};
    break;
  case 3:
    _crosshairColor = {0, 0, 255, 255};
    break;
  case 4:
    _crosshairColor = {0, 255, 255, 255};
    break;
  }

}

void Menu::updateHighscore(){
  _highscoreItems.clear();
  _highscoreItems.push_back("Highscore");
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
    _highscoreItems.push_back(output0);
  }
  ifs.close();
}

void Menu::draw(SDL_Renderer &renderer){
  SDL_SetRenderDrawColor(&renderer, _bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
  SDL_RenderClear(&renderer);
 
  SDL_Surface* text_surface;

  SDL_Rect menuPos;
  
  int itemAmount = _currentItems.size();
  for(int i = 0; i < itemAmount; ++i){
    if(i == 0){//Title
      if(!(text_surface = TTF_RenderText_Shaded(_titleFont, _currentItems.at(i), _titleColor1, _bgColor))){
	std::cerr<<TTF_GetError()<<std::endl;
      }
    }
    else if(i == _currentSelection){
      if(!(text_surface = TTF_RenderText_Shaded(_highlightFont, _currentItems.at(i), _highlightColor, _bgColor))){
	std::cerr<<TTF_GetError()<<std::endl;
      }
    }
    else{
      if(!(text_surface = TTF_RenderText_Shaded(_breadFont, _currentItems.at(i), _breadColor, _bgColor))){
	std::cerr<<TTF_GetError()<<std::endl;
      }
    }
    SDL_Texture* text_texture = NULL;
    text_texture = SDL_CreateTextureFromSurface(&renderer, text_surface);
    if(text_texture == NULL){
      std::cerr<<SDL_GetError()<<std::endl;
    }
    int w, h;
    if(SDL_QueryTexture(text_texture, NULL, NULL, &w, &h) != 0){
      std::cerr<<"Query: "<<SDL_GetError()<<std::endl;
    }
    menuPos.x = 640/2 - w/2;
    menuPos.y = 480/8 + i * 64;
    menuPos.w = w;
    menuPos.h = h;
    if(SDL_RenderCopy(&renderer, text_texture, NULL, &menuPos) != 0 ){
      std::cerr<<SDL_GetError()<<std::endl;
    }
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
  }

  if(_subMenu == 2){ //Options
    SDL_Surface* image = IMG_Load("crosshair_gap_1.png");
    if(image == NULL){
      std::cerr<<SDL_GetError()<<std::endl;
    }
    else{
      SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer, image);
      SDL_SetTextureColorMod(texture, _crosshairColor.r, _crosshairColor.g, _crosshairColor.b);
      const SDL_Rect rect = {3*640/4, 480/4+64, image->w, image->h};
      SDL_RenderCopy(&renderer, texture, NULL, &rect);
      SDL_DestroyTexture(texture);
      SDL_FreeSurface(image);
    }
  }
  
  
}

int Menu::input(std::map<char, bool> &keys){

  if(keys['W']){
    if(_currentSelection != 1 && _currentSelection != 0)
      _currentSelection--;
    keys['W'] = false;
  }
  if(keys['S']){
    int compare = _currentItems.size() - 1;
    if(_currentSelection != compare && _currentSelection != 0)
      _currentSelection++;
    keys['S'] = false;
  }

  if(keys[SDLK_SPACE]){
    if(_subMenu == 0 || _subMenu == 2){
      int NEWGAME = 1;
      int HELP = 2;
      int OPTIONS = 3;
      int HIGHSCORE = 4;
      int EXIT = _currentItems.size() - 1;
      if(_currentSelection == NEWGAME){
	if(_subMenu == 2){
	  _currentCrosshairColor++;
	  if(_currentCrosshairColor == 5) //MAX
	    _currentCrosshairColor = 0;
	}
	else
	  return 1;
      }
      else if(_currentSelection == HELP){
	if(_subMenu == 2){
	  _subMenu = 0;
	  _currentItems = _menuItems;
	  _currentSelection = 1;
	  int red = _crosshairColor.r;
	  int grn = _crosshairColor.g;
	  int blu = _crosshairColor.b;
	  std::ofstream file;
	  file.open("config.txt");
	  if(file.is_open()){
	    file <<red<<' '<<grn<<' '<<blu;
	    file.close();
	  }
	  else{
	    std::cerr<<"Couldnt open config.txt"<<std::endl;
	  }
	}
	else{
	  _subMenu = 1;
	  _currentItems = _helpItems;
	  _currentSelection = 0;
	}
      }
      else if(_currentSelection == OPTIONS){
	_subMenu = 2;
	_currentItems = _optionItems;
	_currentSelection = 1;
      }
      else if(_currentSelection == HIGHSCORE){
	_subMenu = 3;
	_currentItems = _highscoreItems;
	_currentSelection = 0;
      }
      else if(_currentSelection == EXIT){
	return 2;
      }
    }
    else{
      _subMenu = 0;
      _currentItems = _menuItems;
      _currentSelection = 1;
    }
    keys[SDLK_SPACE] = false;
  }

  return 0;

}
