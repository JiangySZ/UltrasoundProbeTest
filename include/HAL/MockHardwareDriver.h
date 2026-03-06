#ifndef MOCK_HARDWARE_DRIVER_H
#define MOCK_HARDWARE_DRIVER_H

#include "HAL/HardwareInterface.h"

class MockHardwareDriver : public HardwareInterface
{
    Q_OBJECT

public:
    explicit MockHardwareDriver(QObject* parent = nullptr);
    ~MockHardwareDriver();

    bool initialize() override;
    bool connect() override;
    void disconnect() override;
    bool isConnected() const override;

    bool acquireData(WaveformData& data, int channel = 0) override;
    bool readProbeId(QString& probeId) override;
    bool getTemperature(int& temperature) override;
    bool motorStart(int speed) override;
    bool motorStop() override;

    QString lastError() const override;
    HardwareStatus status() const override;

    void setWaveformType(const QString& type);
    void setNoiseLevel(double level);

private:
    double generateSineWave(double time, double frequency, double amplitude);
    double generateNoise(double amplitude);

    bool m_connected;
    QString m_lastError;
    int m_temperature;
    QString m_waveformType;
    double m_noiseLevel;
    bool m_motorRunning;
    int m_motorSpeed;
    quint64 m_timestamp;
};

#endif // MOCK_HARDWARE_DRIVER_H
