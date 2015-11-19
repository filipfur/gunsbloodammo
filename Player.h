#include <map>
#include "Character.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character{
public:

  Player(int x, int y, int width, int height, int hp, Weapon weapon);
  Player(int x, int y, int width, int height, Weapon weapon);
  Player(int x, int y, int width, int height);
  Player();

  int input(std::map<char,bool> &);

};

#endif
