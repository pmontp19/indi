#include "zoomslider.h"
#include "MyGLWidget.h"

ZoomSlider::ZoomSlider(QWidget *parent) : QSlider(parent)
{

}

void ZoomSlider::tractaZoom() {
    emit enviaZoom(value());
}
