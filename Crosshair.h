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
  void setColor(Uint8, Uint8, Uint8);
  int input(int, int);

 private:
  SDL_Rect _pos;
  SDL_Surface* _image;
  SDL_Texture* _texture;
  Uint8 _red, _green, _blue;

};

#endif
