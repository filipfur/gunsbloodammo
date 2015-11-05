#include "World.h"

World::World(){
  _player = new Character(0, 0, 8, 8);
}

World::~World(){

}

void World::draw(SDL_Renderer &renderer, int x, int y){
  SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
  SDL_RenderClear(&renderer);
  _player->draw(renderer, x, y);
}

void World::update(){
  _player->update();
}

int World::keyPressed(char key){
  _player->keyPressed(key);
  return 1;
}

void World::keyReleased(char key){
  _player->keyReleased(key);
}
