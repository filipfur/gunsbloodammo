#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <map>
#include <string>

class Map{

 public:

  Map(std::string, const char*, int);
  ~Map();
  void draw(SDL_Renderer &, int, int);
  void update();

  int getTilesize(){
    return _tilesize;
  }
  int getWidth(){
    return _mapWidth;
  }
  int getHeight(){
    return _mapHeight;
  }
  bool checkCollision(SDL_Rect);
  
 private:

  bool readMap(std::string);
  int _tilesize, _mapWidth, _mapHeight;
  SDL_Surface* _tileset;
  SDL_Surface* _canvas;
  SDL_Texture* _texture;
  SDL_Rect _pos;

  std::vector<std::pair<SDL_Rect, int>> _tiles;
  std::multimap<SDL_Rect, int> _tilemap;

};

#endif
