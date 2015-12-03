#include "Powerup.h"

//konstruktor
Powerup::Powerup(int x, int y, Type type, int value){

  _surface = IMG_Load("bullet.png");
  _x = x;
  _y = y;
  _width = _surface->w;
  _height = _surface->h;
  _value = value;
  _type =  type;

  _pos.x = x;
  _pos.y = y;
  _pos.w = _surface->w;
  _pos.h = _surface->h;
  
  _texture = NULL;
}

//destruktor
Powerup::~Powerup(){
}

int Powerup::getX()
{
  return _x;
}

int Powerup::getY()
{
  return _y;
}

int Powerup:: getValue()
{
  return _value;
}

int Powerup::getType()
{
  return _type;
}

void Powerup::draw(SDL_Renderer &renderer, int x, int y){

  if(_texture == NULL){
    _texture = SDL_CreateTextureFromSurface(&renderer, _surface);
  }
  const SDL_Rect rect = {_pos.x-x, _pos.y-y, _pos.w, _pos.h};
  SDL_RenderCopy(&renderer, _texture, NULL, &rect);
  
}
