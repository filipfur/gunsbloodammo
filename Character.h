#include <SDL.h>
#ifndef CHAR_H
#define CHAR_H

class Character{
 public:
  Character(int, int, int, int);
  ~Character();

  void draw(SDL_Renderer &, int, int);
  void update();

  int keyPressed(char);
  void keyReleased(char);

 private:

  SDL_Rect _pos;
  char _direction;
  double _dx, _dy;
  double _x, _y;
  int _width, _height;
  const static int MOVESPEED = 0.1;
  

};

#endif
