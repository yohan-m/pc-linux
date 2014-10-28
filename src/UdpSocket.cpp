#include "UdpSocket.h"

UdpSocket::UdpSocket() : QUdpSocket()
{
    bind(QHostAddress::Local,31000) ;

    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(read())) ;

    timer = new QTimer() ;
    timer->setInterval(1000) ;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(write())) ;
    timer->start() ;
}

void UdpSocket::write()
{
    u_int32_t data1 = 3 ;
    u_int32_t data2 = 4 ;
    u_int32_t data3 = 5 ;
    u_int32_t data4 = 6 ;

    //Creation of the frame
    wifiFrame wf ;
    wf = createWifiFrame(TIME_FRAME,data1,data2,data3,data4) ;

    //Conversion of the frame in *char
    char tab[19] ;
    wifiFrameToChar(wf,tab) ;

    //Send the frame
    qint16 nbBit = writeDatagram(tab, sizeof(char)*19, QHostAddress::Localhost,31000) ;
    qDebug() << "nbBit: " << nbBit ;
}

void UdpSocket::read()
{
     qDebug() << "Reception: " ;
     while (hasPendingDatagrams())
     {
         QByteArray datagram;
         datagram.resize(pendingDatagramSize());

         QHostAddress sender;
         quint16 senderPort;

         char tab[19] ;
         qint16 taille = (qint16)sizeof(char)*19 ;
         readDatagram(tab, taille , &sender, &senderPort) ;

         wifiFrame wf2 ;
         wf2 = wifiFrameFromChar(tab) ;

         qDebug() << "Message from: " << sender.toString();
         qDebug() << "Message port: " << senderPort;
         qDebug() << "Num: " << wf2.seqNum ;
         qDebug() << "data1: " << wf2.data[0] ;
         qDebug() << "data2: " << wf2.data[1] ;
         qDebug() << "data3: " << wf2.data[2] ;
         qDebug() << "data4: " << wf2.data[3] ;
     }

     processDatagram() ;
}


void UdpSocket::processDatagram()
{
}
