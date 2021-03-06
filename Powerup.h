#include <SDL.h>
#include <SDL_image.h>
#include <map>

#ifndef POWER_H
#define POWER_H

class Powerup{

 public:

  //enum Type{AMMO, WEAPON, HEALTH};
  using Type  = int;
  int AMMO = 0;
  int WEAPON = 1;
  int HEALTH = 2;

  Powerup(int x, int y, Type type, int value);
  Powerup(){}
  ~Powerup();
 

  int getX();
  int getY();
  int getValue();
  int getType();
  SDL_Rect getRect();

  void draw(SDL_Renderer &, int ,int);
 

 private:
  double _x, _y;
  int _width, _height;
  int _value;
  Type _type;
  SDL_Rect _pos;
  SDL_Surface* _surface;
  SDL_Texture* _texture;
};

#endif
