#include "Crosshair.h"

Crosshair::Crosshair(const char* filepath, int r, int g, int b) : _red(r), _green(g), _blue(b){
  _image = IMG_Load(filepath);
  _pos.x = 0;
  _pos.y = 0;
  _pos.w = _image->w;
  _pos.h = _image->h;
  _texture = NULL;

}

Crosshair::~Crosshair(){
  SDL_FreeSurface(_image);
  SDL_DestroyTexture(_texture);
}

void Crosshair::update(){

}

void Crosshair::draw(SDL_Renderer &renderer){
  if(_texture == NULL)
    _texture = SDL_CreateTextureFromSurface(&renderer, _image);
  SDL_SetTextureColorMod(_texture, _red, _green, _blue);
  SDL_RenderCopy(&renderer, _texture, NULL, const_cast<SDL_Rect*>(&_pos));
}

void Crosshair::setColor(Uint8 r, Uint8 g, Uint8 b){
  _red = r;
  _green = g;
  _blue = b;
}

int Crosshair::input(int mx, int my){
  _pos.x = mx - _pos.w/2;
  _pos.y = my - _pos.h/2;
  return 0;
}
