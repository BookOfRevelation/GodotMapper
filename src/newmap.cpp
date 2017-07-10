#include "newmap.h"
#include "ui_newmap.h"


#include <QtWidgets>

NewMap::NewMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMap),
    filename(""),
    imagepath(""),
    tileWidth(0),
    tileHeight(0),
    chipsetWidth(0),
    chipsetHeight(0),
    mapper(nullptr)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());


}

NewMap::~NewMap()
{
    delete ui;
}

void NewMap::on_tilebtn_clicked()
{
    filename = QFileDialog::getOpenFileName(
                this,
                tr("Load tileset"),
                "../",
                tr("Tileset (*.tres)")
                );

    QImage im;
    QString basepath = QFileInfo(filename).absoluteDir().path();

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(
                  this,
                  tr("Error"),
                  tr("Could not open ")+filename+tr(". Please try again.")
                  );
    }
    else
    {
        //skip first 2lines
        QByteArray line = file.readLine();
        line = file.readLine();

        //get ext_resource
        line = file.readLine();
        QString strline(line);
        QString respath(line);
        respath = respath.split(" ").at(1).split("\"").at(1);

        QString imageName = strline.split(" ").at(1).split("/").at(3);
        imageName.chop(1);


        if(! (im.load(basepath + "/" +imageName)))
        {
            QMessageBox::critical(
                      this,
                      tr("Error"),
                      tr("Could not find the chipset image. Please check that the file ")+imageName+tr(" is located in ") + basepath + tr(".")
                      );
            filename = "";
            ui->tilele->setText("");
        }
        else
        {
            this->chipsetWidth = im.width();
            this->chipsetHeight = im.height();

            //get the first region to det tile
            //width and tile height

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

            //0/region
            line = file.readLine();

            QString regionline(line);

            this->tileWidth = regionline.split("=").at(1).split(",").at(2).simplified().toInt();

            regionline = QString(line);
            regionline = regionline.split("=").at(1).split(",").at(3);
            regionline.chop(2);
            this->tileHeight = regionline.simplified().toInt();

            ui->createbtn->setEnabled(true);

            if(mapper != nullptr)
            {
                delete mapper;
                mapper = nullptr;
            }
            this->mapper = new Mapper(im, tileWidth, tileHeight, QFileInfo(respath).dir().path() + "/" + QFileInfo(filename).fileName());


        }

        file.close();
    }



    ui->tilele->setText(filename);
}

void NewMap::on_createbtn_clicked()
{
    this->mapper->show();
    this->setHidden(true);

}


void NewMap::loadMap(const QString &scenePath)
{
    if(mapper != nullptr)
    {
        delete mapper;
        mapper = nullptr;
    }

    mapper = new Mapper(scenePath);
}
