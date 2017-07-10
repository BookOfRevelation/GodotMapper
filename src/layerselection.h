#ifndef LAYERSELECTION_H
#define LAYERSELECTION_H

#include <QWidget>
#include <QtWidgets>

class LayerSelection : public QWidget
{
    Q_OBJECT
public:
    explicit LayerSelection(QWidget *parent = 0);

signals:

    void layerChange();

public slots:

private:

    QLabel* lbl;
    QSpinBox* layer;

    QLabel* oplbl;
    QLabel* transp;
    QLabel* opaque;
    QSlider* slider;

    void changeLayer(int newVal);
    void changeTransparency(int newVal);

};

#endif // LAYERSELECTION_H
