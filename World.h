#include "Game.h"
#include "Character.h"
#include <SDL.h>
#ifndef WORLD_H
#define WORLD_H

class World{
 public:
  World();
  ~World();
  void draw(SDL_Renderer &, int, int);
  void update();
  
  int keyPressed(char);
  void keyReleased(char);
 private:
  Character* _player;

};

#endif
