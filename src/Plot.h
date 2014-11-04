#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>
#include <qwt_plot_grid.h>

#include <QWidget>

/*! \class Plot
 * \brief 2D display widget
 *
 * This class inherits QwtPlot and allows to display a two dimensionel graph. \n
 * It is used for a 2D display of the drone's position.
 *
 */
class Plot :  public QwtPlot
{
    public:
        Plot(QWidget *parent);
        virtual void drawCanvas (QPainter *painter) ;

        void setPosX(int x);
        void setPosY(int y);

private:
        QwtPlotGrid *grid ;

        int posX ;
        int posY ;
};

#endif // PLOT_H
