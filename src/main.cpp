#include <QApplication>
#include <qwt_plot.h>
#include "Window.h"
#include "UdpSocket.h"
#include "Plot.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window window ;
    window.show() ;

    return app.exec();
}


