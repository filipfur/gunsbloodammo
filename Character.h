#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include "Weapon.h"
#include "Projectile.h"
#ifndef CHAR_H
#define CHAR_H

class Character{
 public:

  int getX();
  int getY();
  void setX(int x);
  void setY(int y);
  int getWidth();
  int getHeight();
  int getHp();
  int getMaxHp();
  double getSpeed();
  Weapon getWeapon();
  int getAmmo();
  int getMaxAmmo();

  void setWeapon(Weapon weapon);
  void setSpeed(double speed);
  void setHP(int i);

  Projectile* shoot(double, bool friendly = false);
  void decHp(int damage);
  void incHp(int hp_gain);
  void decAmmo();
  void incAmmo(int ammo_gain);
  void setAngle(double angle);
  void setMoving(bool b);
  SDL_Rect getRect();

  void draw(SDL_Renderer &, int, int);
  void update();

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
