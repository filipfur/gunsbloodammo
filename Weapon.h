#ifndef WEAPON_H
#define WEAPON_H
//#include "Weapon.cc";
using namespace std;

class Weapon
{
 public:
  Weapon(int ammo, int max_ammo);

  Weapon();

  ~Weapon();

  int getAmmo();

  int getMaxAmmo();

  void decAmmo();
  void incAmmo(int x);


 private:

  int _ammo;
  int _max_ammo;
};



#endif
