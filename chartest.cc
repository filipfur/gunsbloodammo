#include <iostream>
#include "Character.h"
#include "Weapon.h"
using namespace std;

int main()
{

  cout << "Creating a character with 5 parameters" << endl << endl;
  Weapon weapon(25,45);
  Character character(30, 20, 40, 50, weapon);
  cout << "Xpos =  " << character.getX() << endl;
  cout << "Ypos = " << character.getY() << endl;
  cout << "Width = " << character.getWidth() << endl;
  cout << "Height = " << character.getHeight() << endl;
  
  cout << "Ammo = " << character.getAmmo() << endl;
  cout << "Max ammo = " << character.getMaxAmmo() << endl;

  cout << "Creating a character with 4 parameters" << endl << endl;
  Character character2(1, 2, 3, 4);
  cout << "Xpos =  " << character2.getX() << endl;
  cout << "Ypos = " << character2.getY() << endl;
  cout << "Width = " << character2.getWidth() << endl;
  cout << "Height = " << character2.getHeight() << endl;
  
  cout << "Ammo = " << character2.getAmmo() << endl;
  cout << "Max ammo = " << character2.getMaxAmmo() << endl;

  return 0;
}
