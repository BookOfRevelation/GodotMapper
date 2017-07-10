#ifndef CONTEXTE_H
#define CONTEXTE_H

#include <QImage>
#include <QStack>
#include <QPair>

#include "action.h"

enum DrawMode
{
    NO_DRAW, SIMPLE_DRAW, BRUSH_DRAW
};


class Contexte
{
public:
    Contexte();

    static void generateTiles(const QImage& chipset, int tileWidth, int tileHeight);

    static QImage getImageFromResFile(const QString& respath);

    static QVector<QImage> tiles;

    static DrawMode drawMode;

    static QGraphicsPixmapItem* currentItem;

    static int currentLayer;

    static qreal transparency;

    static QPair<Action*, Action*> formAction(QGraphicsPixmapItem* ancestor, QGraphicsPixmapItem* newitem);

    //undo/redo stack
    static QStack<QPair<Action*, Action*>> actions;
    static QStack<QPair<Action*, Action*>> redoStack;

};

#endif // CONTEXTE_H
