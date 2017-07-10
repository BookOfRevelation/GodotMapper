#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDialog>

namespace Ui {
class MainWidget;
}

class MainWidget : public QDialog
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    QString computeTresFile(const QString& dirPath);

private slots:

    void on_tilesetbtn_clicked();

    void on_exportbtn_clicked();

private:
    Ui::MainWidget *ui;

    QString filename;

    int tileWidth;
    int tileHeight;

    int chipsetWidth;
    int chipsetHeight;



};

#endif // MAINWIDGET_H
