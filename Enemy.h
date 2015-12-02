
#include "Character.h"
#include <math.h>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Character{
public:

  Enemy(int x, int y, int hp, Weapon weapon);
  Enemy(int x, int y, Weapon weapon);
  Enemy(int x, int y, const char*, const char*);
  ~Enemy(){}
  void newDir();
  void update();
  void setDir(double radians);
  double getDir();
};

#endif
