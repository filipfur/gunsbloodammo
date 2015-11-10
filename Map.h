#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

class Map{

 public:

  Map(std::string, const char*, int);
  ~Map();
  void draw(SDL_Renderer &, int, int);
  void update();
  
 private:

  bool readMap(std::string);
  int _tilesize;
  SDL_Surface* _tileset;
  std::vector<std::pair<SDL_Rect, int>> _tiles;

};

#endif
