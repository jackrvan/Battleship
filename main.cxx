#include <QApplication>
#include "battleship.hxx"
#include <iostream>
//MainWindow *w;
Battleship *b;

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	
	b = new Battleship();
	b->show();

	b->drawHud();
	//std::cout << "After hud" << std::endl;
	b->drawShips();
	//std::cout << "After ships()" << std::endl;
	b->drawBoard();
	//std::cout << "After board" << std::endl;

	return app.exec();
}