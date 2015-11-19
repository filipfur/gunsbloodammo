#include "Projectile.h"


Projectile::Projectile(int x, int y, int width, int height, int dx, int dy, int damage){
  _x = x;
  _y = y;
  _width = width;
  _height = height;
  _dx = dx;
  _dy = dy;
  _damage = damage;

  _pos.x = x;
  _pos.y = y;
  _pos.w = width;
  _pos.h = height;

}


Projectile::Projectile(int width, int height, int damage){
  _x = 0;
  _y = 0;
  _width = width;
  _height = height;
  _dx = 0;
  _dy = 0;
  _damage = damage;

  _pos.x = 0;
  _pos.y = 0;
  _pos.w = 0;
  _pos.h = 0;
}

Projectile::Projectile(){
  _x = 0;
  _y = 0;
  _width = 0;
  _height = 0;
  _dx = 0;
  _dy = 0;
  _damage = 0;

  _pos.x = 0;
  _pos.y = 0;
  _pos.w = 0;
  _pos.h = 0;
}


Projectile::~Projectile(){

}



int Projectile::getX()
{
  return _x;
}

int Projectile::getY()
{
  return _y;
}



int Projectile::getWidth()
{
  return _width;
}

int Projectile::getHeight()
{
  return _height;
}


int Projectile::getDamage()
{
  return _damage;
}

double Projectile::getMoveSpeed(){
  return _movespeed;
}

double Projectile::getDir(){
  return atan2(_dy,_dx);
}

void Projectile::setDir(double radians)
{
  _dx = cos(radians);
  _dy = sin(radians);
}

void Projectile::setMoveSpeed(double speed){
  _movespeed = speed;
}


void Projectile::draw(SDL_Renderer &renderer, int x, int y){
  
  SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(&renderer, const_cast<SDL_Rect*>(&_pos));
  
}

void Projectile::update(){

  _x += _dx*_movespeed;
  _y += _dy*_movespeed;

  _pos.x = _x;
  _pos.y = _y;
}


