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

int Character::keyPressed(char key){

  if(key == 'W'){
    _direction = 'W';
    _dy = -MOVESPEED;
  }
  if(key == 'A'){
    _direction = 'A';
    _dx = -MOVESPEED;
  }
  if(key == 'S'){
    _direction = 'S';
    _dy = MOVESPEED;
  }
  if(key == 'D'){
    _direction = 'D';
    _dx = MOVESPEED;
  }

  return 2;
}

void Character::keyReleased(char key){
  
  if(key == 'W'){
    _dy = 0;
  }
  if(key == 'A'){
    _dx = 0;
  }
  if(key == 'S'){
    _dy = 0;
  }
  if(key == 'D'){
    _dx = 0;
  }

}
