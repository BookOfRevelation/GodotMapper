#include "tilescene.h"
#include "contexte.h"
TileScene::TileScene()
    : QGraphicsScene()
{
    selectedEffect = new QGraphicsColorizeEffect;
    selectedEffect->setColor(Qt::red);
}

TileScene::~TileScene()
{
    delete selectedEffect;
}

void TileScene::mousePressEvent(QGraphicsSceneMouseEvent* pMouseEvent)
{
    QGraphicsPixmapItem* item =
            dynamic_cast<QGraphicsPixmapItem*>
            (
                itemAt
                (
                    pMouseEvent->scenePos().x(),
                    pMouseEvent->scenePos().y(),
                    QTransform()
                )
            );

    if(item)
    {
        item->setGraphicsEffect(selectedEffect);
        Contexte::currentItem = item;

    }
    else
    {
        Contexte::currentItem = nullptr;
    }
}
