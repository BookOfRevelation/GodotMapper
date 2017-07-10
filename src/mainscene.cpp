#include "mainscene.h"
#include "contexte.h"

#include <QDebug>
#include "action.h"


QStack<QPair<Action*, Action*>> Contexte::actions;
QStack<QPair<Action*, Action*>> Contexte::redoStack;

MainScene::MainScene() :
    QGraphicsScene(), clicking(false)
{
}

void MainScene::mousePressEvent(QGraphicsSceneMouseEvent* pMouseEvent)
{

    if(Contexte::drawMode != NO_DRAW)
    {
        QGraphicsPixmapItem* ancestor = nullptr;
        QGraphicsPixmapItem* newitem = nullptr;
        //left click : paint !
        if(pMouseEvent->button() == Qt::LeftButton)
        {
            clicking = true;
            if(Contexte::currentItem)
            {
                //remove existing item
                ancestor = this->removeTile(pMouseEvent->scenePos());

                //add new item
                newitem = this->addTile(pMouseEvent->scenePos());
            }
        }
        //right click : erase !
        else if(pMouseEvent->button() == Qt::RightButton)
        {
            ancestor = this->removeTile(pMouseEvent->scenePos());
        }

        //push to the actions
        qDebug()<<"adding action";
        Contexte::actions.push(Contexte::formAction(ancestor, newitem));

    }
}

QGraphicsPixmapItem* MainScene::removeTile(QPointF at)
{
    QGraphicsPixmapItem* item =
            dynamic_cast<QGraphicsPixmapItem*>
            (
                itemAt
                (
                    at.x(),
                    at.y(),
                    QTransform()
                )
            );

    if(item && item->zValue() == Contexte::currentLayer )
    {
        removeItem(item);
    }

    return item;
}

QGraphicsPixmapItem* MainScene::addTile(QPointF at)
{

    if(Contexte::currentItem)
    {
        QGraphicsPixmapItem* item =
                addPixmap(Contexte::currentItem->pixmap());
        item->setData(0, Contexte::currentItem->data(0));
        item->setZValue(Contexte::currentLayer);
        int correctX = at.x() - (static_cast<int>(at.x()) % Contexte::currentItem->pixmap().width());
        int correctY = at.y() - (static_cast<int>(at.y()) % Contexte::currentItem->pixmap().height());
        item->setPos(correctX, correctY);

        return item;

    }
    else
    {
        return nullptr;
    }

}

void MainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* /*pMouseEvent*/)
{
    clicking = false;
}

void MainScene::mouseMoveEvent(QGraphicsSceneMouseEvent *pMouseEvent)
{
    QGraphicsScene::mouseMoveEvent(pMouseEvent);
    if(clicking && Contexte::drawMode == BRUSH_DRAW)
    {
        QGraphicsPixmapItem* ancestor = nullptr;
        QGraphicsPixmapItem* newitem = nullptr;
        ancestor = this->removeTile(pMouseEvent->scenePos());
        newitem = this->addTile(pMouseEvent->scenePos());
        //push to the actions
        Contexte::actions.push(Contexte::formAction(ancestor, newitem));

    }
}


void MainScene::undo()
{
    if(Contexte::actions.size() > 0)
    {
        QPair<Action*, Action*> lastAct = Contexte::actions.pop();
        Contexte::redoStack.push(Contexte::formAction(lastAct.first->pitem, lastAct.second->pitem));
        if(lastAct.first->pitem)
        {
            //on a un ancètre :
            //le place
            Action* ancact = lastAct.first;
            QGraphicsPixmapItem* item =
                    addPixmap(ancact->pitem->pixmap());
            item->setData(0, ancact->pitem->data(0));
            item->setZValue(ancact->zvalue);
            item->setPos(ancact->position);



        }
        this->removeItem(lastAct.second->pitem);
    }
}

void MainScene::redo()
{
    if(Contexte::redoStack.size() > 0)
    {
        QPair<Action*, Action*> lastAct = Contexte::redoStack.pop();
        Contexte::actions.push(Contexte::formAction(lastAct.first->pitem, lastAct.second->pitem));
        if(lastAct.second->pitem)
        {
            //on a un ancètre :
            //le place
            Action* ancact = lastAct.second;
            QGraphicsPixmapItem* item =
                    addPixmap(ancact->pitem->pixmap());
            item->setData(0, ancact->pitem->data(0));
            item->setZValue(ancact->zvalue);
            item->setPos(ancact->position);



        }
        this->removeItem(lastAct.first->pitem);
    }
}
