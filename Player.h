#include <map>
#include <math.h>
#include "Character.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character{
public:
  
  Player(Player* other){
    _angle = other->_angle;
    _dx = _dy = 0;
    _x = other->_x;
    _y = other->_y;
    _width = other->_width;
    _height = other->_height;
    _surface = other->_surface;
    _texture = other->_texture;
    _hp = other-> _hp;
    _hpMax = other->_hpMax;
    _weapon = other->_weapon;
    _movespeed = other->_movespeed;
  }
  
  Player(int x, int y, int hp, Weapon weapon);
  Player(int x, int y, Weapon weapon);
  Player(int x, int y);
  ~Player(){}

  int input(std::map<char,bool> &, int, int, bool, bool);

};

#endif
