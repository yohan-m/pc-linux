#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include "wifiFrame.h"

class UdpSocket : public QUdpSocket
{
    Q_OBJECT

    public:
        UdpSocket();
        void processDatagram() ;

    public slots:
        void write() ;
        void read() ;

    private:
        QTimer *timer ;
};

#endif // UDPSOCKET_H
