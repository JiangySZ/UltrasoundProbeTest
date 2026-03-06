#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>

struct Port
{
    QString id;
    QString name;
    QString type;
    bool isConnected;
};

struct HardwareStatus
{
    bool isConnected;
    QString errorMessage;
    int temperature;
    quint64 timestamp;
};

struct WaveformData
{
    QVector<double> samples;
    int sampleRate;
    int channel;
    quint64 timestamp;
};

class HardwareInterface : public QObject
{
    Q_OBJECT

public:
    explicit HardwareInterface(QObject* parent = nullptr);
    virtual ~HardwareInterface();

    virtual bool initialize() = 0;
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;

    virtual bool acquireData(WaveformData& data, int channel = 0) = 0;
    virtual bool readProbeId(QString& probeId) = 0;
    virtual bool getTemperature(int& temperature) = 0;
    virtual bool motorStart(int speed) = 0;
    virtual bool motorStop() = 0;

    virtual QString lastError() const = 0;
    virtual HardwareStatus status() const = 0;

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& error);
    void dataAcquired(const WaveformData& data);
};

#endif // HARDWARE_INTERFACE_H
