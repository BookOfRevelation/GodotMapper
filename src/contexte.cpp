#include "contexte.h"
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QDir>
#include <QMessageBox>

QVector<QImage> Contexte::tiles;

QGraphicsPixmapItem* Contexte::currentItem;


Contexte::Contexte()
{

}


void Contexte::generateTiles(const QImage &chipset, int tileWidth, int tileHeight)
{
    Contexte::tiles.clear();
    int width = chipset.width()/tileWidth;
    int height = chipset.height()/tileHeight;

    for(int i = 0 ; i < width ; ++i)
    {
        for(int j = 0 ; j < height ; ++j)
            Contexte::tiles.push_back(chipset.copy(i*tileWidth, j*tileHeight, tileWidth, tileHeight));
    }

    Contexte::currentItem = nullptr;
}


QImage Contexte::getImageFromResFile(const QString &respath)
{
    QString basdir = QFileInfo(respath).dir().path();
    //open the resfile and get the image url
    QString impath("");

    QFile file(respath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(
                  nullptr,
                  QString("Error"),
                  QString("Could not open ")+respath+QString(". Please try again (CONTEXTE GET IMAGE).")
                  );
    }
    else
    {
        QString line;

        line = file.readLine();
        line = file.readLine();
        line = file.readLine();

        //ext_resource line
        QString imlocal = line.split("\"").at(1);

        QUrl imurl(imlocal);


        impath = basdir + QString("/") + imurl.fileName();
    }

    qDebug()<<"loading "<<impath;
    qDebug()<<"from : "<<respath;
    return QImage(impath);
}

QPair<Action*, Action*> Contexte::formAction(QGraphicsPixmapItem *ancestor, QGraphicsPixmapItem *newitem)
{
    Action* ancact;
    Action* newact;

    if(ancestor)
    {
        //keeping info after remove ?
        ancact = new Action(ancestor, ancestor->scenePos(), ancestor->zValue() );
    }
    else
    {
        ancact = new Action(nullptr, QPointF(), 0);
    }
    if(newitem)
    {
        newact = new Action(newitem, newitem->scenePos(), newitem->zValue());
    }
    else
    {
        newact = new Action(nullptr, QPointF(), 0);
    }
    qDebug()<<"Forming : "<<QPair<Action*, Action*>(ancact, newact);
    return QPair<Action*, Action*>(ancact, newact);

}
