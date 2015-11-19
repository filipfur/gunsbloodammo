#include "Player.h"

Player::Player(int x, int y, int width, int height, int hp, Weapon weapon){
  Character(x,y,width,height,hp,weapon);
}
Player::Player(int x, int y, int width, int height, Weapon weapon){
  Character(x,y,width,height,weapon);
}
Player::Player(int x, int y, int width, int height){
  Character(x,y,width,height);
}
Player::Player(){
  Character();
}


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
