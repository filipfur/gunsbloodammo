#include <SDL.h>
#undef main
#include <vector>
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <string>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

class Menu{

 public:
  Menu(std::vector<const char*>, std::vector<const char*>,
       std::vector<const char*>, std::vector<const char*>,
       const char* fontStyle = "BloodLust.ttf");
  ~Menu();

  void update();
  void updateHighscore();
  void draw(SDL_Renderer &);

  int input(std::map<char,bool> &);

  int get_difficulty();

 private:

  std::vector<const char*> _currentItems, _menuItems,
    _helpItems,_optionItems, _highscoreItems;
  TTF_Font* _titleFont;
  TTF_Font* _breadFont;
  TTF_Font* _highlightFont;
  SDL_Color _titleColor1, _titleColor2, _breadColor,
    _highlightColor, _bgColor, _crosshairColor;
  int _currentSelection, _subMenu, _currentCrosshairColor;
  int _difficulty = 0;

};
