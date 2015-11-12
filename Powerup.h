#include <SDL.h>
#include <map>
#ifndef POWER_H
#define POWER_H

class PowerUp{

 public:

  //enum Type{AMMO, WEAPON, HEALTH};
  using Type  = int;
  int AMMO = 0;
  int WEAPON = 1;
  int HEALTH = 2;

  PowerUp (int x, int y, Type type, int value, int width, int height);
  PowerUp (int x, int y, Type type, int value);
  PowerUp();
  ~PowerUp();
 

  int getX();
  int getY();
  int getValue();
  int getType();

  void draw(SDL_Renderer &, int ,int);
 

 private:
  double _x, _y;
  int _width, _height;
  int _value;
  Type _type;
  SDL_Rect _pos;
  
};

#endif
