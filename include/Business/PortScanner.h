#ifndef PORT_SCANNER_H
#define PORT_SCANNER_H

#include <QObject>
#include <QString>
#include <QList>
#include "HAL/HardwareInterface.h"

enum class ProbePortStatus
{
    Connected,
    Disconnected,
    Error
};

struct ProbePort
{
    QString id;
    ProbePortStatus status;
    QString probeId;
};

class PortScanner : public QObject
{
    Q_OBJECT

public:
    explicit PortScanner(QObject* parent = nullptr);
    ~PortScanner();

    QList<ProbePort> scan();
    ProbePort checkPort(const QString& portId);

    static QStringList availablePorts();

signals:
    void portScanned(const ProbePort& port);
    void scanCompleted(int foundCount);
    void errorOccurred(const QString& error);

private:
    HardwareInterface* m_hardware;
};

#endif
