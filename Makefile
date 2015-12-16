#Makefile för GBA


#g++ main.cc Game.cc Menu.cc World.cc Character.cc Weapon.cc Projectile.cc Crosshair.cc Powerup.cc GUI.cc Player.cc Enemy.cc Map.cc -o gba -g -pedantic -Wall -Wextra -Wno-unused-parameter -std=c++11 -L/sw/gcc-/lib -static-libstdc++ -lSDL2_image -lSDL2_mixer -lSDL2_ttf -I/usr/include/SDL2 -D_REENTRANT -L/usr/lib/x86_64-linux-gnu -lSDL2 -Isrc -Isrc/layer

#g++ -g -pedantic -Wall -Wextra -Wno-unused-parameter -std=c++11 -L/sw/gcc-/lib -static-libstdc++ -lSDL2_image -lSDL2_mixer -lSDL2_ttf -I/usr/include/SDL2 -D_REENTRANT -L/usr/lib/x86_64-linux-gnu -lSDL2 -Isrc -Isrc/layer -o nygba main.cc Game.cc Menu.cc World.cc Character.cc Weapon.cc Projectile.cc Crosshair.cc Powerup.cc GUI.cc Player.cc Enemy.cc Map.cc


CCC	= g++
CCFLAGS += -g -pedantic -Wall -Wextra -Wno-unused-parameter -std=c++11
LDFLAGS += -L/sw/gcc-/lib -static-libstdc++ -lSDL2_image -lSDL2_mixer -lSDL2_ttf -I/usr/include/SDL2 -D_REENTRANT -L/usr/lib/x86_64-linux-gnu -lSDL2 -Isrc -Isrc/layer

nygba:  Menu.h World.h Character.h Weapon.h Projectile.h Crosshair.h Powerup.h GUI.h Player.h Enemy.h Map.h Game.cc Menu.cc World.cc Character.cc Weapon.cc Projectile.cc Crosshair.cc Powerup.cc GUI.cc Player.cc Enemy.cc Map.cc Game.cc Makefile main.cc
	$(CCC) main.cc Game.cc Menu.cc World.cc Character.cc Weapon.cc Projectile.cc Crosshair.cc Powerup.cc GUI.cc Player.cc Enemy.cc Map.cc -o nygba $(CCFLAGS) $(LDFLAGS)
	@echo "Kör programmet med kommandot ./nygba"


# Städa
clean: 
	@ \rm -f *.o *.gch core

# Storstäda
zap: clean
	@ \rm -rf nygba *~
