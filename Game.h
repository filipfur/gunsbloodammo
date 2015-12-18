#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "Menu.h"
#include "World.h"
#include "Player.h"

class Game {
public:
  Game();
  virtual ~Game();
  int run(int, int, int, bool intro = false);
private:
  //options
  const static int MENU = 0;
  const static int GAMEPLAY = 1;
  const static int EXIT = 2;
  const static int GAMEOVER = 3;
  const static int NEXTLEVEL = 4;
  const static int WINNING = 5;

  void set_highscoreItems(std::vector<const char*> &);
  void run_intro();
  void init_levels();
  void run_gameplay();
  void run_gameover();
  void run_menu();
  void run_winning();
  void init_menu();
  int init_sdlstuff(int screenWidth, int screenHeight);

  SDL_Renderer* _renderer;
  SDL_Window* _window;
  Menu* _menu;
  std::vector<World*> _levels;
  std::vector<World*>::iterator _currentLevel;
  std::map<char, bool> _keys;
  int _mouseX, _mouseY;
  bool _mouseR, _mouseL;
  int _currtime = 0;
  int gameState = MENU;
  int _game_speed;
  char key;
  SDL_Event input;

  std::chrono::high_resolution_clock::time_point fps_start;
  std::chrono::high_resolution_clock::time_point refresh_start;
  int frames = 0;

};

#endif
