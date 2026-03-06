#ifndef PROBE_READER_H
#define PROBE_READER_H

#include <QObject>
#include <QString>
#include "HAL/HardwareInterface.h"

class ProbeReader : public QObject
{
    Q_OBJECT

public:
    explicit ProbeReader(QObject* parent = nullptr);
    ~ProbeReader();

    bool readId(const QString& portId, QString& probeId);
    bool validateIdFormat(const QString& probeId);
    bool verifyId(const QString& portId, const QString& expectedId);

signals:
    void idRead(const QString& probeId);
    void readError(const QString& error);

private:
    HardwareInterface* m_hardware;
};

#endif // PROBE_READER_H
