#include "UdpSocket.h"

UdpSocket::UdpSocket() : QUdpSocket()
{
    bind(31000,QUdpSocket::ShareAddress) ;

    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(read())) ;

    //Init of the timer which will call the write function each period
    timer = new QTimer() ;
    timer->setInterval(500) ;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(write())) ;
    timer->start() ;

    posX = 0 ;
    posY = 0 ;
    posZ = 0 ;

    //Used to test the real time display with incremented values sent from localhost
    counterX = 0 ;
    counterY = 0 ;
    counterZ = 0 ;   
}

void UdpSocket::write()
{
    //Creation of the frame
    wifiFrame wf ;
    wf = createWifiFrame(TIME_FRAME,++counterX,++counterY,++counterZ,4) ;

    //Conversion of the frame in *char
    char * tab = wifiFrameToChar(wf) ;

    //Send the frame
    writeDatagram(tab, sizeof(char)*19, QHostAddress::LocalHost, 31000) ;
}

void UdpSocket::read()
{
     while (hasPendingDatagrams())
     {
         QHostAddress sender ;
         quint16 senderPort;

         //Read the frame and store it in tab
         char tab[19] ;
         readDatagram(tab, sizeof(char)*19, &sender, &senderPort) ;

         wifiFrame wf ;
         wf = wifiFrameFromChar(tab) ;


         if(wf.type == DISCOVERY_FRAME)
         {
            //Send back the discovery frame received to the sender
            char * tab = wifiFrameToChar(wf) ;
            writeDatagram(tab,sizeof(char)*19, sender, senderPort) ;
         }
         else
            processDatagram(wf) ;
     }
}

void UdpSocket::processDatagram(wifiFrame wf)
{
    qDebug() << "Num: " << wf.seqNum ;
    qDebug() << "Type: " << wf.type ;
    qDebug() << "data1: " << wf.data[0] ;
    qDebug() << "data2: " << wf.data[1] ;
    qDebug() << "data3: " << wf.data[2] ;
    qDebug() << "data4: " << wf.data[3] ;

    posX = wf.data[0] ;
    posY = wf.data[1] ;
    posZ = wf.data[2] ;
}

int UdpSocket::getPosX()
{
    return posX ;
}


int UdpSocket::getPosY()
{
    return posY ;
}


int UdpSocket::getPosZ()
{
    return posZ ;
}
