#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QtWidgets>

MainWidget::MainWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWidget),
    filename(""),
    tileWidth(0),
    tileHeight(0)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

MainWidget::~MainWidget()
{
    delete ui;
}



void MainWidget::on_tilesetbtn_clicked()
{
    filename = QFileDialog::getOpenFileName(
                this,
                tr("Load tileset"),
                "../",
                tr("Image (*.png)")
                );
    ui->tilesetle->setText(filename);

    QImage image(filename) ;
    chipsetWidth = image.width();
    chipsetHeight = image.height();

}

void MainWidget::on_exportbtn_clicked()
{
    if(filename.isEmpty())
    {
        QMessageBox::critical(
                    this,
                    QString(tr("Missing parameters")),
                    QString(tr("The filepath cannot be empty."))
                    );
    }
    else if(ui->wsb->value() <= 0 || ui->hsb->value() <= 0)
    {
        QMessageBox::critical(
                    this,
                    QString(tr("Wrong dimensions")),
                    QString(tr("The tile dimenson cannot contains a 0 or negative px value."))
                    );
    }
    else
    {
        tileWidth = ui->wsb->value();
        tileHeight = ui->hsb->value();
        QString savePath = QFileDialog::getSaveFileName(
                    this,
                    tr("Save tileset"),
                    "../",
                    tr("Tileset resource (*.tres)")
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

            QString fileContent = computeTresFile(QFileInfo(savePath).absoluteDir().dirName());
            //write the tres file
            QTextStream out(&file);
            out<<fileContent;


            //copy the base image to be in the same directory
            //as the tres file

            qDebug()<<"original : "<<filename;
            qDebug()<<"target : "<<QFileInfo(savePath).absoluteDir().path() + QFileInfo(filename).fileName();
            QFile::copy(
                        filename,
                        QFileInfo(savePath).absoluteDir().path() + QString("/") + QFileInfo(filename).fileName()
                        );

            QMessageBox::information(
                        this,
                        tr("File saved"),
                        tr("File saved in ") + QFileInfo(savePath).absoluteDir().path() + QString(".")
                        );

            ui->hsb->setValue(0);
            ui->wsb->setValue(0);

            this->filename = "";

            this->tileWidth = this->tileHeight = 0;

            this->chipsetWidth = this->chipsetHeight = 0;

            ui->tilesetle->setText("");

            file.close();

        }

    }
}

QString MainWidget::computeTresFile(const QString& dirPath)
{
    QString content = "";

    QString path = dirPath + QString("/") + QFileInfo(filename).fileName();


    QString header =
            QString("[gd_resource type=\"TileSet\" load_steps=3 format=1]\n\n") +
            QString("[ext_resource path=\"res://")+
            QString(path)+
            QString("\" type=\"Texture\" id=1]\n\n") +
            QString("[sub_resource type=\"RectangleShape2D\" id=1]\n\n") +
            QString("custom_solver_bias = 0.0\nextents = Vector2( 10, 10 )\n\n[resource]\n\n")
            ;

    qDebug()<<"Dimensions : "<<tileWidth<<" "<<tileHeight<<" (tiles)";

    int vtiles = chipsetWidth / tileWidth;
    int htiles = chipsetHeight / tileHeight;

    QString tileDescription = "";
    qDebug()<<"Found "<<vtiles<<" * "<<htiles<<" nodes";
    for(int i = 0; i < vtiles; ++i)
    {
        for(int j = 0; j < htiles; ++j)
        {
            QString id = QString::number(j + i*htiles);
            QString prefix = id + "/";
            QString currentTile = "";

            QString region =
                    QString::number(i*tileWidth) + ", " +
                    QString::number(j*tileHeight) + ", " +
                    QString::number(tileWidth) + ", "+
                    QString::number(tileHeight);

            currentTile =
                    prefix + QString("name = \"tile") + id + QString("\"\n") +
                    prefix + QString("texture = ExtResource( 1 )\n") +
                    prefix + QString("tex_offset = Vector2( 0, 0 )\n") +
                    prefix + QString("region = Rect2( ") + region + QString(" )\n") +
                    prefix + QString("occluder_offset = Vector2( 8, 8 )\n") +
                    prefix + QString("navigation_offset = Vector2( 8, 8 )\n") +
                    prefix + QString("shape_offset = Vector2( 0, 0 )\n") +
                    prefix + QString("shapes = [ ]\n")
                    ;
            tileDescription = tileDescription + currentTile;
        }
    }

    qDebug()<<"Total tiles : "<<tileDescription.size();

    content = "" + header + tileDescription;
    return content;
}

