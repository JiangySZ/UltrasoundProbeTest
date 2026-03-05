#include <QApplication>
#include <QCoreApplication>
#include <QDebug>

#include "Config/Logger.h"
#include "UI/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("UltrasoundProbeTest");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Wisonic");

    Logger::instance()->init("app.log");
    qCInfo(LOG_MAIN) << "Application started";
    qCInfo(LOG_MAIN) << "Version:" << app.applicationVersion();

    MainWindow window;
    window.show();

    int result = app.exec();

    qCInfo(LOG_MAIN) << "Application exiting";
    Logger::instance()->close();

    return result;
}
