#include "Plot.h"

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

    posX = 0 ;
    posY = 0 ;
}

void Plot::drawCanvas(QPainter *painter)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);

    double x = transform(QwtPlot::xBottom,posX) ;
    double y = transform(QwtPlot::yLeft,posY) ;

    painter->drawEllipse(x,y,10,10) ;
}

void Plot::setPosX(double x)
{
    posX = x;
}

void Plot::setPosY(double y)
{
    posY = y;
}
