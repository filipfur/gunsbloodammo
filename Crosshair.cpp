#include "Crosshair.h"

Crosshair::Crosshair(const char* filepath, int r, int g, int b){
  _color = {0, 0, 0, 255};
  _image = IMG_Load(filepath);
  _pos.x = 0;
  _pos.y = 0;
  _pos.w = _image->w;
  _pos.h = _image->h;

  
  // SDL_PixelFormat *fmt;
  // Uint32 temp, pixel;
  // Uint8 red, green, blue, alpha;
  // fmt = _image->format;
  // SDL_LockSurface(_image);
  // for(int y = 0; y < _image->h; y++){
  //   for(int x = 0; x < _image->w; x++){
  //     std::cout<<x<<*((Uint32*)_image->pixels)<<std::endl;
  //     /* Get Red component */
  //     temp=pixel&fmt->Rmask; /* Isolate red component */
  //     temp=temp>>fmt->Rshift;/* Shift it down to 8-bit */
  //     temp=temp<<fmt->Rloss; /* Expand to a full 8-bit number */
  //     red=(Uint8)temp;

  //     /* Get Green component */
  //     temp=pixel&fmt->Gmask; /* Isolate green component */
  //     temp=temp>>fmt->Gshift;/* Shift it down to 8-bit */
  //     temp=temp<<fmt->Gloss; /* Expand to a full 8-bit number */
  //     green=(Uint8)temp;

  //     /* Get Blue component */
  //     temp=pixel&fmt->Bmask; /* Isolate blue component */
  //     temp=temp>>fmt->Bshift;/* Shift it down to 8-bit */
  //     temp=temp<<fmt->Bloss; /* Expand to a full 8-bit number */
  //     blue=(Uint8)temp;

  //     /* Get Alpha component */
  //     temp=pixel&fmt->Amask; /* Isolate alpha component */
  //     temp=temp>>fmt->Ashift;/* Shift it down to 8-bit */
  //     temp=temp<<fmt->Aloss; /* Expand to a full 8-bit number */
  //     alpha=(Uint8)temp;
  //   }
  // }
  // SDL_UnlockSurface(_image);

}

Crosshair::~Crosshair(){
  SDL_FreeSurface(_image);
}

void Crosshair::update(){

}

void Crosshair::draw(SDL_Renderer &renderer){
  SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer, _image);
  SDL_RenderCopy(&renderer, texture, NULL, const_cast<SDL_Rect*>(&_pos));
  SDL_DestroyTexture(texture);
}

int Crosshair::input(int mx, int my){
  _pos.x = mx - _pos.w/2;
  _pos.y = my - _pos.h/2;
  return 0;
}
