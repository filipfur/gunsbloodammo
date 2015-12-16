#include "Character.h"

int Character::getX()
{
  return _x;
}

int Character::getY()
{
  return _y;
}

void Character::setX(int x){
  _x = x;
  _pos.x = x;
}

void Character::setY(int y){
  _y = y;
  _pos.y = y;
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

int Character:: getMaxHp(){
  return _hpMax;
}

double Character::getSpeed(){
  return _movespeed;
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

void Character::setSpeed(double speed){
  _movespeed = speed;
}

void Character::setHP(int i){
  _hp = i;
}

void Character::decHp(int damage)
{
  _hp -= damage;
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

void Character:: setAngle(double angle){
  _angle = angle;
}

void Character::setMoving(bool b) {
  _move = b;
}

SDL_Rect Character::getRect(){
  return _rect;
}

//returnerar en projektil och sänker antal skott.
//Anroparen får se till att det finns skott kvar.
Projectile* Character::shoot(double rad, bool friendly){
  if(_weapon.isReady()){
	decAmmo();
    Projectile* p = _weapon.getProjectile();
	p->setDir(rad);
	p->setPos(_x+_rect.w/2, _y+_rect.h/2);
	if(friendly)
		p->setFriendly();
    return p;
  }
  return nullptr;
}

void Character::draw(SDL_Renderer &renderer, int camx, int camy){
  const SDL_Rect rect = {_pos.x-camx, _pos.y-camy, _pos.w, _pos.h};
  if (_texture == NULL){
	  _texture = SDL_CreateTextureFromSurface(&renderer, _surface);
  }
  const SDL_Point mid = {_width/2, _height/2};
  SDL_RenderCopyEx(&renderer, _texture, NULL, &rect,
		   _angle, &mid, SDL_FLIP_NONE);
}

void Character::update() {
  _weapon.update();
  if (_move) {
    _x += _dx*_movespeed;
    _y += _dy*_movespeed;

    _pos.x = _x;
    _pos.y = _y;
    _rect.x = _x;
    _rect.y = _y;
  }

}
