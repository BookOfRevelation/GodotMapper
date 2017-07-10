#include "mapper.h"
#include "contexte.h"
#include <QDebug>

DrawMode Contexte::drawMode;

Mapper::Mapper(const QImage& chipset, int tw, int th, const QString& path) :
    QMainWindow(), tileWidth(tw), tileHeight(th), respath(path)
{
    Contexte::drawMode = NO_DRAW;
    Contexte::generateTiles(chipset, tw, th);

    mainWidget = new MainView(tw, th);
    this->setCentralWidget(mainWidget);

    rightDock = new RightDocker();
    this->addDockWidget(Qt::RightDockWidgetArea, rightDock);

    connect(rightDock, RightDocker::layerChange, mainWidget, MainView::updateLayer);

    createActions();
    createMenus();
    createToolBar();

}

Mapper::Mapper(const QString &path):
    QMainWindow()
{

    QString layer1("");
    QString layer2("");
    QString layer3("");

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(
                  this,
                  tr("Error"),
                  tr("Could not open ")+path+tr(". Please try again (MAPPER LOADING ERROR).")
                  );
    }
    else
    {
        QString line;

        line = file.readLine();
        line = file.readLine();
        line = file.readLine();

        //ext_resource line
        respath = line.split("\"").at(1);

        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();

        //cell/size line
        line = file.readLine();
        QString dimensions = line.split("(").at(1);

        QString w = dimensions.split(",")[0].remove(0,1);
        tileWidth = w.toInt();
        QString h = dimensions.split(",")[1].remove(0,1);
        h.chop(2);
        tileHeight = h.toInt();

        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();

        line = file.readLine();
        layer1 = line.split("=").at(1); //give IntArray

        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();

        line = file.readLine();
        layer2 = line.split("=").at(1); //give IntArray

        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();
        line = file.readLine();

        line = file.readLine();
        layer3 = line.split("=").at(1); //give IntArray

        file.close();
    }

    QString completeResPath = QFileInfo(path).dir().path();
    QString resname = QUrl(respath).fileName();
    completeResPath = completeResPath + QString("/") + resname;
    Contexte::drawMode = NO_DRAW;
    Contexte::generateTiles(Contexte::getImageFromResFile(completeResPath), tileWidth, tileHeight);

    mainWidget = new MainView(tileWidth, tileHeight);
    this->setCentralWidget(mainWidget);

    rightDock = new RightDocker();
    this->addDockWidget(Qt::RightDockWidgetArea, rightDock);

    connect(rightDock, RightDocker::layerChange, mainWidget, MainView::updateLayer);

    createActions();
    createMenus();
    createToolBar();

    drawLayer(layer1,1);
    drawLayer(layer2,2);
    drawLayer(layer3,3);

    this->show();
}

void Mapper::createActions()
{

    //file
    saveAction = new QAction(tr("Save map"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setIcon(QIcon("icons/save.png"));
    QObject::connect(
                saveAction, QAction::triggered,
                this, Mapper::save
                );

    undoAction = new QAction(tr("Undo"));
    undoAction->setShortcut(QKeySequence::Undo);
    undoAction->setIcon(QIcon("icons/undo.png"));
    QObject::connect(
                undoAction, QAction::triggered,
                this, Mapper::undo
                );


    redoAction = new QAction(tr("Redo"));
    redoAction->setShortcut(QKeySequence::Redo);
    redoAction->setIcon(QIcon("icons/redo.png"));
    QObject::connect(
                redoAction, QAction::triggered,
                this, Mapper::redo
                );
}

void Mapper::createMenus()
{
    this->fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(saveAction);

    this->editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
}

void Mapper::createToolBar()
{
    toolBar = new QToolBar();
    toolBar->addAction(saveAction);
    toolBar->addSeparator();
    toolBar->addAction(undoAction);
    toolBar->addAction(redoAction);

    addToolBar(toolBar);
}

void Mapper::save()
{
    QString savePath = QFileDialog::getSaveFileName(
                this,
                tr("Save map"),
                "../",
                tr("Godot map (*.tscn)")
                );


    QFile file(savePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(
                    this,
                    tr("Error"),
                    tr("Could not save ")+savePath+tr(". Please try again.")
                    );
    }
    else
    {
        QString fileContent = computeTscnFile();
        //write the tres file
        QTextStream out(&file);
        out<<fileContent;

        QMessageBox::information(
                    this,
                    tr("File saved"),
                    tr("File saved in ") + QFileInfo(savePath).absoluteDir().path() + QString(".")
                    );

        file.close();

        setWindowModified(false);
    }
}


QString Mapper::computeTscnFile()
{
    QString content = "";

    QString header =
            QString("[gd_scene load_steps=2 format=1]\n\n") +
            QString("[ext_resource path=\"")+ respath +
            QString("\" type=\"TileSet\" id=1]\n\n") +
            QString("[node name=\"Root\" type=\"Node2D\"]\n\n");

    //for each layer
    QString layers("");
    for(int i = 1 ; i <= 3 ; i++)
    {
        QString currentLayer("");

        currentLayer =
                QString("[node name=\"TileMap_Layer"+ QString::number(i) +"\" type=\"TileMap\" parent=\".\"]\n\n") +
                QString("mode = 0\n") +
                QString("tile_set = ExtResource( 1 )\n") +
                QString("cell/size = Vector2( ") + QString::number(tileWidth) + QString(", ") + QString::number(tileHeight) + " )\n" +
                QString("cell/quadrant_size = ") + QString::number(tileWidth) + QString("\n") +
                QString("cell/custom_transform = Matrix32( 1, 0, 0, 1, 0, 0 )\n") +
                QString("cell/half_offset = 2\n") +
                QString("cell/tile_origin = 0\n") +
                QString("cell/y_sort = false\n") +
                QString("cell/use_kinematic = false\n")+
                QString("collision/friction = 1.0\n")+
                QString("collision/bounce = 0.0\n")+
                QString("collision/layers = 1\n")+
                QString("collision/mask = 1\n")+
                QString("occluder/light_mask = 1\n")+
                QString("tile_data = IntArray( "+ mainWidget->getIntArray(i) +" )\n\n")
                ;

        layers = layers + currentLayer;
    }

    content = header + layers;

    return content;

}


void Mapper::drawLayer(QString intArray, int layer)
{
    this->mainWidget->drawLayer(intArray, layer);
}

void Mapper::redo()
{
    this->mainWidget->redo();
}

void Mapper::undo()
{
    this->mainWidget->undo();
}
