#include "World.h"

World::World(int x, int y, vector<pair<int, int>> enemies,
	     const char* mapFile, const char* tileFile) {
  _map = new Map(mapFile, tileFile, 64);

  _player = new Player(x, y);
  vector<const char*> enemyTypes = { "enemy1.png", "enemy2.png", "enemy3.png" };
  vector<const char*> gunTypes = { "pistol.png", "m4.png", "shotgun.png" };

  for (unsigned int i{ 0 }; i < enemies.size(); ++i){
    _enemies.push_back(new Enemy(enemies.at(i).first, enemies.at(i).second,
				 enemyTypes.at(i%enemyTypes.size()),
				 gunTypes.at(i%gunTypes.size())));
  }

  _powerups.push_back(new Powerup(512-64, 512, 0, 20));
  
  std::ifstream file("config.txt");
  int r = 0, g = 0, b = 0;
  if(file.is_open()){
    file>>r>>g>>b;
    file.close();
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
  _enemies.clear();
  _projectiles.clear();

}

void World::draw(SDL_Renderer &renderer, const int currtime){
  SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
  SDL_RenderClear(&renderer);

  _map->draw(renderer, _cam.x, _cam.y);
  
  _player->draw(renderer, _cam.x, _cam.y);
  for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
	  (*it)->draw(renderer, _cam.x, _cam.y);
  }
  for(auto it = _projectiles.begin(); it != _projectiles.end(); ++it){
    (*it)->draw(renderer, _cam.x, _cam.y);
  }
  for(auto it = _powerups.begin(); it != _powerups.end(); ++it){
    (*it)->draw(renderer, _cam.x, _cam.y);
  }
  _crosshair->draw(renderer);
  _GUI->draw(renderer, currtime);
}

void World::update(){

_cam.x = _player->getX() - 640/2;

  if(_cam.x < 0)
    _cam.x = 0;
  else if(_cam.x > _map->getWidth()*_map->getTilesize()-640)
    _cam.x = _map->getWidth()*_map->getTilesize()-640;
    
_cam.y = _player->getY() - 480/2;
  if(_cam.y < 0)
    _cam.y = 0;
  else if(_cam.y > _map->getHeight()*_map->getTilesize()-480)
    _cam.y = _map->getHeight()*_map->getTilesize()-480;

  int x = _player->getX();
  int y = _player->getY();
  
  _player->update();

  if(_map->checkCollision(_player->getRect())){
    _player->setX(x);
    _player->setY(y);
  }

  for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
	  x = (*it)->getX();
	  y = (*it)->getY();
	  if (sqrt((x - _player->getX())*(x - _player->getX()) +
		   (y - _player->getY())*(y - _player->getY())) <= 200) {

	    (*it)->setDir(-atan2((x - _player->getX()),
				 (y - _player->getY())) - M_PI / 2 );
	    Projectile* shell;
	    if ((shell = (*it)->shoot(-atan2((x - _player->getX()),
					     (y - _player->getY())) -
				      M_PI / 2)) != nullptr) {
	      _projectiles.push_back(shell);
	    }
	    (*it)->setMoving(false);
	  }
	  else {
	    (*it)->setMoving(true);
	  }
	  (*it)->update();
	  if (_map->checkCollision((*it)->getRect())) {
	    (*it)->setX(x);
	    (*it)->setY(y);
	    (*it)->newDir();
	  }
  }
  
  bool deleted = false;
  for(auto it = _projectiles.begin(); it != _projectiles.end(); ++it){
    (*it)->update();
    if(_map->checkCollision((*it)->getRect())){
      deleted = true;
    }
    for (auto it2 = _enemies.begin(); it2 != _enemies.end(); ++it2) {
      const SDL_Rect rect1 = (*it)->getRect();
      const SDL_Rect rect2 = (*it2)->getRect();
      if (SDL_HasIntersection(&rect1, &rect2) && (*it)->isFriendly()) {
	deleted = true;
	(*it2)->decHp(40);
      }
    }
    const SDL_Rect rect1 = (*it)->getRect();
    const SDL_Rect rect2 = _player->getRect();
    if (SDL_HasIntersection(&rect1, &rect2) && !(*it)->isFriendly()) {
      deleted = true;
      _player->decHp(8);
    }
    if (deleted == true) {
      _projectiles.erase(it);
      break;
    }
    
  }
  
  for(auto it = _powerups.begin(); it != _powerups.end(); ++it){
    const SDL_Rect rect1 = (*it)->getRect();
    const SDL_Rect rect2 = _player->getRect();
    if(SDL_HasIntersection(&rect1, &rect2)){
      if((*it)->getType() == 0)
	_player->incAmmo((*it)->getValue());
      _powerups.erase(it);
      break;
    }
  }
  
  _crosshair->update();
  _GUI->update();
}

Player World::getPlayer(){
  return _player;
}

void World::setPlayer(Player player){
  _player->setWeapon(player.getWeapon());
  _player->setHP(player.getHp());
}

int World::input(std::map<char,bool> &keys, int mx, int my, bool mr, bool ml){

  if(_player->getHp() <= 0){
    return 3; //Game Over
  }
  for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
	  if ((*it)->getHp() <= 0) {
		  _enemies.erase(it);
		  break;
	  }
  }

  if(_enemies.empty()){
    return 4; //level cleared (next level/game clear)
  }
  

  _player->setAngle(atan2((_player->getY()-_cam.y-my),
			  (_player->getX()-_cam.x-mx))*180/M_PI + 180);
  
  _player->input(keys, mx, my, mr, ml);
  
  _crosshair->input(mx, my);

  if(keys[SDLK_ESCAPE]){
    return 0;
  }
  
  if(ml && _player->getAmmo() > 0){
    Projectile* shell;
    if((shell = _player->shoot(-atan2((_player->getX() - _cam.x - mx),
				      (_player->getY() - _cam.y - my)) -
			       M_PI / 2, true)) != nullptr){
      _projectiles.push_back(shell);
    }
    ml = false;
  }

  return 1;
}
