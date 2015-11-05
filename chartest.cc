#include <iostream>
#include "Character.h"
#include "Weapon.h"
using namespace std;

int main()
{
  Weapon weapon(25,45);
  Character character(30, 20, 40, 50, weapon);
  cout << "Xpos =  " << character.getX() << endl;
  cout << "Ypos = " << character.getY() << endl;
  cout << "Width = " << character.getWidth() << endl;
  cout << "Height = " << character.getHeight() << endl;
  
  cout << "Ammo = " << character.getWeapon().getAmmo() << endl;
  cout << "Max ammo = " << character.getWeapon().getMaxAmmo() << endl;


  return 0;
}
