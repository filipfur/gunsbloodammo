#include "Map.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Map::Map(std::string filepath, const char* tileset, int tilesize){
  _tilesize = tilesize;
  readMap(filepath);
  _tileset = IMG_Load(tileset);
  
}
Map::~Map(){}

void Map::draw(SDL_Renderer &renderer, int x, int y){

  SDL_Surface* canvas = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);

  int compare = _tiles.size();
  //cout<<compare<<endl;
  for(int i = 0; i < compare; i++){
    SDL_Rect temp;
    temp.x = _tiles.at(i).second*_tilesize % _tileset->w;
    temp.y = _tiles.at(i).second*_tilesize / _tileset->w;
    cout<<"("<<temp.x<<"; "<<temp.y<<")"<<" : "<<_tiles.at(i).second<<endl;
    temp.w = _tilesize;
    temp.h = _tilesize;

    SDL_BlitSurface(_tileset, const_cast<SDL_Rect*>(&temp), canvas,&_tiles.at(i).first);
  }

  SDL_RenderCopy(&renderer, SDL_CreateTextureFromSurface(&renderer, canvas), NULL, NULL);

  SDL_FreeSurface(canvas);

}

void Map::update(){

}

bool Map::readMap(string filepath){
  ifstream fileReader;
  fileReader.open(filepath, ifstream::in);
  int x = 0, y = 0;
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
    x = 0;
    y++;
  }

  return true;

}
