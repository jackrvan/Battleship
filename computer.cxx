#include "computer.hxx"
#include <cstdlib>
#include <ctime>

void Computer::place_ships() {
	place_a_ship(carrier);
	place_a_ship(battleship);
	place_a_ship(cruiser);
	place_a_ship(sub);
	place_a_ship(destroyer);
}

void Computer::place_a_ship(const Ship &aShip) {
	srand(static_cast<unsigned>(time(0)));
	int isHorizontal = rand() % 2; //Will be either 0 or 1
	int size = aShip.getHolesLeft();
	if(isHorizontal) {
		int x = rand() % (11-size);
		int y = rand() % 10;
		while(overlap(x, y, size, true)) {
			x = rand() % (11-size);
			y = rand() % 10;
		}
		setShip(x, y, size, aShip.get_name(), true);
	} else {
		int x = rand() % 10;
		int y = rand() % (11-size);
		while(overlap(x, y, size, false)) {
			x = rand() % 10;
			y = rand() % (11-size);
		}
		setShip(x, y, size, aShip.get_name(), false);
	}
}