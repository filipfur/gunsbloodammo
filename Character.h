#include <SDL.h>
#include <map>
#include "Weapon.h"
#ifndef CHAR_H
#define CHAR_H

class Character{
 public:
  Character(int x, int y, int width, int height, Weapon weapon);
  Character(int x, int y, int width, int height);
  ~Character();

  int getX();
  int getY();
  int getWidth();
  int getHeight();
  Weapon getWeapon();
  int getAmmo();
  int getMaxAmmo();
  void draw(SDL_Renderer &, int, int);
  void update();

  int input(std::map<char,bool> &);

 private:

  SDL_Rect _pos;
  char _direction;
  double _dx, _dy;
  double _x, _y;
  int _width, _height;
  double MOVESPEED = 0.1;
  Weapon _weapon;

};

#endif
