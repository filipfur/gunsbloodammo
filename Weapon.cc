#include "Weapon.h"

using namespace std;

Weapon::Weapon(int ammo, int max_ammo, Projectile* projectile)
{
  _ammo = ammo;
  _max_ammo = max_ammo;
  _projectile = projectile;
  _timer = high_resolution_clock::now();
}

Weapon::Weapon(int ammo, int max_ammo, const char* filepath,
	       const char* filepath2)
{
  _ammo = ammo;
  _max_ammo = max_ammo;
  _timer = high_resolution_clock::now();
  _projectile = new Projectile(10,20,30);
  _surface = IMG_Load(filepath);
  _icon = IMG_Load(filepath2);

}



Weapon::~Weapon()
{

}

void Weapon::update(){
  _ready = duration_cast<duration<double>>(high_resolution_clock::now() -
					   _timer).count() * 1000 >= _delay;
}

SDL_Surface* Weapon::getIcon() {
  return _icon;
}

int Weapon::getAmmo()
{
  return _ammo;
}

SDL_Surface* Weapon::getSurface() {
	return _surface;
}

int Weapon::getMaxAmmo()
{
  return _max_ammo;
}

Projectile* Weapon::getProjectile()
{
  _timer = high_resolution_clock::now();
  _ready = duration_cast<duration<double>>(high_resolution_clock::now() -
					   _timer).count() * 1000 >= _delay;
  return new Projectile(10,20,30);
}


void Weapon::decAmmo()
{
  if(_ammo > 0)
    {
      _ammo = _ammo - 1;
    }
}

void Weapon::incAmmo(int x)
{
  _ammo = _ammo + x;
  if (_ammo > _max_ammo)
    {
      _ammo = _max_ammo;
    }
}

bool Weapon::isReady(){
  return _ready;
}
