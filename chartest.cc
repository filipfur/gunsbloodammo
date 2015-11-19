#include <iostream>
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Powerup.h"
using namespace std;

int main()
{

  cout << "Creating a character with 5 parameters" << endl << endl;
  Weapon weapon(25,45);
  Player character(30, 20, 40, 50, weapon);
  cout << "Xpos =  " << character.getX() << endl;
  cout << "Ypos = " << character.getY() << endl;
  cout << "Width = " << character.getWidth() << endl;
  cout << "Height = " << character.getHeight() << endl;
  
  cout << "Ammo = " << character.getAmmo() << endl;
  cout << "Max ammo = " << character.getMaxAmmo() << endl;

  cout << "Creating a character with 4 parameters" << endl << endl;
  Enemy character2(1, 2, 3, 4);
  cout << "Xpos =  " << character2.getX() << endl;
  cout << "Ypos = " << character2.getY() << endl;
  cout << "Width = " << character2.getWidth() << endl;
  cout << "Height = " << character2.getHeight() << endl;
  
  cout << "Ammo = " << character2.getAmmo() << endl;
  cout << "Max ammo = " << character2.getMaxAmmo() << endl;


  for (int i{0}; i < 10; i++){
    cout << "Shoot!" << endl;
    character2.shoot();
    cout << "Ammo = " << character2.getAmmo() << endl;
  }

  for (int i{0}; i < 10; i++){
    cout << "Player is hit!" << endl;
    character2.decHp(4);
    cout << "Hp = " << character2.getHp() << endl;
  }



  cout << "Creating a powerup" << endl;
  Powerup p(15, 15, 0, 10);



  cout << "x = " << p.getX() << endl
       << "y = " << p.getY() << endl;
  if (p.getType() == 0)
    {
      cout << "Type = " << "Ammo" << endl;
    }
  else if(p.getType() == 2)
    {
      cout << "Type = " << "health" << endl;
    }
  else
    {
      cout << "Type = " << "Weapon" << endl;
    }
  cout << "value = " << p.getValue() << endl;


  cout << "create projectile" << endl;

  Projectile projectile(50,50,20);

  cout << "Set direction = 0,7" << endl;

  projectile.setDir(0.7);

  cout << "Direction = " << projectile.getDir() << endl;

  return 0;
}
