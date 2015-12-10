#include <SDL.h>
#include <map>
#include "Weapon.h"
#include "Projectile.h"
#include <SDL_image.h>
#ifndef CHAR_H
#define CHAR_H

class Character{
 public:

  int getX();
  int getY();
  void setX(int x){
    _x = x;
	_pos.x = x;
  }
  void setY(int y){
    _y = y;
	_pos.y = y;
  }
  int getWidth();
  int getHeight();
  int getHp();
  int getMaxHp(){
    return _hpMax;
  }
  double getSpeed();
  Weapon getWeapon();
  int getAmmo();
  int getMaxAmmo();

  void setWeapon(Weapon weapon);
  void setSpeed(double speed);

  Projectile* shoot(double, bool friendly = false);
  void decHp(int damage);
  void incHp(int hp_gain);
  void decAmmo();
  void incAmmo(int ammo_gain);
  void setAngle(double angle){
    _angle = angle;
  }
  void setMoving(bool b) {
	  _move = b;
  }
  SDL_Rect getRect(){
    return _rect;
  }

  void draw(SDL_Renderer &, int, int);
  void update();

  //int input(std::map<char,bool> &);
  //moved to Player class

 protected:

  SDL_Rect _pos, _rect;
  char _direction;
  double _dx, _dy;
  double _x, _y;
  int _width, _height;
  double _movespeed = 1;
  Weapon _weapon;
  int _hp;
  int _hpMax;
  SDL_Surface* _surface;
  SDL_Texture* _texture;
  double _angle;
  bool _move = true;
};

#endif
