#ifndef CROSS_H
#define CROSS_H
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Crosshair{
 public:
  Crosshair(const char*, int, int, int);
  ~Crosshair();
  
  void update();
  void draw(SDL_Renderer &);
  int input(int, int);

 private:
  SDL_Rect _pos;
  SDL_Surface* _image;
  SDL_Color _color;

};

#endif
