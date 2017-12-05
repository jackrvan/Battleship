#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>
#include <QtGui>
#include <QScreen>
#include <QList>

#include "box.hxx"
#include "dimensions.hxx"

class Board {
public:
	Board();
	void placeSquares(int, int);
	void drawColumn(int, int);
	void setBoxesAsUsed(int, int, int, bool);
	bool isBoxUsed(int, int);
	void setGreen(int, int);
	void setRed(int, int);

private:
	QList<Box*> boxes;
	int upperLeftX, upperLeftY;
};

#endif