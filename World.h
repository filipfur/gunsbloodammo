#include "Game.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "Projectile.h"
#include <SDL.h>
#include <map>
#include <vector>
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
  World(int, int, std::vector<pair<int,int>>, const char*, const char*);
  ~World();
  void draw(SDL_Renderer &, const int);
  void update();
  
  int input(std::map<char,bool> &, int, int, bool, bool);
 private:
  Camera _cam;
  Map* _map;
  Player* _player;
  vector<Enemy*> _enemies;
  Crosshair* _crosshair;
  GUI* _GUI;
  std::vector<Projectile*> _projectiles;
  

};

#endif
