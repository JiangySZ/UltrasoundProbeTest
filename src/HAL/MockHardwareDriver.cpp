#include "HAL/MockHardwareDriver.h"
#include <QDateTime>
#include <cmath>
#include <cstdlib>
#include <ctime>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

MockHardwareDriver::MockHardwareDriver(QObject* parent)
    : HardwareInterface(parent)
    , m_connected(false)
    , m_temperature(25)
    , m_noiseLevel(0.1)
    , m_motorRunning(false)
    , m_motorSpeed(0)
    , m_timestamp(0)
{
    m_waveformType = "sine";
    srand(static_cast<unsigned>(time(nullptr)));
}

MockHardwareDriver::~MockHardwareDriver()
{
    disconnect();
}

bool MockHardwareDriver::initialize()
{
    m_lastError.clear();
    return true;
}

bool MockHardwareDriver::connect()
{
    if (m_connected) {
        m_lastError = "Already connected";
        return false;
    }

    m_connected = true;
    m_timestamp = QDateTime::currentMSecsSinceEpoch();
    emit connected();
    return true;
}

void MockHardwareDriver::disconnect()
{
    if (m_connected) {
        m_connected = false;
        m_motorRunning = false;
        m_motorSpeed = 0;
        emit disconnected();
    }
}

bool MockHardwareDriver::isConnected() const
{
    return m_connected;
}

bool MockHardwareDriver::acquireData(WaveformData& data, int channel)
{
    if (!m_connected) {
        m_lastError = "Not connected";
        return false;
    }

    const int numSamples = 4096;
    const int sampleRate = 40000000;
    const double frequency = 4000000.0;
    const double amplitude = 1.0;
    const double duration = static_cast<double>(numSamples) / sampleRate;

    data.samples.clear();
    data.samples.reserve(numSamples);
    data.sampleRate = sampleRate;
    data.channel = channel;
    data.timestamp = QDateTime::currentMSecsSinceEpoch();

    for (int i = 0; i < numSamples; ++i) {
        double time = static_cast<double>(i) / sampleRate;
        double sineWave = generateSineWave(time, frequency, amplitude);
        double noise = generateNoise(m_noiseLevel);
        data.samples.append(sineWave + noise);
    }

    emit dataAcquired(data);
    return true;
}

bool MockHardwareDriver::readProbeId(QString& probeId)
{
    if (!m_connected) {
        m_lastError = "Not connected";
        return false;
    }

    probeId = "MOCK-PROBE-128E";
    return true;
}

bool MockHardwareDriver::getTemperature(int& temperature)
{
    if (!m_connected) {
        m_lastError = "Not connected";
        return false;
    }

    m_temperature = 25 + (rand() % 5);
    temperature = m_temperature;
    return true;
}

bool MockHardwareDriver::motorStart(int speed)
{
    if (!m_connected) {
        m_lastError = "Not connected";
        return false;
    }

    m_motorRunning = true;
    m_motorSpeed = speed;
    return true;
}

bool MockHardwareDriver::motorStop()
{
    if (!m_connected) {
        m_lastError = "Not connected";
        return false;
    }

    m_motorRunning = false;
    m_motorSpeed = 0;
    return true;
}

QString MockHardwareDriver::lastError() const
{
    return m_lastError;
}

HardwareStatus MockHardwareDriver::status() const
{
    HardwareStatus status;
    status.isConnected = m_connected;
    status.errorMessage = m_lastError;
    status.temperature = m_temperature;
    status.timestamp = m_timestamp;
    return status;
}

void MockHardwareDriver::setWaveformType(const QString& type)
{
    m_waveformType = type;
}

void MockHardwareDriver::setNoiseLevel(double level)
{
    m_noiseLevel = level;
}

double MockHardwareDriver::generateSineWave(double time, double frequency, double amplitude)
{
    return amplitude * std::sin(2.0 * M_PI * frequency * time);
}

double MockHardwareDriver::generateNoise(double amplitude)
{
    return ((rand() % 2000) / 1000.0 - 1.0) * amplitude;
}
