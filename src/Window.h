#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <qwt_slider.h>
#include "UdpSocket.h"
#include "Plot.h"
#include "NavControl/navcontrolui.h"

/*! \class Window
 *  \brief Main window of the GUI
 *
 *  This class allows to instanciate, organize and update Qwt widgets (a 2D graphical widget and a read-only cursor) used for the display. \n
 *  We can also connect or disconnect from the drone and get the drone's position in real time thanks to an udpSocket attribute.\n
 *
 */
class Window : public QWidget
{
    Q_OBJECT

    public:
        Window() ;
        ~Window() ;


        /*!
         * \brief Center and set the size of the window
         *
         */
        void initWindow() ;

        /*!
         * \brief Instanciate and initialize all widgets
         *
         */
        void initWidgets() ;

        void updateMission();

public slots:

        /*!
         * \brief Create a udp Socket waiting a frame to read
         *
         */
        void connect();

        /*!
         * \brief Delete the udpSocket
         *
         */
        void disconnect();

        /*!
         * \brief Update the display
         *
         * This slot is called each time a frame is read
         * It gets the new position received to update the display
         *
         */
        void update(double x, double y, double z);

        /*!
         * \brief Simulation
         *
         * This slot is called when the button "Simulation Display" is clicked
         * It allows to simulate a real time display by sending a frame with 3D position from localhost
         * each 100ms
         *
         */
        void simu() ;

        void onLaunchMissionClicked() ;
        void onStopMissionClicked() ;
        void onChangeMissionState(char state);
        void onChangeRadioButton();
        void onChangeButtonMissionCarre() ;

        virtual void keyPressEvent(QKeyEvent* event);
        virtual void keyReleaseEvent(QKeyEvent* event);
        void onChangeAltitudeFromBarometer(double alt);

    private:
        //Qt widgets
        QPushButton *buttonConnect ;
        QPushButton *buttonDisconnect ;
        QPushButton *buttonSimu ;
        QPushButton *launchMissionButton ;
        QPushButton *stopMissionButton ;
        QPushButton *buttonMissionCarre ;

        QDoubleSpinBox *spinX ;
        QDoubleSpinBox *spinY ;
        QDoubleSpinBox *spinZ ;
        QDoubleSpinBox *spinAngle ;

        QCheckBox *checkEmmetteur ;
        QRadioButton *radioButtonDrone ;
        QRadioButton *radioButtonPc ;

        QLabel *valueX ;
        QLabel *valueY ;
        QLabel *valueZ ;
        QLabel *stateMissionLabel ;

        //Qwt widgets
        Plot *plot ;
        QwtSlider *slider ;

        //UdpSocket
        UdpSocket *udpSocket ;
        bool socketIsActive ;

        //NavControl
        navControlUI * navControl;

        int numMission ;

};

#endif // WINDOW_H
