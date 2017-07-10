#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "mainview.h"

class MainScene : public QGraphicsScene
{
public:
    MainScene();

    void mousePressEvent(QGraphicsSceneMouseEvent* pMouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* pMouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* pMouseEvent);
    void undo();
    void redo();
private:
    bool clicking;

    QGraphicsPixmapItem* addTile(QPointF at);
    QGraphicsPixmapItem* removeTile(QPointF at);
};

#endif // MAINSCENE_H
