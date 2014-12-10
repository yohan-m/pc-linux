#include "UdpSocket.h"

UdpSocket::UdpSocket() : QUdpSocket()
{
    bind(PC_PORT,QUdpSocket::ShareAddress) ;

    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(read())) ;
}

void UdpSocket::write()
{
    //Creation of the frame
    wifiFrame wf ;
    counterX += 4 ;
    counterY += 8 ;
    counterZ += 5 ;
    wf = createPositionFrame(counterX,counterY,counterZ) ;

    //Conversion of the frame in *char
    char *tab = (char*)&wf ;

    //Send the frame
    writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress::LocalHost, DRONE_PORT) ;
}

void UdpSocket::sendFrameDrone(wifiFrame wf)
{
    //Conversion of the frame in *char
    char *tab = (char*)&wf ;
    writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;
}

void UdpSocket::read()
{
     //qDebug() << "Lecture activée" ;

     QHostAddress sender ;
     quint16 senderPort;
     wifiFrame wf ;
     char tab[CONVERTED_WIFI_FRAME_SIZE] ;

     while (hasPendingDatagrams())
     {
         //Read the frame and store it in tab
         readDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, &sender, &senderPort) ;

         wf = *(wifiFrame*)tab;

         if(wf.type == DISCOVERY_FRAME)
         {
            //Send back the discovery frame received to the sender
            writeDatagram(tab,sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, sender, senderPort) ;
         }
         else if(wf.type == MISSION_FRAME)
         {
             qDebug()<<"mission frame received";
             emit missionStateChanged(wf.stateMission) ;
         }
         else
            processDatagram(wf) ;
     }
}

void UdpSocket::processDatagram(wifiFrame wf)
{
    /*qDebug() << "Num Seq: " << wf.seqNum ;
    qDebug() << "Type: " << wf.type ;
    qDebug() << "x: " << wf.positions[0] ;
    qDebug() << "y: " << wf.positions[1] ;
    qDebug() << "z: " << wf.positions[2] ;

    qDebug() << "posX : " << wf.positions[0] ;*/

    double posX = (double)(wf.positions[0])/(double)100.0 ;
    double posY = (double)(wf.positions[1])/(double)100.0 ;
    double posZ = (double)(wf.positions[2])/(double)100.0 ;

    //qDebug() << "posX : " << posX ;

    emit wifiFrameRead(posX, posY, posZ);
}

void UdpSocket::simuDisplay()
{
    //Used to test the real time display with incremented values sent from localhost
    counterX = 4.2/2 ;
    counterY = 6.6/2 ;
    counterZ = 0 ;

    //Init of the timer which will call the write function
    timer = new QTimer() ;
    timer->setInterval(100) ;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(write())) ;
    timer->start() ;
}
