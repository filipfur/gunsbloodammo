
#include "Character.h"
#include <math.h>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Character{
public:

  Enemy(int x, int y, int width, int height, int hp, Weapon weapon);
  Enemy(int x, int y, int width, int height, Weapon weapon);
  Enemy(int x, int y, int width, int height);
  //Enemy();
  ~Enemy(){}
  void setDir(double radians);
  double getDir();
};

#endif
