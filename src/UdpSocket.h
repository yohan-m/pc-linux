#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include "wifiFrame.h"


/*! \class UdpSocket
 * \brief Udp socket of the remote pc
 *
 * This class allows to read frames or to send them to the drone. \n
 * Getters allow the user interface to get the positions received and update their displays.
 *
 */
class UdpSocket : public QUdpSocket
{
    Q_OBJECT

    public:

        /*!
         * \brief Constructor
         *
         * Bind a port in shareAdress mode.
         *
         */
        UdpSocket();

        /*!
         * \brief Extract the data from the frame
         *
         * Update the positions atributes of the class with the data received
         *
         * \param wf : The frame from which we extract data
         *
         */
        void processDatagram(wifiFrame wf) ;


        /*!
         * \brief Send positions from localhost to test the display
         *
         */
        void simuDisplay() ;

        void sendFrameDrone(wifiFrame wf);


public slots:

        /*!
         * \brief Send a wifiFrame to the drone
         *
         * Also used in local to test the behaviour in reception
         */
        void write() ;

        /*!
         * \brief Read the wifiFrame received from the drone
         *
         * It emits a signal to update the user interface with the values received.
         * If the wifi frame is a discovery frame, it sends back the frame to the drone.
         */
        void read() ;

    signals:

        /*!
         * \brief Signal emitted just after the data has been extracted from the frame
         *
         */
        void wifiFrameRead(double x, double y, double z);

        void missionStateChanged(char state) ;

    private:
        QTimer *timer ;

        double counterX ;
        double counterY ;
        double counterZ ;
};

#endif // UDPSOCKET_H
