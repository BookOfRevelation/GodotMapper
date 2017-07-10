#ifndef RIGTHDOCKER_H
#define RIGTHDOCKER_H

#include <QtWidgets>
#include <QDockWidget>

class RightDocker : public QDockWidget
{
    Q_OBJECT
public:
    RightDocker();

signals:
    void layerChange();

public slots:
    void changeLayer();

private:
    QWidget* widget;
};

#endif // RIGTHDOCKER_H
