#ifndef DRONENAVDATA_H
#define DRONENAVDATA_H

#include <QUdpSocket>
#include <QDebug>
#include <QThread>
#include <string>
#include <QDebug>
#include "dronecontrol.h"

class droneNavData : public QUdpSocket
{
    Q_OBJECT
public:
    droneNavData(droneControl *control_init);
    int init(int seqNum);

private:
    int write(const char * data, int size);
    droneControl * control;

signals:
    void newBat(int bat);
    void newState(int state);
    void newAlt(int alt);
    void newPitch(int pitch);
    void newRoll(int roll);
    void newYaw(int yaw);
    void newVx(int vx);
    void newVy(int vy);
    void newVz(int vz);

public slots:

private slots:
    void slotRead();

};

#endif // DRONENAVDATA_H
