QT += widgets network svg

CONFIG += qwt

INCLUDEPATH += ../../common-sources/src \
               /usr/local/qwt-6.1.1/include

DEPENDPATH +=  /usr/local/qwt-6.1.1/lib

LIBS += -L/usr/local/qwt-6.1.1/lib -lqwt

HEADERS += \
    UdpSocket.h \
    Window.h \
    Plot.h \
    NavControl/dronecontrol.h \
    NavControl/dronenavdata.h \
    NavControl/navcontrolui.h \
    struct.h \
    NavControl/qfi_ADI.h \
    NavControl/qfi_ASI.h \
    NavControl/qfi_HSI.h

SOURCES += \
    UdpSocket.cpp \
    ../../common-sources/src/wifiFrame.cpp \
    main.cpp \
    Window.cpp \
    Plot.cpp \
    NavControl/dronecontrol.cpp \
    NavControl/dronenavdata.cpp \
    NavControl/navcontrolui.cpp \
    NavControl/qfi_ADI.cpp \
    NavControl/qfi_ASI.cpp \
    NavControl/qfi_HSI.cpp

RESOURCES += \
    NavControl/img.qrc
