#include "Projectile.h"

Projectile::Projectile(int width, int height, int damage){
  _x = 0;
  _y = 0;
  _width = width;
  _height = height;
  _dx = 0;
  _dy = 0;
  _damage = damage;

  
  _surface = NULL;
  _surface = IMG_Load("bullet.png");
  if (_surface == NULL) {
	  std::cerr << SDL_GetError() << std::endl;
  }
  _texture = NULL;

  _pos.x = 0;
  _pos.y = 0;
  _pos.w = _surface->w;
  _pos.h = _surface->h;

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

void Projectile::setPos(int x, int y){
  _x = x;
  _y = y;
  _pos.x = x;
  _pos.y = y;
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

void Projectile::setFriendly() {
  _friendly = true;
}

bool Projectile::isFriendly() {
  return _friendly;
}

double Projectile::getMoveSpeed(){
  return _movespeed;
}

SDL_Rect Projectile::getRect(){
  return _pos;
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
  
  SDL_SetRenderDrawColor(&renderer, 255, 255, 206, 255);
  const SDL_Rect rect = {_pos.x-x, _pos.y-y, _pos.w, _pos.h};
  if(_texture == NULL)
    _texture = SDL_CreateTextureFromSurface(&renderer, _surface);
  SDL_RenderCopyEx(&renderer, _texture, NULL, &rect,
		   atan2(_dy, _dx) * 180 / M_PI + 90, NULL, SDL_FLIP_NONE);
  
}

void Projectile::update(){

  _x += _dx*_movespeed;
  _y += _dy*_movespeed;

  _pos.x = _x;
  _pos.y = _y;
}


