#include "Plot.h"
#include <QLabel>

Plot::Plot(QWidget *parent) : QwtPlot(parent)
{
    setTitle("2D display of the drone's position");
    setFixedSize(800,600) ;

    /*grid = new QwtPlotGrid() ;
    grid->setPen(Qt::black);
    grid->attach(this);*/

    setAxisScale(QwtPlot::xBottom,0,6.6,0.5);
    setAxisScale(QwtPlot::yLeft,0,4.2,0.5);

    setAxisTitle(QwtPlot::xBottom,QString("Y (m)")) ;
    setAxisTitle(QwtPlot::yLeft,QString("X (m)")) ;

    setCanvasBackground(Qt::white);

    img = new QPixmap(":/img/images/drone.jpg") ;

    posX = 4.2/2 ;
    posY = 6.6/2 ;

    xMission = 0 ;
    yMission = 0 ;
    missionActive = false ;
}

void Plot::drawCanvas(QPainter *painter)
{
    double x ;
    double y ;

    if(missionActive)
    {
        x = transform(QwtPlot::xBottom,yMission) ;
        y = transform(QwtPlot::yLeft,xMission) ;
        x -= 20 ;
        y -= 20;

        QPen pen (Qt::red);
        pen.setWidth(5) ;
        painter->setPen(pen);
        painter->setBrush(Qt::white);
        painter->drawEllipse(x,y,35,35);
    }

    x = transform(QwtPlot::xBottom,posY) ;
    y = transform(QwtPlot::yLeft,posX) ;

    x = x - img->width()/2 ;
    y = y - img->height()/2 ;

    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawPixmap(x,y,*img);
}

void Plot::setPosX(double x)
{
    posX = x;
}

void Plot::setPosY(double y)
{
    posY = y;
}

void Plot::drawTarget(double x, double y)
{
    missionActive = true ;
    xMission = x ;
    yMission = y ;
}

void Plot::removeTarget()
{
    missionActive = false ;
}
