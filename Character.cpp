#include "Character.h"

Character::Character(int x, int y, int width, int height){
  _x = x;
  _y = y;
  _width = width;
  _height = height;

  _pos.x = x;
  _pos.y = y;
  _pos.w = width;
  _pos.h = height;

  _direction = 'W';
  _dx = _dy = 0;

}

Character::~Character(){

}

int getX()
{
  return _x;
}

int getY()
{
  return _y;
}

int getWidth()
{
  return _width;
}

int getHeight()
{
  return __height;
}


void Character::draw(SDL_Renderer &renderer, int x, int y){
  
  SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(&renderer, const_cast<SDL_Rect*>(&_pos));
  
}

void Character::update(){

  _x += _dx;
  _y += _dy;

  _pos.x = _x;
  _pos.y = _y;

}

int Character::input(std::map<char,bool> &keys){

  if(keys['W']){
    _direction = 'W';
    _dy = -MOVESPEED;
  }
  else if(keys['S']){
    _direction = 'S';
    _dy = MOVESPEED;
  }
  else{
    _dy = 0;
  }
  if(keys['A']){
    _direction = 'A';
    _dx = -MOVESPEED;
  }
  else if(keys['D']){
    _direction = 'D';
    _dx = MOVESPEED;
  }
  else{
    _dx = 0;
  }

  return 2;
}
