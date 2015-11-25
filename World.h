#include "Game.h"
#include "Character.h"
#include "Player.h"
#include "Crosshair.h"
#include <SDL.h>
#include <map>
#include "Map.h"
#include "GUI.h"
#include <iostream>
#include <fstream>
#ifndef WORLD_H
#define WORLD_H

struct Camera{
  double x;
  double y;
  int speed = 8;
};

class World{
 public:
  World(int, int, const char*, const char*);
  ~World();
  void draw(SDL_Renderer &);
  void update();
  
  int input(std::map<char,bool> &, int, int);
 private:
  Camera _cam;
  Map* _map;
  Player* _player;
  Crosshair* _crosshair;
  GUI* _GUI;

};

#endif
