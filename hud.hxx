#ifndef HUD_H
#define HUD_H

#include <QObject>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QPointF>
#include <QLinearGradient>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QKeyEvent>

#include "dimensions.hxx"

class Hud : public QObject, public QGraphicsItem {
public:
	Hud() { }
	QRectF boundingRect() const;
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};

#endif