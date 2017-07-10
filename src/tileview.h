#ifndef TILEVIEW_H
#define TILEVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>

#include "tilescene.h"

class TileView : public QGraphicsView
{
public:
    TileView();

    void wheelEvent(QWheelEvent* event);

    void mouseMoveEvent(QMouseEvent *event);


private:

    TileScene* scene;


    void loadTiles();


};

#endif // TILEVIEW_H
