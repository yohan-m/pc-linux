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
    void newNavData(int bat, int state, int pitch, int roll, int yaw, int alt, int vx, int vy, int vz);

public slots:

private slots:
    void slotRead();

};

#endif // DRONENAVDATA_H
