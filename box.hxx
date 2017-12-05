#ifndef BOX_H
#define BOX_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QtGui>

#include "dimensions.hxx"

class Box : public QGraphicsRectItem {
public:
	Box();
	void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
	void dropEvent(QGraphicsSceneDragDropEvent *) override;
	void mousePressEvent(QGraphicsSceneMouseEvent *) override;
	void setUsed(bool b) { used = b; }
	bool isUsed() { return used; }
	void setGreen(bool b) { green = b; }
	void setRed(bool b) { red = b; }

private:
	bool used = false;
	bool green = false;
	bool red = false;
};

#endif