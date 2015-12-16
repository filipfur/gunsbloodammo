#include "Enemy.h"

Enemy::Enemy(int x, int y, int hp, Weapon weapon){

}
Enemy::Enemy(int x, int y, Weapon weapon){

}
Enemy::Enemy(int x, int y, const char* filepath, const char* filepath2){
  _texture = NULL;
  SDL_Surface* enemy = IMG_Load(filepath);
  _hp = 100;
  _hpMax = 100;
  Weapon weapon(100, 100, filepath2, "never used");
  _weapon = weapon;
  _surface = SDL_CreateRGBSurface(0, enemy->w + _weapon.getSurface()->w,
				  enemy->h, 32, 0x000000FF, 0x0000FF00,
				  0x00FF0000, 0xFF000000);
  _x = x;
  _y = y;
  _width = enemy->w;
  _height = enemy->h;
  _rect.x = x;
  _rect.y = y;
  _rect.w = _width;
  _rect.h = _height;
  _pos.x = x;
  _pos.y = y;
  _pos.w = _surface->w;
  _pos.h = _surface->h;
  _dx = cos(0.5);
  _dy = sin(0.5);
  _angle = 0.5 * 180 / M_PI + 180;

  SDL_Rect src = { 0, 0, enemy->w, enemy->h };
  SDL_Rect src2 = { enemy->w - 4, enemy->h/2-_weapon.getSurface()->h/2,
		    _weapon.getSurface()->w, _weapon.getSurface()->h };
  SDL_BlitSurface(enemy, NULL, _surface, &src);
  SDL_BlitSurface(_weapon.getSurface(), NULL, _surface, &src2);
}

void Enemy::update() {
  Character::update();
}

void Enemy::newDir() {
  setDir(getDir()+0.1);
}

void Enemy::setDir(double radians){
  _dx = cos(radians);
  _dy = sin(radians);
  _angle = radians * 180 / M_PI;
}

double Enemy::getDir(){
  return atan2(_dy,_dx);
}
