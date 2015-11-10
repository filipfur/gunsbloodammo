#include <SDL.h>
#include <map>
#ifndef PROJ_H
#define PROJ_H
class Projectile{
 public:
  Projectile(int x, int y, int width, int height, int dx, int dy, int damage);
  Projectile(int width, int height, int damage);
  ~Projectile();


  int getX();
  int getY();
  int getWidth();
  int getHeight();
  
  int getDamage();

  void draw(SDL_Renderer &, int, int);
  void update();



 private:

  SDL_Rect _pos;
  double _dx, _dy;
  double _x, _y;
  int _width, _height;
  double MOVESPEED = 0.1;

  int _damage;

};

#endif
