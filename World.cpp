#include "World.h"

World::World(int x, int y, const char* mapFile, const char* tileFile){
  _map = new Map(mapFile, tileFile, 64);
  _player = new Player(x, y, 8, 8);
  std::ifstream file("config.txt");
  int r,g,b;
  if(file.is_open()){
    file>>r>>g>>b;
    file.close();
    std::cout<<r<<' '<<g<<' '<<b<<std::endl;
  }
  else{
    std::cerr<<"Couldnt open config.txt"<<std::endl;
  }

  _crosshair = new Crosshair("crosshair_gap_1.png", r, g, b);
  _GUI = new GUI(_player);
  _cam.x = 0;
  _cam.y = 0;
}

World::~World(){

  delete(_crosshair);
  delete(_GUI);
  delete(_map);
  delete(_player);

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
  //_player->decHp(1);
}

int World::input(std::map<char,bool> &keys, int mx, int my){

  if(_player->getHp() <= 0){
    return 3;
  }

  if(_player->getX() >= 480){
    return 4;
  }

  _player->input(keys);
  _crosshair->input(mx, my);

  if(keys[SDLK_ESCAPE]){
    return 0;
  }

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
