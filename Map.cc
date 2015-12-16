#include "Map.h"

using namespace std;

Map::Map(std::string filepath, const char* tileset, int tilesize){
  _tilesize = tilesize;
  readMap(filepath);
  _tileset = IMG_Load(tileset);
  
  _canvas = SDL_CreateRGBSurface(0, _mapWidth*_tilesize,
				 _mapHeight*_tilesize, 32, 0, 0, 0, 0);
  _texture = NULL;
  int compare = _tiles.size();
  for(int i = 0; i < compare; i++){
    SDL_Rect temp;
    temp.x = _tiles.at(i).second*_tilesize % _tileset->w;
    temp.y = _tiles.at(i).second*_tilesize / _tileset->w * _tilesize;
    temp.w = _tilesize;
    temp.h = _tilesize;

    SDL_BlitSurface(_tileset, const_cast<SDL_Rect*>(&temp),
		    _canvas,&_tiles.at(i).first);
  }

}
Map::~Map(){

  SDL_FreeSurface(_tileset);
  SDL_FreeSurface(_canvas);
  SDL_DestroyTexture(_texture);

}

void Map::draw(SDL_Renderer &renderer, int x, int y){

  _pos.x = x;
  _pos.y = y;
  _pos.w = 640;
  _pos.h = 480;
  if(_texture == NULL)
    _texture = SDL_CreateTextureFromSurface(&renderer, _canvas);
  const SDL_Rect src = _pos;
  SDL_RenderCopy(&renderer, _texture, &src, NULL);

}

void Map::update(){

}

int Map::getTilesize(){
  return _tilesize;
}

int Map::getWidth(){
  return _mapWidth;
}

int Map::getHeight(){
    return _mapHeight;
  }

bool Map::readMap(string filepath){
  ifstream fileReader;
  fileReader.open(filepath, ifstream::in);
  int x = 0, y = 0;
  int counter = 0;
  string line;
  while(getline(fileReader, line)){

    std::stringstream linestream(line);
    int tileID;
    while(linestream >> tileID){
      SDL_Rect pos;
      pos.x = x*_tilesize;
      pos.y = y*_tilesize;
      pos.w = _tilesize;
      pos.h = _tilesize;
      _tiles.push_back(std::make_pair(pos, tileID));
      x++;
    }
    if(counter == 0)
      counter = x;
    x = 0;
    y++;
  }

  _mapWidth = counter;
  _mapHeight = y;
  return true;

}

bool Map::checkCollision(SDL_Rect rect){
  for(auto it = _tiles.begin(); it != _tiles.end(); ++it){
    if(SDL_HasIntersection(&it->first, &rect)){
      if(it->second != 16 && it->second != 18 &&
	 it->second != 19 && it->second != 8){
	return true;
      }
    }
  }
  return false;
}
