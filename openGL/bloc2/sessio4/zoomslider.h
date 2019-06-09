#ifndef ZOOMSLIDER_H
#define ZOOMSLIDER_H

#include <QSlider>

class ZoomSlider : public QSlider
{
    Q_OBJECT
public:
    explicit ZoomSlider(QWidget *parent = nullptr);

signals:
    void enviaZoom(int valor);

public slots:
    void tractaZoom();
};

#endif // ZOOMSLIDER_H
