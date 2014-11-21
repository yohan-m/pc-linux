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

/**
 * @class droneControl
 * @brief Control the drone (takeoff/land/movements/emergency/calibrate), send AT-Command on port 5556.
 */
class droneControl : public QUdpSocket
{
    Q_OBJECT

public:
    droneControl();

    /**
     * @brief Write data on port 5556
     * @param data
     * @param size
     * @return
     */
    int write(const char * data, int size);

    /**
     * @brief Convert an int to a string
     * @param Number
     * @return
     */
    std::string NumberToString (int Number);

    /**
     * @brief Reset the communication watchdog
     * @param seqNum
     * @return
     */
    int sendResetWatchdog(int seqNum);

    /**
     * @brief Send en emergency packet to the drone
     * @param seqNum
     * @return
     */
    int sendEmergency(int seqNum);

    /**
     * @brief Calibrate the horizontal plan of the drone (the drone must be landed)
     * @param seqNum
     * @return
     */
    int sendCalibHPlan(int seqNum);

    /**
     * @brief Calibrate the magnetometer (the drone must be flying)
     * @param seqNum
     * @return
     */
    int sendCalibMagn(int seqNum);

    /**
     * @brief Take off
     * @param seqNum
     * @return
     */
    int sendTakeOff(int seqNum);

    /**
     * @brief Land
     * @param seqNum
     * @return
     */
    int sendLand(int seqNum);

    /**
     * @brief Move the drone
     * @param seqNum
     * @param flag
     * @param leftRightTilt
     * @param frontBackTilt
     * @param verticalSpeed
     * @param angularSpeed
     * @return
     */
    int sendMovement(int seqNum, int flag, float leftRightTilt, float frontBackTilt, float verticalSpeed, float angularSpeed);

private:

signals:

public slots:

private slots:
    void slotRead();

};

#endif // UDPDRONE_H
