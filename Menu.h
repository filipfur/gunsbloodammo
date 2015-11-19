#include <SDL.h>
#include <vector>
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <map>
#include <fstream>
#include <iostream>

class Menu{

 public:
  Menu(std::vector<const char*>, std::vector<const char*>, std::vector<const char*>, const char* fontStyle = "BloodLust.ttf");
  ~Menu();

  void update();
  void draw(SDL_Renderer &);

  int input(std::map<char,bool> &);

 private:

  std::vector<const char*> _currentItems, _menuItems, _helpItems,_optionItems;
  TTF_Font* _titleFont;
  TTF_Font* _breadFont;
  TTF_Font* _highlightFont;
  SDL_Color _titleColor1, _titleColor2, _breadColor, _highlightColor, _bgColor, _crosshairColor;
  int _currentSelection, _subMenu, _currentCrosshairColor;

};
