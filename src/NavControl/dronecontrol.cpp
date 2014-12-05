#include "dronecontrol.h"

droneControl::droneControl() : QUdpSocket()
{
    bind(QHostAddress(UDP_ADDR_DRONE),UDP_PORT_DRONE);
    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(slotRead())) ;
}


int droneControl::sendResetWatchdog(int seqNum)
{
    std::string seq = NumberToString(seqNum);

    char * rstw = (char *)malloc((11+seq.length())*sizeof(char));

    memcpy(rstw,"AT*COMWDG=",10);
    memcpy(&rstw[10],seq.data(),seq.length());
    memcpy(&rstw[10+seq.length()],"\r",1);

    //qDebug() << QString(rstw);

    int cnt_bytes = write((const char *)rstw,11+seq.length());

    delete rstw;

    if(cnt_bytes!=(11+(int)seq.length())) {
        qDebug() << "Failed to send reset watchdog";
        return -1;
    }

    return 0;
}

int droneControl::sendEmergency(int seqNum)
{
    std::string seq = NumberToString(seqNum);

    char * reset = (char *)malloc((18+seq.length())*sizeof(char));

    memcpy(reset,"AT*REF=",7);
    memcpy(&reset[7],seq.data(),seq.length());
    memcpy(&reset[7+seq.length()],",290717952\r",11);

    qDebug() << QString(reset);

    int cnt_bytes = write((const char *)reset,18+seq.length());

    delete reset;

    if(cnt_bytes!=(18+(int)seq.length())) {
        qDebug() << "Failed to send emergency";
        return -1;
    }

    return 0;
}


int droneControl::sendCalibHPlan(int seqNum)
{
    std::string seq = NumberToString(seqNum);

    char * calib = (char *)malloc((10+seq.length())*sizeof(char));

    memcpy(calib,"AT*FTRIM=",9);
    memcpy(&calib[9],seq.data(),seq.length());
    memcpy(&calib[9+seq.length()],"\r",1);

    qDebug() << QString(calib);

    int cnt_bytes = write((const char *)calib,10+seq.length());

    delete calib;

    if(cnt_bytes!=(10+(int)seq.length())) {
        qDebug() << "Failed to send calib";
        return -1;
    }

    return 0;
}

int droneControl::sendCalibMagn(int seqNum)
{
    std::string seq = NumberToString(seqNum);

    char * calib = (char *)malloc((12+seq.length())*sizeof(char));

    memcpy(calib,"AT*CALIB=",9);
    memcpy(&calib[9],seq.data(),seq.length());
    memcpy(&calib[9+seq.length()],",0\r",3);

    qDebug() << QString(calib);

    int cnt_bytes = write((const char *)calib,12+seq.length());

    delete calib;

    if(cnt_bytes!=(12+(int)seq.length())) {
        qDebug() << "Failed to send calib";
        return -1;
    }

    return 0;
}


int droneControl::sendTakeOff(int seqNum)
{
    std::string seq = NumberToString(seqNum);

    char * takeoff = (char *)malloc((18+seq.length())*sizeof(char));

    memcpy(takeoff,"AT*REF=",7);
    memcpy(&takeoff[7],seq.data(),seq.length());
    memcpy(&takeoff[7+seq.length()],",290718208\r",11);

    qDebug() << QString(takeoff);

    int cnt_bytes = write((const char *)takeoff,18+seq.length());

    delete takeoff;

    if(cnt_bytes!=(18+(int)seq.length())) {
        qDebug() << "Failed to send take off";
        return -1;
    }

    return 0;
}


int droneControl::sendLand(int seqNum)
{
    std::string seq = NumberToString(seqNum);

    char * land = (char *)malloc((18+seq.length())*sizeof(char));

    memcpy(land,"AT*REF=",7);
    memcpy(&land[7],seq.data(),seq.length());
    memcpy(&land[7+seq.length()],",290717696\r",11);

    qDebug() << QString(land);

    int cnt_bytes = write((const char *)land,18+seq.length());

    delete land;

    if(cnt_bytes!=(18+(int)seq.length())) {
        qDebug() << "Failed to send land";
        return -1;
    }

    return 0;
}


int droneControl::sendMovement(int seqNum, int flag, float leftRightTilt, float frontBackTilt, float verticalSpeed, float angularSpeed)
{
    std::string seq = NumberToString(seqNum);
    std::string cflag = NumberToString(flag);

    int lrTilt_int = *(int*)&leftRightTilt;
    int fbTilt_int = *(int*)&frontBackTilt;
    int vSpeed_int = *(int*)&verticalSpeed;
    int aSpeed_int = *(int*)&angularSpeed;
    std::string lrTilt = NumberToString(lrTilt_int);
    std::string fbTilt = NumberToString(fbTilt_int);
    std::string vSpeed = NumberToString(vSpeed_int);
    std::string aSpeed = NumberToString(aSpeed_int);

    char * move = (char *)malloc((14+seq.length()+cflag.length()+lrTilt.length()+fbTilt.length()+vSpeed.length()+aSpeed.length())*sizeof(char));

    memcpy(move,"AT*PCMD=",8);
    memcpy(&move[8],seq.data(),seq.length());
    memcpy(&move[8+seq.length()],",",1);
    memcpy(&move[9+seq.length()],cflag.data(),cflag.length());
    memcpy(&move[9+seq.length()+cflag.length()],",",1);
    memcpy(&move[10+seq.length()+cflag.length()],lrTilt.data(),lrTilt.length());
    memcpy(&move[10+seq.length()+cflag.length()+lrTilt.length()],",",1);
    memcpy(&move[11+seq.length()+cflag.length()+lrTilt.length()],fbTilt.data(),fbTilt.length());
    memcpy(&move[11+seq.length()+cflag.length()+lrTilt.length()+fbTilt.length()],",",1);
    memcpy(&move[12+seq.length()+cflag.length()+lrTilt.length()+fbTilt.length()],vSpeed.data(),vSpeed.length());
    memcpy(&move[12+seq.length()+cflag.length()+lrTilt.length()+fbTilt.length()+vSpeed.length()],",",1);
    memcpy(&move[13+seq.length()+cflag.length()+lrTilt.length()+fbTilt.length()+vSpeed.length()],aSpeed.data(),aSpeed.length());
    memcpy(&move[13+seq.length()+cflag.length()+lrTilt.length()+fbTilt.length()+vSpeed.length()+aSpeed.length()],"\r",1);

    qDebug() << QString(move);

    int cnt_bytes = write((const char *)move,14+seq.length()+cflag.length()+lrTilt.length()+fbTilt.length()+vSpeed.length()+aSpeed.length());

    delete move;

    if(cnt_bytes!=(14+(int)seq.length()+(int)cflag.length()+(int)lrTilt.length()+(int)fbTilt.length()+(int)vSpeed.length()+(int)aSpeed.length())) {
        qDebug() << "Failed to send land";
        return -1;
    }

    return 0;
}


std::string droneControl::NumberToString (int Number)
{
     std::ostringstream ss;
     ss << Number;
     return ss.str();
}


int droneControl::write(const char * data, int size)
{
    qint64 cnt_bytes = writeDatagram(data,size,QHostAddress(UDP_ADDR_DRONE),UDP_PORT_DRONE);

    return cnt_bytes;
}


void droneControl::slotRead()
{
    QHostAddress sender;
    quint16 senderPort;
    char data[FRAME_MAX_SIZE];

    while (hasPendingDatagrams())
    {
        readDatagram(data, FRAME_MAX_SIZE, &sender, &senderPort);
    }
}

