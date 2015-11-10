#include "Weapon.h"

using namespace std;

Weapon::Weapon(int ammo, int max_ammo, Projectile projectile)
{
  _ammo = ammo;
  _max_ammo = max_ammo;
  _projectile = projectile;
}

Weapon::Weapon(int ammo, int max_ammo)
{
  _ammo = ammo;
  _max_ammo = max_ammo;

  Projectile projectile(10,20,30);
  _projectile = projectile;

}


Weapon::Weapon()
{
  _ammo = 50;
  _max_ammo = 100;

  Projectile projectile(10,20,30);
  _projectile = projectile;
}



Weapon::~Weapon()
{

}

int Weapon::getAmmo()
{
  return _ammo;
}

int Weapon::getMaxAmmo()
{
  return _max_ammo;
}

Projectile Weapon::getProjectile()
{
  return _projectile;
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

