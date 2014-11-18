#include "dronenavdata.h"

droneNavData::droneNavData(droneControl * control_init) : QUdpSocket()
{
    bind(5554,QUdpSocket::ShareAddress) ;

    control = control_init;

    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(slotRead())) ;
}

int droneNavData::init(int seqNum)
{
    char init[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int cnt_bytes = write((const char *)init,14);
    if(cnt_bytes!=14) {
        qDebug() << "Failed to send init packet";
        return -1;
    }

    std::string seq = control->NumberToString(seqNum);
    char * cfg = (char *)malloc((41+seq.length())*sizeof(char));
    memcpy(cfg,"AT*CONFIG=",10);
    memcpy(&cfg[10],seq.data(),seq.length());
    memcpy(&cfg[10+seq.length()],",\"general:navdata_demo\",\"TRUE\"\r",31);

    //char cfg[43]  = "AT*CONFIG=2,\"general:navdata_demo\",\"TRUE\"\r";
    int err = control->write((const char *)cfg,41+seq.length());
    qDebug() << cfg;
    if(err!=0) {
        qDebug() << "Failed to send cfg packet";
        return -1;
    }

    /*char control[12] = "AT*CTRL=3,\r";
    cnt_bytes = cfgSocket->writeDatagram((const char *)control,11,QHostAddress("192.168.1.1"),5556);
    qDebug() << control;
    if(cnt_bytes!=11) {
        qDebug() << "Failed to send control packet";
        return -1;
    }*/

    return 0;
}


int droneNavData::write(const char * data, int size)
{
    qint64 cnt_bytes = writeDatagram(data,size,QHostAddress("192.168.1.1"),5554);

    return cnt_bytes;
}


void droneNavData::slotRead()
{
    int cnt_bytes = 0;
    QHostAddress sender ;
    quint16 senderPort;
    char tab[1024] ;

    while (hasPendingDatagrams())
    {
        cnt_bytes = readDatagram(tab, sizeof(char)*1024, &sender, &senderPort) ;

        qDebug() << "read " << cnt_bytes << " bytes : " << tab;

        //Then emit signals to display altitude, vx, etc...
    }
}
