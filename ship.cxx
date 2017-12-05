#include "ship.hxx"
#include <cmath>
#include <iostream>

bool Ship::hit() {
    --holesLeft;
    std::cout << get_name() << " has holes left = " << holesLeft << std::endl;
    if(holesLeft == 0) {
        alive = false;
    }
    return alive; //If true our ship still has at least one hole left
}
