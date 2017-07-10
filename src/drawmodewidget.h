#ifndef DRAWMODEWIDGET_H
#define DRAWMODEWIDGET_H

#include <QWidget>
#include "contexte.h"

#include <QtWidgets>

class DrawModeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawModeWidget(QWidget *parent = 0);

signals:

public slots:


private:
    QButtonGroup* bgroup;

    QPushButton* mouseBtn;
    QPushButton* pencilBtn;
    QPushButton* brushBtn;

};

#endif // DRAWMODEWIDGET_H
