#include "hud.hxx"
#include <iostream>

QRectF Hud::boundingRect() const {
	return QRectF(0, 0, Dimensions::hudWidth, Dimensions::hudHeight);
}

void Hud::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * widget) {
	Q_UNUSED(widget);
	//std::cout << "Drawing HUD at " << pos().x() << " " << pos().y() << std::endl;
	QRectF rect = boundingRect();
	painter->setPen(QPen(Qt::red, 3));
	painter->drawRoundedRect(rect, 80.0, 20.0);
}
