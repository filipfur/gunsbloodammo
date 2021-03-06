#include <SDL.h>
#include <map>
#include <SDL_image.h>
#include <iostream>
#ifndef PROJ_H
#define PROJ_H

class Projectile{
 public:
  Projectile(int width, int height, int damage);

  Projectile() {}

  ~Projectile();


  int getX();
  int getY();
  void setPos(int x, int y);
  int getWidth();
  int getHeight();
  int getDamage();
  void setFriendly();
  bool isFriendly();

  double getMoveSpeed();
  SDL_Rect getRect();

  double getDir();
  void setDir(double radians);
  void setMoveSpeed(double speed);

  void draw(SDL_Renderer &, int, int);
  void update();



 private:

  SDL_Rect _pos;
  double _dx, _dy;
  double _x, _y;
  double _angle;
  int _width, _height;
  double _movespeed = 5;
  bool _friendly = false;
  int _damage;
  SDL_Surface* _surface;
  SDL_Texture* _texture;

};

#endif
