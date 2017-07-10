#include "rigthdocker.h"
#include "tileview.h"
#include "drawmodewidget.h"
#include "layerselection.h"
RightDocker::RightDocker():
    QDockWidget()
{

    widget = new QWidget();

    QBoxLayout* mainlt = new QBoxLayout(QBoxLayout::TopToBottom);

    mainlt->addWidget(new TileView());
    mainlt->addWidget(new DrawModeWidget());
    LayerSelection* l = new LayerSelection();
    mainlt->addWidget(l);

    connect(l, LayerSelection::layerChange, this, RightDocker::changeLayer);


    widget->setLayout(mainlt);



    this->setWidget(widget);


}


void RightDocker::changeLayer()
{
    emit layerChange();
}
