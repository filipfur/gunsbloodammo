#include "Player.h"

Player::Player(int x, int y, int hp, Weapon weapon){
}
Player::Player(int x, int y, Weapon weapon){
}
Player::Player(int x, int y){
  _texture = NULL;
  SDL_Surface* player = IMG_Load("player.png");
  Weapon weapon(100, 100, "m4.png", "pistol_icon.png");
  _weapon = weapon;
  _surface = SDL_CreateRGBSurface(0, player->w + _weapon.getSurface()->w, player->h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

  _hp = 100;
  _hpMax = 100;
  _width = player->w;
  _height = player->h;
  
  _x = x;
  _y = y;
  _rect.x = x;
  _rect.y = y;
  _rect.w = _width;
  _rect.h = _height;
  _pos.x = x;
  _pos.y = y;
  _pos.w = _surface->w;
  _pos.h = _surface->h;
  _dx = _dy = _angle = 0;
  SDL_Rect src = { 0, 0, player->w, player->h };
  SDL_Rect src2 = { player->w - 4, player->h/2-_weapon.getSurface()->h/2,
		    _weapon.getSurface()->w, _weapon.getSurface()->h };
  SDL_BlitSurface(player, NULL, _surface, &src);
  SDL_BlitSurface(_weapon.getSurface(), NULL, _surface, &src2);
  _movespeed = 2;
}

int Player::input(std::map<char,bool> &keys, int mouseX, int mouseY,
		  bool mouseR, bool mouseL){

  if(keys['W']){
    _direction = 'W';
	if (keys['A'] || keys['D']) {
		_dy = -1 / sqrt(2);
	}
	else
		_dy = -1.0;
  }
  else if(keys['S']){
    _direction = 'S';
	if (keys['A'] || keys['D']) {
		_dy = 1 / sqrt(2);
	}
	else
		_dy = 1.0;
  }
  else{
    _dy = 0;
  }
  if(keys['A']){
    _direction = 'A';
	if (keys['W'] || keys['S']) {
		_dx = -1 / sqrt(2);
	}
	else
		_dx = -1.0;
  }
  else if(keys['D']){
    _direction = 'D';
	if (keys['W'] || keys['S']) {
		_dx = 1 / sqrt(2);
	}
	else
		_dx = 1.0;
  }
  else{
    _dx = 0;
  }

  return 2;
}
