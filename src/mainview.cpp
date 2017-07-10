#include "mainview.h"
#include "contexte.h"

#define SCENE_LIMITS 100
#define GODOT_Y_MAX 65536

#include <QDebug>
#include <QPointF>
#include <QScrollBar>

MainView::MainView(int tw, int th)
    : QGraphicsView(), tileWidth(tw), tileHeight(th)
{
    scene = new MainScene();
    this->setScene(scene);
    this->setMouseTracking(true);
    this->viewport()->setMouseTracking(true);
    drawGrid();

}

void MainView::wheelEvent(QWheelEvent *event)
{
    const QPointF p0scene = mapToScene(event->pos());
    qreal factor = (std::pow(1.2, event->delta()/240.0));
    scale(factor,factor);

    const QPointF p1mouse = mapFromScene(p0scene);
    const QPointF move = p1mouse - event->pos();

    horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
    verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());

}

void MainView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if(event->buttons() == Qt::MidButton || (event->buttons() == Qt::LeftButton && Contexte::drawMode == NO_DRAW))
    {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        translate(event->x(),event->y());
    }
}

void MainView::drawGrid()
{
    QPen axisPen(Qt::blue);
    QPen normalPen(Qt::gray);

    //add axis
    this->scene->addLine(0, 0, 0, SCENE_LIMITS*tileHeight, axisPen);
    this->scene->addLine(0, 0, SCENE_LIMITS*tileWidth, 0, axisPen);

    for(int i = 1 ; i < SCENE_LIMITS ; ++i)
    {
        this->scene->addLine(i*tileWidth, 0, i*tileWidth, SCENE_LIMITS*tileHeight, normalPen);
    }

    for(int j = 1; j < SCENE_LIMITS;  ++j)
    {
        this->scene->addLine(0, j*tileHeight, SCENE_LIMITS*tileWidth, j*tileHeight, normalPen);
    }
}

void MainView::updateLayer()
{
    int layer = Contexte::currentLayer;

    QGraphicsItem* item;

    foreach (item, this->scene->items())
    {
        QGraphicsPixmapItem* pitem =
                dynamic_cast<QGraphicsPixmapItem*>(item);
        if(pitem)
        {
            if(pitem->zValue() == layer)
            {
                //current layer is opaque
                pitem->setOpacity(1.0);
            }
            else
            {
                //no current layer is transparent
                pitem->setOpacity(Contexte::transparency);
            }
        }
    }
}

QString MainView::getIntArray(int layer) const
{
    QString intArray = "";

    QGraphicsItem* item;

    foreach(item, scene->items())
    {
        //compute the coord if the zValue is
        //equal to the proposed layer
        if(item->zValue() == layer)
        {
            //force int division
            int coordX = static_cast<int>(item->scenePos().x()) / tileWidth;
            int coordY = static_cast<int>(item->scenePos().y()) / tileHeight;

            int coord1d = coordX + (coordY * GODOT_Y_MAX);

            int tileid = item->data(0).toInt();

            intArray =
                    intArray +
                    QString::number(coord1d) +
                    QString(", ") +
                    QString::number(tileid) +
                    QString(", ")
                    ;
        }
    }

    //remove last ", " sequence
    intArray.chop(2);

    return intArray;
}


void MainView::drawLayer(QString intArray, int layer)
{
    QString numbers = intArray.split("(").at(1);
    numbers.chop(2);

    qDebug()<<"IntArray values : "<<numbers;

    QStringList list = numbers.split(",");

    int posX = 0;
    int posY = 0;

    for(int i = 0; i < list.size(); ++i)
    {
        //get the id
        if(i%2)
        {
            int imid = list[i].toInt();
            QImage im = Contexte::tiles.at(imid);

            QGraphicsPixmapItem* item = scene->addPixmap(QPixmap::fromImage(im));
            item->setPos(posX, posY);
            item->setData(0, QVariant(imid));
            item->setZValue(layer);

        }
        //get the pos
        else
        {
            int pos1d = list[i].toInt();
            posY = (pos1d / GODOT_Y_MAX) * tileHeight;
            posX = (pos1d % GODOT_Y_MAX) * tileWidth;


        }
    }
}

void MainView::undo()
{
    this->scene->undo();
}

void MainView::redo()
{
    this->scene->redo();
}
