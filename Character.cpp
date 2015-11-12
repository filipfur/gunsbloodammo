#include "Character.h"



Character::Character(int x, int y, int width, int height, int hp, Weapon weapon){
  _x = x;
  _y = y;
  _width = width;
  _height = height;
  _hp = hp;
  _hpMax = hp;
  _weapon = weapon;

  _pos.x = x;
  _pos.y = y;
  _pos.w = width;
  _pos.h = height;

  _direction = 'W';
  _dx = _dy = 0;
}

Character::Character(int x, int y, int width, int height, Weapon weapon){
  _x = x;
  _y = y;
  _width = width;
  _height = height;
  _hp = 100;
  _hpMax = 100;
  _weapon = weapon;

  _pos.x = x;
  _pos.y = y;
  _pos.w = width;
  _pos.h = height;

  _direction = 'W';
  _dx = _dy = 0;
}

Character::Character(int x, int y, int width, int height){
  _x = x;
  _y = y;
  _width = width;
  _height = height;
  _hp = 100;
  _hpMax = 100;
  Weapon weapon(100,100);
  _weapon = weapon;

  _pos.x = x;
  _pos.y = y;
  _pos.w = width;
  _pos.h = height;

  _direction = 'W';
  _dx = _dy = 0;
}

Character::Character(){
  _x = 0;
  _y = 0;
  _width = 0;
  _height = 0;
  _hp = 100;
  _hpMax = 100;
  Weapon weapon(100,100);
  _weapon = weapon;

  _pos.x = 0;
  _pos.y = 0;
  _pos.w = 0;
  _pos.h = 0;

  _direction = 'W';
  _dx = _dy = 0;
}



Character::~Character(){

}

int Character::getX()
{
  return _x;
}

int Character::getY()
{
  return _y;
}

int Character::getWidth()
{
  return _width;
}

int Character::getHeight()
{
  return _height;
}

int Character::getHp()
{
  return _hp;
}

Weapon Character::getWeapon()
{
  return _weapon;
}

int Character::getAmmo()
{
  return _weapon.getAmmo();
}

int Character::getMaxAmmo()
{
  return _weapon.getMaxAmmo();
}

void Character::setWeapon(Weapon weapon)
{
  _weapon = weapon;
}

void Character::decHp(int damage)
{
  _hp = _hp - damage;
}

void Character::incHp(int hp_gain)
{
  _hp += hp_gain;
}

void Character::decAmmo()
{
  _weapon.decAmmo();
}
void Character::incAmmo(int ammo_gain)
{
  _weapon.incAmmo(ammo_gain);
}



//returnerar en projektil och sänker antal skott.
//Anroparen får se till att det finns skott kvar.
Projectile Character::shoot()
{
  _weapon.decAmmo();
  return _weapon.getProjectile();
}

void Character::draw(SDL_Renderer &renderer, int x, int y){
  
  SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(&renderer, const_cast<SDL_Rect*>(&_pos));
  
}

void Character::update(){

  _x += _dx;
  _y += _dy;

  _pos.x = _x;
  _pos.y = _y;

}

int Character::input(std::map<char,bool> &keys){

  if(keys['W']){
    _direction = 'W';
    _dy = -MOVESPEED;
  }
  else if(keys['S']){
    _direction = 'S';
    _dy = MOVESPEED;
  }
  else{
    _dy = 0;
  }
  if(keys['A']){
    _direction = 'A';
    _dx = -MOVESPEED;
  }
  else if(keys['D']){
    _direction = 'D';
    _dx = MOVESPEED;
  }
  else{
    _dx = 0;
  }

  return 2;
}
