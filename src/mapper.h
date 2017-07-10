#ifndef MAPPER_H
#define MAPPER_H

#include <QMainWindow>
#include <QToolBar>

#include "mainview.h"
#include "rigthdocker.h"

class Mapper : public QMainWindow
{
    Q_OBJECT
public:
    //new map
    Mapper(const QImage& chipset, int tw, int th, const QString& path);

    //load map
    Mapper(const QString& path);

    void save();

    void undo();
    void redo();


private:

    int tileWidth;
    int tileHeight;

    QString respath;

    MainView* mainWidget;
    RightDocker* rightDock;

    //menus
    QMenu* fileMenu;
    QMenu* editMenu;
    //actions
    QAction* saveAction;
    QAction* undoAction;
    QAction* redoAction;
    //toolbar
    QToolBar* toolBar;

    void createActions();
    void createToolBar();
    void createMenus();

    QString computeTscnFile();

    void drawLayer(QString intArray, int layer);



};

#endif // MAPPER_H
