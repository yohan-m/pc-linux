#ifndef UDPDRONE_H
#define UDPDRONE_H

#include <QUdpSocket>
#include <QDebug>
#include <string>
#include <sstream>
#include <cstdio>

#define UDP_PORT_DRONE 5556
#define UDP_ADDR_DRONE "192.168.1.1"
#define FRAME_MAX_SIZE 1024

class droneControl : public QUdpSocket
{
    Q_OBJECT

public:
    droneControl();
    int write(const char * data, int size);
    std::string NumberToString (int Number);
    std::string NumberToString (float Number);

private:

signals:

public slots:
    int sendResetWatchdog(int seqNum);
    int sendEmergency(int seqNum);
    int sendCalib(int seqNum);
    int sendTakeOff(int seqNum);
    int sendLand(int seqNum);
    int sendMovement(int seqNum, int flag, float leftRightTilt, float frontBackTilt, float verticalSpeed, float angularSpeed);

private slots:
    void slotRead();

};

#endif // UDPDRONE_H
