#ifndef ACTION_H
#define ACTION_H

#include <QGraphicsPixmapItem>
#include <QPointF>

class Action
{
public:
    Action(QGraphicsPixmapItem* _pitem, const QPointF& _position, int _zvalue);

    QGraphicsPixmapItem* pitem;
    QPointF position;
    int zvalue;
};

#endif // ACTION_H
