#ifndef NEWMAP_H
#define NEWMAP_H

#include "mapper.h"
#include <QDialog>

namespace Ui {
class NewMap;
}

class NewMap : public QDialog
{
    Q_OBJECT

public:
    explicit NewMap(QWidget *parent = 0);
    ~NewMap();

    void loadMap(const QString& scenePath);

private slots:
    void on_tilebtn_clicked();

    void on_createbtn_clicked();

private:
    Ui::NewMap *ui;

    QString filename;
    QString imagepath;

    int tileWidth;
    int tileHeight;

    int chipsetWidth;
    int chipsetHeight;

    Mapper* mapper;



};

#endif // NEWMAP_H
