#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <qwt_slider.h>
#include "UdpSocket.h"
#include "Plot.h"

/*! \class Window
 *  \brief Main window of the GUI
 *
 *  This class allows to instanciate, organize and update the qt and qwt widgets
 *  used for the display. \n
 *  We can also connect or disconnect from the drone
 *  and get the drone's position in real time thanks to an udpSocket attribute.
 *
 */
class Window : public QWidget
{
    Q_OBJECT

    public:
        Window() ;
        ~Window() ;
        void initWindow() ;
        void initWidgets() ;

    public slots:
        void connect();
        void disconnect();
        void update();

    private:
        //Qt widgets
        QPushButton *buttonConnect ;
        QPushButton *buttonDisconnect ;

        QLabel *labelX ;
        QLabel *labelY ;
        QLabel *labelZ ;

        QLabel *valueX ;
        QLabel *valueY ;
        QLabel *valueZ ;

        //Qwt widgets
        Plot *plot ;
        QwtSlider *slider ;

        //UdpSocket
        UdpSocket *udpSocket ;

};

#endif // WINDOW_H
