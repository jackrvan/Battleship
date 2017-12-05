#include "box.hxx"
#include <iostream>
#include "battleship.hxx"
using namespace std;

extern Battleship *b;

Box::Box() {
	setAcceptDrops(true);
	QRectF aSquare = QRectF(QPointF(0,0), QPointF(Dimensions::boxSize, Dimensions::boxSize));
	setRect(aSquare);
}

void Box::paint(QPainter * painter, const QStyleOptionGraphicsItem * option = 0, QWidget * widget = 0) {
	Q_UNUSED(option);
	Q_UNUSED(widget);
	//std::cout << "BOX PAINT" << std::endl;
	if(green) painter->setBrush(Qt::green);
	else if(red) painter->setBrush(Qt::red);	
	painter->drawRect(0, 0, Dimensions::boxSize, Dimensions::boxSize);
}

void Box::dropEvent(QGraphicsSceneDragDropEvent *event) {
	Q_UNUSED(event);
	int x = (this->pos().rx() - 400)/Dimensions::boxSize;
	int y = (this->pos().ry() + 200)/Dimensions::boxSize - 10; //No clue why we need the -10 at the end will figure out later
	//std::cout << "Dropped in square " << x << ' '  << y << std::endl;
	b->placeShip(x, y);
}

void Box::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	Q_UNUSED(event);
	if(!b->getLocked()) {
		std::cout << "Please place and lock ships before you start your turn" << std::endl;
		return;
	}
	int x = (this->pos().rx() - 400)/Dimensions::boxSize;
	int y = (this->pos().ry() + 175)/Dimensions::boxSize + 1;
	//std::cout << "Clicked on square " << x << ' ' << y << std::endl;
	if((x >= 0) && (x < 10) && (y >= 0) && (y < 10)) b->takeTurn(x, y);
	else std::cout << "Please click on a square on board 1 to try and hit your opponent ships" << std::endl;
}