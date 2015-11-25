#include "Player.h"
#include <iostream>

Player::Player(int x, int y, int width, int height, int hp, Weapon weapon){
  Character(x,y,width,height,hp,weapon);
}
Player::Player(int x, int y, int width, int height, Weapon weapon){
  Character(x,y,width,height,weapon);
}
Player::Player(int x, int y, int width, int height){
  std::cout<<"width"<<width<<std::endl;
  //Character(x,y,width,height);
  _x = x;
  _y = y;
  _width = width;
  _height = height;
  std::cout<<"width CHARACTER"<<width<<std::endl;
  _hp = 100;
  _hpMax = 100;
  Weapon weapon(100,100);
  _weapon = weapon;

  _pos.x = x;
  _pos.y = y;
  _pos.w = width;
  _pos.h = height;

  _direction = 'W';
  _dx = _dy = 0;
}/*
Player::Player(){
  Character();
}
 */

int Player::input(std::map<char,bool> &keys){

  if(keys['W']){
    _direction = 'W';
    _dy = -1.0;
  }
  else if(keys['S']){
    _direction = 'S';
    _dy = 1.0;
  }
  else{
    _dy = 0;
  }
  if(keys['A']){
    _direction = 'A';
    _dx = -1.0;
  }
  else if(keys['D']){
    _direction = 'D';
    _dx = 1.0;
  }
  else{
    _dx = 0;
  }

  return 2;
}
