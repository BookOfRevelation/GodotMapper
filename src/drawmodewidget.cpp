#include "drawmodewidget.h"
#include "contexte.h"


DrawModeWidget::DrawModeWidget(QWidget *parent) : QWidget(parent)
{
    bgroup = new QButtonGroup(this);
    bgroup->setExclusive(true);

    mouseBtn = new QPushButton(QIcon("icons/hand.png"), "mouse");
    pencilBtn = new QPushButton(QIcon("icons/pencil.png"), "pencil");
    brushBtn = new QPushButton(QIcon("icons/brush.png"), "brush");

    mouseBtn->setCheckable(true);
    pencilBtn->setCheckable(true);
    brushBtn->setCheckable(true);

    bgroup->addButton(mouseBtn, NO_DRAW);
    bgroup->addButton(pencilBtn, SIMPLE_DRAW);
    bgroup->addButton(brushBtn, BRUSH_DRAW);

    QBoxLayout* mainlt = new QBoxLayout(QBoxLayout::LeftToRight);
    this->setLayout(mainlt);

    mainlt->addWidget(mouseBtn);
    mainlt->addWidget(pencilBtn);
    mainlt->addWidget(brushBtn);

    connect(
            bgroup,
            static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            [=](int mode){Contexte::drawMode = static_cast<DrawMode>(mode); }
    );



}

