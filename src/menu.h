#ifndef MENU_H
#define MENU_H

#include "mainwidget.h"
#include "newmap.h"
#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_tilesetbtn_clicked();

    void on_mapbtn_clicked();

    void on_loadbtn_clicked();

private:
    Ui::Menu *ui;

    MainWidget* tileWidget;

    NewMap* newMap;
};

#endif // MENU_H
