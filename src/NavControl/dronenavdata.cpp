#include "dronenavdata.h"
#include "struct.h"

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

    int err = control->write((const char *)cfg,41+seq.length());
    qDebug() << cfg;
    if(err!=(41+seq.length())) {
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
    QHostAddress sender ;
    quint16 senderPort;
    QByteArray datagram;


    while (hasPendingDatagrams())
    {
        datagram.resize(pendingDatagramSize());

        readDatagram(datagram.data(), datagram.size(), &sender, &senderPort) ;

        Navdata *nav = (Navdata*) datagram.data() ;
        NavdataDemo *navdataDemo = (NavdataDemo*) &nav->options[0] ;

        emit newBat(navdataDemo->vbat) ;
        emit newState(navdataDemo->ctrl_state) ;
        emit newAlt(navdataDemo->altitude/10);
        emit newPitch(navdataDemo->theta/1000);
        emit newRoll(navdataDemo->phi/1000);
        emit newYaw(navdataDemo->psi/1000);
        emit newVx(navdataDemo->vx);
        emit newVy(navdataDemo->vy);
        emit newVz(navdataDemo->vz);
    }
}
