#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "mainscene.h"
#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>

class MainScene;

class MainView : public QGraphicsView
{
public:
    MainView(int tw, int th);

    void wheelEvent(QWheelEvent* event);

    void mouseMoveEvent(QMouseEvent *event);

    void updateLayer();

    QString getIntArray(int layer) const;

    void drawLayer(QString intArray, int layer);
    void undo();
    void redo();

private:
    int tileWidth;
    int tileHeight;

    MainScene* scene;


    void drawGrid();

};

#endif // MAINVIEW_H
