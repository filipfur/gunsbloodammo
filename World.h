#include "Game.h"
#include "Character.h"
#include "Crosshair.h"
#include <SDL.h>
#include <map>
#include "Map.h"
#ifndef WORLD_H
#define WORLD_H

struct Camera{
  double x;
  double y;
  int speed = 8;
};

class World{
 public:
  World();
  ~World();
  void draw(SDL_Renderer &);
  void update();
  
  int input(std::map<char,bool> &, int, int);
 private:
  Camera _cam;
  Map* _map;
  Character* _player;
  Crosshair* _crosshair;

};

#endif
