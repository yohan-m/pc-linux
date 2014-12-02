#include "Plot.h"
#include <QLabel>

Plot::Plot(QWidget *parent) : QwtPlot(parent)
{
    setTitle("2D display of the drone's position");
    setFixedSize(800,600) ;

    /*grid = new QwtPlotGrid() ;
    grid->setPen(Qt::black);
    grid->attach(this);*/

    setAxisScale(QwtPlot::xBottom,0,5.5,0.5);
    setAxisScale(QwtPlot::yLeft,0,3.5,0.5);

    setAxisTitle(QwtPlot::xBottom,QString("Y (m)")) ;
    setAxisTitle(QwtPlot::yLeft,QString("X (m)")) ;

    setCanvasBackground(Qt::white);

    img = new QPixmap(":/img/images/drone.jpg") ;

    posX = 3.5/2 ;
    posY = 5.5/2 ;
}

void Plot::drawCanvas(QPainter *painter)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);

    double x = transform(QwtPlot::xBottom,posY) ;
    double y = transform(QwtPlot::yLeft,posX) ;

    x = x - img->width()/2 ;
    y = y - img->height()/2 ;

    painter->drawPixmap(x,y,*img);

    //painter->drawEllipse(x,y,10,10) ;
}

QImage m_image;

void Plot::setPosX(double x)
{
    posX = x;
}

void Plot::setPosY(double y)
{
    posY = y;
}
