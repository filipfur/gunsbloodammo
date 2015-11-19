#include "Enemy.h"

Enemy::Enemy(int x, int y, int width, int height, int hp, Weapon weapon){
  Character(x,y,width,height,hp,weapon);
}
Enemy::Enemy(int x, int y, int width, int height, Weapon weapon){
  Character(x,y,width,height,weapon);
}
Enemy::Enemy(int x, int y, int width, int height){
  Character(x,y,width,height);
}
Enemy::Enemy(){
  Character();
}

void Enemy::setDir(double radians){
  _dx = cos(radians);
  _dy = sin(radians);
}

double Enemy::getDir(){
  return atan2(_dy,_dx);
}
