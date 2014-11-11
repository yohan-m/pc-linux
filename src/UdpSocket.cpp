#include "UdpSocket.h"

UdpSocket::UdpSocket() : QUdpSocket()
{
    bind(31000,QUdpSocket::ShareAddress) ;

    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(read())) ;
}

void UdpSocket::write()
{
    //Creation of the frame
    wifiFrame wf ;
    counterX += 5 ;
    counterY += 5 ;
    counterZ += 5 ;
    wf = createWifiFrame(TIME_FRAME,counterX,counterY,counterZ,4) ;

    //Conversion of the frame in *char
    char * tab = wifiFrameToChar(wf) ;

    //Send the frame
    writeDatagram(tab, sizeof(char)*19, QHostAddress::LocalHost, 31000) ;
}

void UdpSocket::read()
{
     qDebug() << "Lecture activée" ;

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
    qDebug() << "data1: " << hex << wf.data[0];
    qDebug() << "data2: " << hex << wf.data[1] ;
    qDebug() << "data3: " << hex << wf.data[2] ;
    qDebug() << "data4: " << hex << wf.data[3] ;

    if(simu)
    {
        posX = (double)wf.data[0]/100 ;
        posY = (double)wf.data[1]/100 ;
        posZ = (double)wf.data[2]/100 ;

        emit wifiFrameRead();
    }
}

void UdpSocket::simuDisplay()
{
    posX = 0 ;
    posY = 0 ;
    posZ = 0 ;

    //Used to test the real time display with incremented values sent from localhost
    counterX = 0 ;
    counterY = 0 ;
    counterZ = 0 ;

    //Init of the timer which will call the write function
    timer = new QTimer() ;
    timer->setInterval(100) ;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(write())) ;
    timer->start() ;

    //Active the update with the read value
    simu = true ;
}

double UdpSocket::getPosX()
{
    return posX ;
}


double UdpSocket::getPosY()
{
    return posY ;
}


double UdpSocket::getPosZ()
{
    return posZ ;
}

