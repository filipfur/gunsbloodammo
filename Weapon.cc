#include "Weapon.h"

using namespace std;

Weapon::Weapon(int ammo, int max_ammo)
{
  _ammo = ammo;
  _max_ammo = max_ammo;
}

Weapon::Weapon()
{
  _ammo = 50;
  _max_ammo = 100;
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

