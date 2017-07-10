#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu),
    tileWidget(nullptr),
    newMap(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    tileWidget = new MainWidget(this);
    newMap = new NewMap(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_tilesetbtn_clicked()
{
    tileWidget->show();
}

void Menu::on_mapbtn_clicked()
{
    newMap->show();
}

void Menu::on_loadbtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Load map"),
                "../",
                tr("Godot map (*.tscn)")
                );


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
        file.close();

        newMap->loadMap(filename);
    }
}
