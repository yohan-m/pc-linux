#ifndef DRONENAVDATA_H
#define DRONENAVDATA_H

#include <QUdpSocket>
#include <QDebug>
#include <QThread>
#include <string>
#include <QDebug>
#include "dronecontrol.h"

/**
 * @class droneNavData
 * @brief Manages the navData on port 5554
 */
class droneNavData : public QUdpSocket
{
    Q_OBJECT
public:
    /**
     * @brief droneNavData
     * @param control_init Necessary to send init command on the port 5556.
     */
    droneNavData(droneControl *control_init);

    /**
     * @brief Init the NavData (get periodic NavData)
     * @param seqNum
     * @return
     */
    int init(int seqNum);

private:
    int write(const char * data, int size);
    droneControl * control;

signals:

    /**
     * @brief Signal emitted each time NavData are received
     * @param bat
     * @param state
     * @param pitch
     * @param roll
     * @param yaw
     * @param alt
     * @param vx
     * @param vy
     * @param vz
     */
    void newNavData(int bat, int state, int pitch, int roll, int yaw, double alt, int vx, int vy, int vz);

public slots:

private slots:
    void slotRead();

};

#endif // DRONENAVDATA_H
