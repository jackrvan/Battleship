#ifndef PLAYER_HXX_
#define PLAYER_HXX_

#include "ship.hxx"
#include <iostream>

using std::cout;
using std::endl;

class Player {
    public:
        Player() : shipsLeft(5) { clearBoard(); }
        void clearBoard() {
            for(int a = 0; a < 10; ++a) {
                for(int b = 0; b < 10; ++b) {
                    board_[a][b] = 'f';
                    oppBoard[a][b] = 'X';
                }
            }
        }
        void setShip(int, int, int, std::string, bool);
        //void attack(Player&);
        bool attack(int, int);
        bool alreadyAttacked(int, int);
        void printBoard();
        void printOppBoard();
        void makeUpper(ui x, ui y);
        void setIsHuman(bool);
        bool overlap(int, int, int, bool);

        ui getShipsLeft();
        Carrier& getCarrier();
        Battle& getBattleship();
        Submarine& getSub();
        Cruiser& getCruiser();
        Destroyer& getDestroyer();

    private:
        unsigned short shipsLeft; 
        char board_[10][10];
        char oppBoard[10][10];
    protected:
        Carrier carrier;
        Battle battleship;
        Submarine sub;
        Cruiser cruiser;
        Destroyer destroyer;
        bool isHuman;
};

#endif
