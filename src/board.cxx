#include "board.hxx"
#include "battleship.hxx"
#include <iostream>

//extern MainWindow *w;
extern Battleship *b;

Board::Board() { std::cout << "Board() " << std::endl; }

void Board::placeSquares(int x, int y) {
	//std::cout << "PLACE SQUARES" << std::endl;
	upperLeftX = x;
	upperLeftY = y;
	for(int a = 0; a < 10; ++a) {
		drawColumn(x + Dimensions::boxSize * a, y);
	}
}

void Board::drawColumn(int x, int y) {
	//std::cout << "draw column begin" << std::endl;

	for(int a = 0; a < 10; ++a) {
		//We create 10 boxes for each column
		Box *box = new Box();

		//std::cout << "Setting position " << x << ", " << y + Dimensions::boxSize * a;
		box->setPos(x, y + Dimensions::boxSize * a);
		boxes.append(box);
		b->aScene->addItem(box);
	}
	//std::cout << "END OF drawColumn()" << std::endl;
}

void Board::setBoxesAsUsed(int xStart, int yStart, int size, bool isHoriz) {
	for(int a = 0; a < size && isHoriz; ++a) {
		boxes.at(yStart * 10 + xStart + a)->setUsed(true);
	}
	for(int a = 0; a < size && !isHoriz; ++a) {
		boxes.at((yStart+a) * 10 + xStart);
	}
}

bool Board::isBoxUsed(int x, int y) {
	return boxes.at(y * 10 + x)->isUsed();
}

void Board::setGreen(int x, int y) {
	//std::cout << "Setting " << x << ", " << y << " green" << std::endl;
	boxes.at(x * 10 + y)->setGreen(true); //Set the current box as green
	boxes.at(x * 10 + y)->setRed(false);
	Box *temp = new Box();
	temp->setPos(upperLeftX + x * Dimensions::boxSize, upperLeftY + y * Dimensions::boxSize);
	temp->setGreen(true);
	b->aScene->addItem(temp);
	//std::cout << "After adding temp" << std::endl;
}

void Board::setRed(int x, int y) {
	boxes.at(x * 10 + y)->setRed(true); //Set the current box as green
	boxes.at(x * 10 + y)->setGreen(false);
	Box *temp = new Box();
	temp->setPos(upperLeftX + x * Dimensions::boxSize, upperLeftY + y * Dimensions::boxSize);
	temp->setRed(true);
	b->aScene->addItem(temp);
}
