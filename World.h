#include "Game.h"
#include "Character.h"
#include <SDL.h>
#include <map>
#ifndef WORLD_H
#define WORLD_H

class World{
 public:
  World();
  ~World();
  void draw(SDL_Renderer &, int, int);
  void update();
  
  int input(std::map<char,bool> &);
 private:
  Character* _player;

};

#endif
