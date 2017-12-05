#include "qtship.hxx"
#include "battleship.hxx"
#include <iostream>

extern Battleship *b;

Qtship::Qtship(int s, std::string name, int num) {
	size = s; //Size of ship
    type = name;
    shipNo = num;
	setCursor(Qt::OpenHandCursor); //When over a qtship our cursor looks like an open hand
	setAcceptDrops(true);
	setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF Qtship::boundingRect() const {
	if(!horiz) {
        return QRectF(0, 0, Dimensions::boxSize, Dimensions::boxSize * size); //Vertical ship
    }
    return QRectF(0, 0, Dimensions::boxSize * size, Dimensions::boxSize); //Horizontal ship
}

void Qtship::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *widget) {
	Q_UNUSED(widget);
    //std::cout << "Qt ship paint()" << std::endl;
	QRectF rect = boundingRect();
	painter->setPen(QPen(Qt::black, 3));
	painter->drawRect(rect);
}

void Qtship::mousePressEvent(QGraphicsSceneMouseEvent *) {
    std::cout << "Qt ship mousePressEvent" << std::endl;
    if(b->getLocked()) {
        //If our ships are locked we dont want to do anything
        return;
    }
	setCursor(Qt::ClosedHandCursor);
    b->setCurrentShip(this);
}

void Qtship::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(b->getLocked()) return;

    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance()) {
        return;
    }

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    QPixmap pixmap(Dimensions::boxSize * size, Dimensions::boxSize);
    if(!horiz) pixmap = pixmap.scaled(Dimensions::boxSize, Dimensions::boxSize * size);
    
    pixmap.fill(Qt::gray);

    QPainter painter(&pixmap);
    paint(&painter, 0, 0);
    painter.end();

    pixmap.setMask(pixmap.createHeuristicMask());

    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(15, 20));

    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

void Qtship::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
    if(b->getLocked()) return;
    setCursor(Qt::OpenHandCursor);
}

void Qtship::rotate() {
    horiz = !horiz;
    if(horiz) {
        setPos(pos().x()-(50 * shipNo), pos().y() + (80*shipNo));
    } else {
        setPos(pos().x()+(50*shipNo), pos().y() - (80*shipNo));
    }
}