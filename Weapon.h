#include "Projectile.h"
#include <chrono>
#ifndef WEAPON_H
#define WEAPON_H
using namespace std::chrono;

class Weapon
{
 public:

  Weapon(int ammo, int max_ammo, Projectile* projectile);

  Weapon(int ammo, int max_ammo, const char*, const char*);
  Weapon() {}

  ~Weapon();

  void update();

  SDL_Surface* getIcon() {
	  return _icon;
  }

  int getAmmo();
  int getMaxAmmo();
  Projectile* getProjectile();

  void decAmmo();
  void incAmmo(int x);

  bool isReady(){
    return _ready;
  }
  SDL_Surface* getSurface();


 private:

  int _ammo;
  int _max_ammo;
  int _delay = 250;
  Projectile* _projectile;
  bool _ready;
  high_resolution_clock::time_point _timer;
  SDL_Surface* _surface, * _icon;
};



#endif
