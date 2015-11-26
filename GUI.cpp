#include "GUI.h"


GUI::GUI(Character* monitored, const char* fontStyle){
  _font = TTF_OpenFont(fontStyle, 52);
  if(!_font){
    std::cerr<<TTF_GetError()<<std::endl;
  };
  _healthColor = {255, 0, 0, 255};
  _ammoColor = {154, 255, 72, 255};
  _bgColor = {0, 0, 0, 255};
  _monitored = monitored;
}

GUI::~GUI(){

}

void GUI::draw(SDL_Renderer& renderer, const int currtime){
  SDL_SetRenderDrawColor(&renderer,_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
  const SDL_Rect rect = {0,480-64,640,64};
  SDL_RenderFillRect(&renderer, &rect);

  SDL_Surface* health_surface;
  SDL_Surface* ammo_surface;
  SDL_Surface* time_surface;

  char output[100];
  strcpy(output,"HP: ");
  strcat(output,std::to_string(_monitored->getHp()).c_str());
  strcat(output,"/");
  //strcat(output,std::to_string(_monitored->getMaxHp()).c_str());
  const char* pointer = output;
  if(!(health_surface = TTF_RenderText_Solid(_font, pointer, _healthColor))){
    std::cerr<<TTF_GetError()<<std::endl;
  }

  strcpy(output,"AMMO: ");
  strcat(output,std::to_string(_monitored->getAmmo()).c_str());
  strcat(output,"/");
  strcat(output,std::to_string(_monitored->getMaxAmmo()).c_str());
  if(!(ammo_surface = TTF_RenderText_Solid(_font, pointer, _ammoColor))){
    std::cerr<<TTF_GetError()<<std::endl;
  }

  strcpy(output,"TIME: ");
  strcat(output,std::to_string(currtime).c_str());
  if(!(time_surface = TTF_RenderText_Solid(_font, pointer, _ammoColor))){
    std::cerr<<TTF_GetError()<<std::endl;
  }
  
  SDL_Texture* health_texture = NULL;
  SDL_Texture* ammo_texture = NULL;
  SDL_Texture* time_texture = NULL;

  time_texture = SDL_CreateTextureFromSurface(&renderer, time_surface);
  health_texture = SDL_CreateTextureFromSurface(&renderer, health_surface);
  ammo_texture = SDL_CreateTextureFromSurface(&renderer, ammo_surface);
  if(health_texture == NULL || ammo_texture == NULL || time_texture == NULL){
    std::cerr<<SDL_GetError()<<std::endl;
  }
  SDL_Rect dest;
  dest.x = 0 + 4;
  dest.y = 480 - health_surface->h;
  dest.w = health_surface->w;
  dest.h = health_surface->h;
  if(SDL_RenderCopy(&renderer, health_texture, NULL, &dest) != 0){
    std::cerr<<SDL_GetError()<<std::endl;
  }

  dest.x = 640 - ammo_surface->w - 4;
  dest.y = 480 - ammo_surface->h;
  dest.w = ammo_surface->w;
  dest.h = ammo_surface->h;
  if(SDL_RenderCopy(&renderer, ammo_texture, NULL, &dest) != 0){
    std::cerr<<SDL_GetError()<<std::endl;
  }

  dest.x = 2;
  dest.y = 2;
  dest.w = time_surface->w;
  dest.h = time_surface->h;
  if(SDL_RenderCopy(&renderer, time_texture, NULL, &dest) != 0){
    std::cerr<<SDL_GetError()<<std::endl;
  }

  SDL_DestroyTexture(health_texture);
  SDL_DestroyTexture(ammo_texture);
  SDL_DestroyTexture(time_texture);
  SDL_FreeSurface(health_surface);
  SDL_FreeSurface(ammo_surface);
  SDL_FreeSurface(time_surface);
}

void GUI::update(){
}
