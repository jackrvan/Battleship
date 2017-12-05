#ifndef SHIP_HXX_
#define SHIP_HXX_

#include <string>

using ui = unsigned int;

class Ship {
    public:
        Ship() = delete;
        explicit Ship(ui holes) : numHoles(holes), holesLeft(holes), alive(true) { }
        virtual std::string get_name() const = 0; //All subclasses of Ship need to implement get_name
        bool hit();
        ui getHolesLeft() const { return holesLeft; }
        ui isAlive() { return alive; }

    private:
        ui numHoles;
        ui holesLeft;
        bool alive; //Is the ship still alive?        
};

class Carrier : public virtual Ship {
    public:
        Carrier() : Ship(5) { }
        std::string get_name() const { return "Carrier"; }
};

class Battle : public virtual Ship {
    public:
        Battle() : Ship(4) { }
        std::string get_name() const { return "Battleship"; }
};

class Submarine : public virtual Ship {
    public:
        Submarine() : Ship(3) { }
        std::string get_name() const { return "Submarine"; }
};

class Cruiser : public virtual Ship {
    public:
        Cruiser() : Ship(3) { }
        std::string get_name() const { return "Cruiser"; }
};

class Destroyer : public virtual Ship {
    public:
        Destroyer() : Ship(2) { }
        std::string get_name() const { return "Destroyer"; }
};

#endif
