#include "World.h"

World::World(){
  _map = new Map("map1.txt", "snow_on_stones.png", 64);
  _player = new Character(0, 0, 8, 8);
  _crosshair = new Crosshair("crosshair_gap_1.png", 0, 255, 0);
  _GUI = new GUI(_player);
  _cam.x = 0;
  _cam.y = 0;
}

World::~World(){

}

void World::draw(SDL_Renderer &renderer){
  SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
  SDL_RenderClear(&renderer);

  _map->draw(renderer, _cam.x, _cam.y);
  _player->draw(renderer, _cam.x, _cam.y);
  _crosshair->draw(renderer);
  _GUI->draw(renderer);
}

void World::update(){
  _player->update();
  _crosshair->update();
  _GUI->update();
  _player->decHp(1);
}

int World::input(std::map<char,bool> &keys, int mx, int my){
  _player->input(keys);
  _crosshair->input(mx, my);

  if(keys[SDLK_UP]){
    _cam.y -= _cam.speed;
    //keys[SDLK_UP] = false;
  }
  if(keys[SDLK_LEFT]){
    _cam.x -= _cam.speed;
    //keys[SDLK_LEFT] = false;
  }
  if(keys[SDLK_DOWN]){
    _cam.y += _cam.speed;
    //keys[SDLK_DOWN] = false;
  }
  if(keys[SDLK_RIGHT]){
    _cam.x += _cam.speed;
    //keys[SDLK_RIGHT] = false;
  }

  if(_cam.x < 0) _cam.x = 0;
  if(_cam.y < 0) _cam.y = 0;

  if(_cam.x > 2048-640) _cam.x = 2048-640;
  if(_cam.y > 2048-480) _cam.y = 2048-480;
  

  return 1;
}
