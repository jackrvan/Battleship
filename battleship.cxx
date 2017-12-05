#include "battleship.hxx"
#include <iostream>

Battleship::Battleship() {
	resize(1000, 1000); //Size of window
	
	aScene = new QGraphicsScene();
	aScene->setSceneRect(0, 0, Dimensions::sceneWidth, Dimensions::sceneHeight);
	setScene(aScene);
	currentShip = NULL;

	button = new QPushButton("Lock Ships", this);
	connect(button, SIGNAL (released()), this, SLOT (lockShips()));
	//button->move(size().width()-750, size().height()-200);
	button->move(175, 400);

	rotate = new QPushButton("Rotate Ships", this);
	connect(rotate, SIGNAL(released()), this, SLOT(rotateShips()));
	rotate->move(275, 400);
	locked = false;

	human.setIsHuman(true);
	ai.setIsHuman(false);
}

void Battleship::drawBoard() {
	//std::cout << "drawBoard()" << std::endl;
	board1.placeSquares(400, 175);
	board2.placeSquares(400, -200);
}

void Battleship::drawHud() {
	hud.setPos(0, 150);
	aScene->addItem(&hud);
}

void Battleship::drawShips() {
	carrier = new Qtship(5, "carrier", 0);
	battle = new Qtship(4, "battleship", 1);
	sub = new Qtship(3, "sub", 2);
	cruiser = new Qtship(3, "cruiser", 3);
	destroyer = new Qtship(2, "destroyer", 4);

	carrier->setPos(25, Dimensions::margin + 180);
	battle->setPos(25, Dimensions::margin + 260);
	sub->setPos(25, Dimensions::margin + 340);
	cruiser->setPos(25, Dimensions::margin + 420);
	destroyer->setPos(25, Dimensions::margin + 500);

	aScene->addItem(carrier);
	aScene->addItem(battle);
	aScene->addItem(sub);
	aScene->addItem(cruiser);
	aScene->addItem(destroyer);

	ai.place_ships();

}

void Battleship::setCurrentShip(Qtship *ship) {
	currentShip = ship;
} 

bool Battleship::overlap(int x, int y, int size) {
	//Test if the ship we are trying to place is on top of another ship
	if(currentShip->isHoriz()) {
		for(int nx = x; nx < (x + size); ++nx) {
			if(board2.isBoxUsed(nx, y)) return true;
		}
	} else {
		for(int ny = y; ny < (y + size); ++ny) {
			if(board2.isBoxUsed(x, ny)) return true;
		}
	}
	return false;
}

void Battleship::placeShip(int x, int y) {
	std::cout << "x = " << x << " y = " << y << std::endl;
	if(currentShip) {
		if((x + currentShip->getSize() > 10 && currentShip->isHoriz()) || (y + currentShip->getSize() > 10 && !currentShip->isHoriz())) {
			std::cout << "Cannot place ship here out of bounds" << std::endl;
			currentShip = NULL;
		} else if((x < 0) || (y < 0)) {
			std::cout << "Wrong board please place ships on lower board" << std::endl;
			currentShip = NULL;
		} else if(overlap(x, y, currentShip->getSize())) {
			std::cout << "Ship already in this spot" << std::endl;
			currentShip = NULL;
		} else {
			//Set the ship
			currentShip->setPos(QPointF(400 + Dimensions::boxSize*x, 175 + Dimensions::boxSize * y)); //Set position of ship
			currentShip->setPlaced(true);
			//std::cout << "We are placing a ship with size " << currentShip->getSize() << " at " << x << ',' << y << std::endl;
			board2.setBoxesAsUsed(x, y, currentShip->getSize(), currentShip->isHoriz());
			human.setShip(x, y, currentShip->getSize(), currentShip->getType(), currentShip->isHoriz()); //(x, y, sizeOfShip, typeOfShip, IsItHorizontal)
			currentShip = NULL;
		}
	} else {
		//This should never happen
		std::cerr << "Current ship is null somehow" << std::endl;
	}
}

void Battleship::lockShips() {
	if(carrier->isPlaced() && battle->isPlaced() && sub->isPlaced() && cruiser->isPlaced() && destroyer->isPlaced()) { //Ensure all ships are on the board
		std::cout << "Locking ships you can no longer move them\n" <<
						"Please click on a square in the first board to try and hit your opponent" << std::endl;
		locked = true;
	} else {
		std::cout << "Not all ships are placed cannot lock" << std::endl;
	}
}

void Battleship::takeTurn(int x, int y) {
	//ai.printBoard();
	if(ai.alreadyAttacked(x,y)) {
		std::cout << "You already guessed this spot try again" << std::endl;
		return;
	}
	if(ai.attack(x, y)) { //Attacking ai true = hit
		board2.setGreen(x, y); //Set square to green to mark as hit
		//std::cout << "HIT!" << std::endl;
		cout << "ships left = " << ai.getShipsLeft() << endl;
		if(ai.getShipsLeft() == 0) {
			endGame(true);
		}
	} else {
		board2.setRed(x, y);
		//std::cout << "MISS" << std::endl;
	}
	aiTurn();
}

void Battleship::aiTurn() {
	//TODO Make AI strategically pick there next turn instead of randomly picking

	int x = rand() % 10; //integer in range 0-10
	int y = rand() % 10;
	while(human.alreadyAttacked(x, y)) {
		//Theoretically could be infinite loop if it keeps guessing numbers that are already taken
		x = rand() % 10; //integer in inclusive range 0-9
		y = rand() % 10;
	}

	if(human.attack(x, y)) {
		board1.setGreen(x, y);
		if(human.getShipsLeft() == 0) {
			endGame(false);
		}
		//std::cout << "COMPUTER HIT YOU" << std::endl;
	} else {
		board1.setRed(x, y);
		//std::cout << "COMPUTER MISSED" << std::endl;
	}
}

void Battleship::endGame(bool humanWon) {
	if(humanWon) {
		//board1.placeSquares(400, 175);
		board2.placeSquares(400, -200);
		std::cout << "Congratulations you won!!" << std::endl;
	} else {
		std::cout << "You lost better luck next time" << std::endl;
	}
	for(int a = 0; a < aScene->items().size(); ++a) {
		aScene->items()[a]->setEnabled(false);
	}
}

void Battleship::rotateShips() {
	if(!(carrier->isPlaced())) {
		aScene->removeItem(carrier);
		carrier->rotate();
		aScene->addItem(carrier);
	}
	if(!(battle->isPlaced())) {
		aScene->removeItem(battle);
		battle->rotate();
		aScene->addItem(battle);
	}
	if(!(sub->isPlaced())) {
		aScene->removeItem(sub);
		sub->rotate();
		aScene->addItem(sub);
	}
	if(!(destroyer->isPlaced())) {
		aScene->removeItem(destroyer);
		destroyer->rotate();
		aScene->addItem(destroyer);
	}
	if(!(cruiser->isPlaced())) {
		aScene->removeItem(cruiser);
		cruiser->rotate();
		aScene->addItem(cruiser);
	}
}