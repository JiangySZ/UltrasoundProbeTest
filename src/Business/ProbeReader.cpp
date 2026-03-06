#include "Business/ProbeReader.h"
#include "HAL/HardwareFactory.h"

ProbeReader::ProbeReader(QObject* parent)
    : QObject(parent)
    , m_hardware(nullptr)
{
    m_hardware = HardwareFactory::create(HardwareFactory::Mode::Mock);
    if (m_hardware) {
        m_hardware->initialize();
    }
}

ProbeReader::~ProbeReader()
{
    if (m_hardware) {
        delete m_hardware;
    }
}

bool ProbeReader::readId(const QString& portId, QString& probeId)
{
    Q_UNUSED(portId);

    if (!m_hardware) {
        emit readError("Hardware not initialized");
        return false;
    }

    if (!m_hardware->isConnected()) {
        if (!m_hardware->connect()) {
            emit readError("Failed to connect");
            return false;
        }
    }

    bool result = m_hardware->readProbeId(probeId);
    if (result) {
        emit idRead(probeId);
    } else {
        emit readError(m_hardware->lastError());
    }

    return result;
}

bool ProbeReader::validateIdFormat(const QString& probeId)
{
    if (probeId.isEmpty()) {
        return false;
    }

    if (probeId.length() < 5) {
        return false;
    }

    QRegExp regex("^[A-Z0-9-]+$");
    return regex.exactMatch(probeId);
}

bool ProbeReader::verifyId(const QString& portId, const QString& expectedId)
{
    QString actualId;
    if (!readId(portId, actualId)) {
        return false;
    }

    return actualId == expectedId;
}
