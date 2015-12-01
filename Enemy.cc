#include "Enemy.h"

Enemy::Enemy(int x, int y, int hp, Weapon weapon){

}
Enemy::Enemy(int x, int y, Weapon weapon){

}
Enemy::Enemy(int x, int y){
  _texture = NULL;
  _surface = IMG_Load("enemy3.png");
  _hp = 100;
  _hpMax = 100;
  Weapon weapon(100, 100);
  _weapon = weapon;
  _x = x;
  _y = y;
  _pos.x = x;
  _pos.y = y;
  _pos.w = _surface->w;
  _pos.h = _surface->h;
  _dx = cos(0.5);
  _dy = sin(0.5);
  _angle = 0.5 * 180 / M_PI + 180;
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
  _angle = radians * 180 / M_PI + 180;
}

double Enemy::getDir(){
  return atan2(_dy,_dx);
}
