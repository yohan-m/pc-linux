#include <QCoreApplication>
#include "UdpSocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UdpSocket udpSocket ;

    return a.exec();
}


