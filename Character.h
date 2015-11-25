#include <SDL.h>
#include <map>
#include "Weapon.h"
#include "Projectile.h"
#ifndef CHAR_H
#define CHAR_H

class Character{
 public:
  
  Character(int x, int y, int width, int height, int hp, Weapon weapon);
  Character(int x, int y, int width, int height, Weapon weapon);
  Character(int x, int y, int width, int height);
  Character(){}
  
  ~Character();

  int getX();
  int getY();
  int getWidth();
  int getHeight();
  int getHp();
  double getSpeed();
  Weapon getWeapon();
  int getAmmo();
  int getMaxAmmo();

  void setWeapon(Weapon weapon);
  void setSpeed(double speed);

  Projectile shoot();
  void decHp(int damage);
  void incHp(int hp_gain);
  void decAmmo();
  void incAmmo(int ammo_gain);


  void draw(SDL_Renderer &, int, int);
  void update();

  //int input(std::map<char,bool> &);
  //moved to Player class

 protected:

  SDL_Rect _pos;
  char _direction;
  double _dx, _dy;
  double _x, _y;
  int _width, _height;
  double _movespeed = 1;
  Weapon _weapon;
  int _hp;
  int _hpMax;
};

#endif
