#include <SDL.h>
#include <map>
#ifndef PROJ_H
#define PROJ_H

class Projectile{
 public:
  Projectile(int x, int y, int width, int height, int dx, int dy, int damage);
  Projectile(int width, int height, int damage);

  Projectile();

  ~Projectile();


  int getX();
  int getY();
  int getWidth();
  int getHeight();
  int getDamage();
  double getMoveSpeed();

  double getDir();
  void setDir(double radians);
  void setMoveSpeed(double speed);

  void draw(SDL_Renderer &, int, int);
  void update();



 private:

  SDL_Rect _pos;
  double _dx, _dy;
  double _x, _y;
  int _width, _height;
  double _movespeed = 0.1;

  int _damage;

};

#endif
