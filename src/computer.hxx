#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.hxx"

class Computer : public Player {
public:
	void place_ships();
	void place_a_ship(const Ship&);
};

#endif