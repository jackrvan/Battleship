#ifndef QTSHIP_H
#define QTSHIP_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>
#include <QtGui>
#include <QApplication>

#include "dimensions.hxx"

class Qtship : public QObject, public QGraphicsItem {
public:
	Qtship() = delete;
	Qtship(int, std::string, int);

	QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    int getSize() { return size; }
    void setPlaced(bool b) { placed = b; }
    bool isPlaced() { return placed; }
    std::string getType() { return type; }
    bool isHoriz() { return horiz; }
    void rotate();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:
	int size;
	bool placed = false;
	std::string type; //What kind of ship is it
	bool horiz = true;
	int shipNo;
};

#endif