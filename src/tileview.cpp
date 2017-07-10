#include "tileview.h"
#include "contexte.h"

#include <QtMath>
#include <QGraphicsPixmapItem>


#include <QPointF>
#include <QScrollBar>

TileView::TileView()
    : QGraphicsView()
{
    this->scene = new TileScene();
    this->setScene(scene);

    loadTiles();

}

void TileView::wheelEvent(QWheelEvent *event)
{
    const QPointF p0scene = mapToScene(event->pos());
    qreal factor = (std::pow(1.2, event->delta()/240.0));
    scale(factor,factor);

    const QPointF p1mouse = mapFromScene(p0scene);
    const QPointF move = p1mouse - event->pos();

    horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
    verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());

}

void TileView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if(event->buttons() == Qt::MidButton || (event->buttons() == Qt::LeftButton && Contexte::drawMode == NO_DRAW))
    {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        translate(event->x(),event->y());
    }
}

void TileView::loadTiles()
{
    //compute the avg tiles per line
    int col = qSqrt(Contexte::tiles.size());

    for(int i = 0 ; i < Contexte::tiles.size() ; ++i)
    {
        QPixmap pm = QPixmap::fromImage(Contexte::tiles[i]);
        QGraphicsPixmapItem* item = scene->addPixmap(pm);
        item->setData(0, QVariant(i));

        item->setPos((i/col)*pm.width(), (i%col)*pm.height());
    }

}
