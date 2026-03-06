#include "Business/PortScanner.h"
#include "HAL/HardwareFactory.h"

PortScanner::PortScanner(QObject* parent)
    : QObject(parent)
    , m_hardware(nullptr)
{
    m_hardware = HardwareFactory::create(HardwareFactory::Mode::Mock);
    if (m_hardware) {
        m_hardware->initialize();
    }
}

PortScanner::~PortScanner()
{
    if (m_hardware) {
        delete m_hardware;
    }
}

QStringList PortScanner::availablePorts()
{
    return QStringList() << "A" << "B" << "C" << "D";
}

QList<ProbePort> PortScanner::scan()
{
    QList<ProbePort> result;
    QStringList ports = availablePorts();

    for (const QString& portId : ports) {
        ProbePort port = checkPort(portId);
        result.append(port);
        emit portScanned(port);
    }

    int connectedCount = 0;
    for (const ProbePort& p : result) {
        if (p.status == ProbePortStatus::Connected) {
            connectedCount++;
        }
    }

    emit scanCompleted(connectedCount);
    return result;
}

ProbePort PortScanner::checkPort(const QString& portId)
{
    ProbePort port;
    port.id = portId;
    port.status = ProbePortStatus::Disconnected;
    port.probeId = QString();

    if (!m_hardware) {
        emit errorOccurred("Hardware not initialized");
        return port;
    }

    if (m_hardware->isConnected()) {
        QString probeId;
        if (m_hardware->readProbeId(probeId)) {
            port.status = ProbePortStatus::Connected;
            port.probeId = probeId;
        }
    } else {
        if (m_hardware->connect()) {
            QString probeId;
            if (m_hardware->readProbeId(probeId)) {
                port.status = ProbePortStatus::Connected;
                port.probeId = probeId;
            }
        }
    }

    return port;
}
