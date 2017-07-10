#ifndef TILESCENE_H
#define TILESCENE_H

#include <QGraphicsScene>
#include <QGraphicsColorizeEffect>
#include <QGraphicsSceneMouseEvent>

class TileScene : public QGraphicsScene
{
public:
    TileScene();
    ~TileScene();

    void mousePressEvent(QGraphicsSceneMouseEvent* pMouseEvent);

private:
    QGraphicsColorizeEffect* selectedEffect;


};

#endif // TILESCENE_H
