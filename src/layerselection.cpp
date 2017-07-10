#include "layerselection.h"
#include "contexte.h"
int Contexte::currentLayer;
qreal Contexte::transparency;

LayerSelection::LayerSelection(QWidget *parent) : QWidget(parent)
{
    Contexte::currentLayer = 1;
    Contexte::transparency = 0.6;

    QBoxLayout* lt = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* mainlt = new QBoxLayout(QBoxLayout::LeftToRight);

    lbl = new QLabel(tr("Z index : "));
    layer = new QSpinBox();
    layer->setMinimum(1);
    layer->setMaximum(3);

    mainlt->addWidget(lbl);
    mainlt->addWidget(layer);

    lt->addLayout(mainlt);


    QBoxLayout* transplt = new QBoxLayout(QBoxLayout::LeftToRight);

    oplbl = new QLabel(tr("Non displayed tile transparency : "));
    transp = new QLabel(tr("transparent"));
    opaque = new QLabel(tr("opaque"));
    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(100);

    slider->setValue(100*Contexte::transparency);

    transplt->addWidget(oplbl);
    transplt->addWidget(transp);
    transplt->addWidget(slider);
    transplt->addWidget(opaque);

    connect(slider, QSlider::valueChanged, this, LayerSelection::changeTransparency);

    lt->addLayout(transplt);
    this->setLayout(lt);

    connect(layer,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, LayerSelection::changeLayer);
}

void LayerSelection::changeLayer(int newVal)
{
    Contexte::currentLayer = newVal;

    emit layerChange();
}

void LayerSelection::changeTransparency(int newVal)
{
    Contexte::transparency = static_cast<qreal>(newVal) /  100.0;

    emit layerChange();
}
