#include "Powerup.h"


//konstruktor
PowerUp::PowerUp (int x, int y, Type type, int value, int width, int height){
  _x = x;
  _y = y;
  _width = width;
  _height = height;
  _value = value;
  _type =  type;

  _pos.x = x;
  _pos.y = y;
  _pos.w = width;
  _pos.h = height;
}

//konstruktor
PowerUp::PowerUp (int x, int y, Type type, int value){
  _x = x;
  _y = y;
  _width = 20;
  _height = 20;
  _value = value;
  _type =  type;

  _pos.x = x;
  _pos.y = y;
  _pos.w = 20;
  _pos.h = 20;
}

//defaultkonstruktor
PowerUp::PowerUp (){
  _x = 5;
  _y = 5;
  _width = 20;
  _height = 20;
  _value = 10;
  _type = AMMO;

 _pos.x = 0;
  _pos.y = 0;
  _pos.w = 0;
  _pos.h = 0;
}

//destruktor
PowerUp::~PowerUp (){
}

int PowerUp::getX()
{
  return _x;
}

int PowerUp::getY()
{
  return _y;
}

int PowerUp:: getValue()
{
  return _value;
}

int PowerUp::getType()
{
  return _type;
}

void PowerUp::draw(SDL_Renderer &renderer, int x, int y){
  
  SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(&renderer, const_cast<SDL_Rect*>(&_pos));
  
}