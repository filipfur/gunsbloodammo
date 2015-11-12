#include <SDL.h>
#include "SDL_ttf.h"
#include <string>
#include "Character.h"
#include <iostream>
#ifndef GUI_H
#define GUI_H

class GUI{

 public:
  GUI(Character*, const char* fontStyle = "BloodLust.ttf");
  ~GUI();

  void draw(SDL_Renderer&);
  void update();

 private:
  TTF_Font* _font;
  Character* _monitored;
  SDL_Color _healthColor, _ammoColor, _bgColor;

};

#endif
