#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPushButton>

#include "board.hxx"
#include "qtship.hxx"
#include "hud.hxx"
#include "computer.hxx"

#include <cstdlib>


class Battleship : public QGraphicsView {
    
    Q_OBJECT

public:
    // constructors
    Battleship();
    void drawHud();
    void drawShips();
    void drawBoard();

    void setCurrentShip(Qtship *);
    void placeShip(int, int);
    bool overlap(int, int, int);
    void takeTurn(int, int);
    void aiTurn();

    void endGame(bool);
    
    bool getLocked() { return locked; }

    QGraphicsScene *aScene;
    Board board1;
    Board board2;
    Qtship *currentShip;

private:
    Hud hud;
    Qtship *battle;
    Qtship *carrier;
    Qtship *sub;
    Qtship *destroyer;
    Qtship *cruiser;
    QPushButton *button;
    QPushButton *rotate;
    Player human; //Our human player
    Computer ai; //opponent
    bool locked;

private slots:
    void lockShips();
    void rotateShips();
};

#endif