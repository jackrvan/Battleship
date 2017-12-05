#include "player.hxx"
#include <iostream>
#include <cctype>
#include <algorithm>

using std::cout;
using std::endl;
using std::cerr;
using std::cin;

Ship& getType(char type, Player& p) {
    switch(type) {
        case 'c':
            return p.getCarrier();
        case 'b':
            return p.getBattleship();
        case 's':
            return p.getSub();
        case 'r':
            return p.getCruiser();
        case 'd':
            return p.getDestroyer();
        default:
            std::cerr << "Error with getting ship" << endl;
            return p.getCarrier(); //NOT SAFE FIND OUT WHAT WE SHOULD ACTUALLY RETURN
            
    }
}

void Player::setShip(int x, int y, int size, std::string type, bool horiz) {
    char temp = tolower(type[0]);
    //cout << "Type = " << type << endl;
    if(type == "Cruiser") temp = 'r';
    if(horiz) {
        for(int nx = x; nx < (x + size); ++nx) {
            board_[nx][y] = temp;
        }
    } else {
        for(int ny = y; ny < (y + size); ++ny) {
            board_[x][ny] = temp;
        }
    }
}

bool Player::attack(int x, int y) {
    //std::cout << "Attacking " << x << " " << y << std::endl;
    board_[x][y] = toupper(board_[x][y]); //Set to upper case to mark that it has been visited
    switch(board_[x][y]) {
        case 'C':
            cout << "c ";
            if(!carrier.hit()) --shipsLeft;
            break;
        case 'B':
            cout << "b "; 
            if(!battleship.hit()) --shipsLeft;
            break;
        case 'S':
            cout << "s";
            if(!sub.hit()) --shipsLeft;
            break;
        case 'R':
            cout << "r";
            if(!cruiser.hit()) --shipsLeft;
            break;
        case 'D':
            cout << "d";
            if(!destroyer.hit()) --shipsLeft;
            break;
        case 'F':
            return false;
        default:
            std::cout << "Something went wrong" << std::endl;
    }
    return true;
}

bool Player::alreadyAttacked(int x, int y) {
    return isupper(board_[x][y]);
}

void Player::printBoard() {
    for(int a = 0; a < 10; ++a) {
        for(int b = 0; b < 10; ++b) {
            cout << board_[b][a] << ' ';
        }
        cout << endl;
    }
}

void Player::printOppBoard() {
    for(int a = 0; a < 10; ++a) {
        for(int b = 0; b < 10; ++b) {
            cout << oppBoard[b][a] << ' ';
        }
        cout << endl;
    }
}

ui Player::getShipsLeft() { return shipsLeft; }

Carrier& Player::getCarrier() { return carrier; }
Battle& Player::getBattleship() { return battleship; }
Submarine& Player::getSub() { return sub; }
Cruiser& Player::getCruiser() { return cruiser; }
Destroyer& Player::getDestroyer() { return destroyer; }

void Player::setIsHuman(bool b) { isHuman = b; }

bool Player::overlap(int x, int y, int size, bool isHoriz) {
    if(isHoriz) {
        for(int nx = x; nx < (x + size); ++nx) {
            if(board_[nx][y] != 'f') return true;
        }
    } else {
        for(int ny = y; ny < (y + size); ++ny) {
            if(board_[x][ny] != 'f') return true;
        }
    }
    return false;
}