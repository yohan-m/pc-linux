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

        /*!
         * \brief Draw the position
         *
         * This function is called each time the position needs to be redrawn \n
         * Convert the drone's position in the widget's coordinates
         *
         * \param painter : Painter used for drawing
         *
         */
        virtual void drawCanvas (QPainter *painter) ;

        void setPosX(double x);
        void setPosY(double y);
        void drawTarget(double xMission, double yMission);
        void removeTarget();

private:
        QwtPlotGrid *grid ;
        QPixmap *img ;

        double posX ;
        double posY ;
        double xMission ;
        double yMission ;
        bool missionActive ;

};

#endif // PLOT_H
