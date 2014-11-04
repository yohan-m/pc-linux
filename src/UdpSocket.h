#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include "wifiFrame.h"


/*! \class UdpSocket
 * \brief Socket udp of the remote pc
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
         */
        void processDatagram(wifiFrame wf) ;

        int getPosX() ;
        int getPosY() ;
        int getPosZ() ;

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

    private:
        QTimer *timer ;

        int posX ;
        int posY ;
        int posZ ;
        double counterX ;
        double counterY ;
        double counterZ ;

};

#endif // UDPSOCKET_H
