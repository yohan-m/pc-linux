#include "UdpSocket.h"
#include <stdint.h>
#include <QDebug>

UdpSocket::UdpSocket() : QUdpSocket()
{
    bind(QHostAddress("192.168.1.2"),52400) ;

    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(read())) ;

    timer = new QTimer() ;
    timer->setInterval(1000) ;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(write())) ;
    timer->start() ;
}

void UdpSocket::write()
{
    QByteArray data ;
    data.append("Test") ;

    writeDatagram(data, QHostAddress("192.168.1.1"),31000);
}

void UdpSocket::read()
{
     while (hasPendingDatagrams())
     {
         QByteArray datagram;
         datagram.resize(pendingDatagramSize());

         QHostAddress sender;
         quint16 senderPort;

         readDatagram(datagram.data(), datagram.size(), &sender, &senderPort) ;


         qDebug() << "Message from: " << sender.toString();
         qDebug() << "Message port: " << senderPort;
         qDebug() << "Message: " << datagram.data() ;
     }

     processDatagram() ;
}


void UdpSocket::processDatagram()
{
}
