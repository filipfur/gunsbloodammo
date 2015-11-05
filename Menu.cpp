#include "Menu.h"
#include "SDL_ttf.h"
#include <iostream>

Menu::Menu(std::vector<const char*> menuItems, std::vector<const char*> optionItems, const char* fontStyle){

  _currentItems = _menuItems = menuItems;
  _optionItems = optionItems;
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
  _titleColor1 = {0, 0, 0, 255};
  _titleColor2 = {255, 255, 255 , 255};
  _breadColor = {128, 128, 128, 255};
  _highlightColor = {255, 0, 0, 255};
  _bgColor = {200, 200, 200, 255};
  _currentSelection = 1;
  _subMenu = 0;

}

Menu::~Menu(){

}

void Menu::update(){

}

void Menu::draw(SDL_Renderer &renderer){
  SDL_SetRenderDrawColor(&renderer, _bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
  SDL_RenderClear(&renderer);
 
  SDL_Surface* text_surface;

  SDL_Rect menuPos;
  
  int itemAmount = _currentItems.size();
  for(int i = 0; i < itemAmount; ++i){
    if(i == 0){
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
    menuPos.y = 480/4 + i * 64;
    menuPos.w = w;
    menuPos.h = h;
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = w;
    src.h = h;
    if(SDL_RenderCopy(&renderer, text_texture, &src, &menuPos) != 0 ){
      std::cerr<<SDL_GetError()<<std::endl;
    }
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
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
    if(_subMenu == 0){
      int compare = _currentItems.size() - 1;
      if(_currentSelection == 1){
	return 1;
      }
      if(_currentSelection == 2){
	_subMenu = 1;
	_currentItems = _optionItems;
	_currentSelection = 0;
      }
      if(_currentSelection == compare){
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
