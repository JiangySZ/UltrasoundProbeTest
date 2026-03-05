#include "Config/ConfigManager.h"
#include "Config/JsonLoader.h"
#include <QJsonArray>

ConfigManager* ConfigManager::s_instance = nullptr;

ConfigManager::ConfigManager()
    : m_loaded(false)
{
}

ConfigManager::~ConfigManager()
{
}

ConfigManager* ConfigManager::instance()
{
    if (!s_instance) {
        s_instance = new ConfigManager();
    }
    return s_instance;
}

bool ConfigManager::loadProbeConfig(const QString& filePath)
{
    JsonLoader loader;
    if (!loader.load(filePath)) {
        m_error = loader.errorString();
        return false;
    }

    QJsonObject root = loader.getRoot();
    if (!root.contains("probe")) {
        m_error = "Missing 'probe' section";
        return false;
    }

    return parseProbeConfig(root);
}

bool ConfigManager::loadWaveformConfig(const QString& filePath)
{
    JsonLoader loader;
    if (!loader.load(filePath)) {
        m_error = loader.errorString();
        return false;
    }

    QJsonObject root = loader.getRoot();
    if (!root.contains("waveform")) {
        m_error = "Missing 'waveform' section";
        return false;
    }

    return parseWaveformConfig(root);
}

bool ConfigManager::parseProbeConfig(const QJsonObject& obj)
{
    QJsonObject probe = obj.value("probe").toObject();
    m_probeConfig.probe.id = probe.value("id").toString();
    m_probeConfig.probe.model = probe.value("model").toString();
    m_probeConfig.probe.type = probe.value("type").toString();
    m_probeConfig.probe.elements = probe.value("elements").toInt(0);
    m_probeConfig.probe.frequency = probe.value("frequency").toDouble(0.0);

    QJsonObject test = obj.value("test").toObject();
    m_probeConfig.test.startDepth = test.value("startDepth").toDouble(0.0);
    m_probeConfig.test.adcRatio = test.value("adcRatio").toDouble(1.0);

    QJsonArray excludeArr = test.value("excludeElements").toArray();
    for (int i = 0; i < excludeArr.size(); ++i) {
        m_probeConfig.test.excludeElements.append(excludeArr[i].toInt());
    }

    QJsonArray calArr = test.value("calibrationElements").toArray();
    for (int i = 0; i < calArr.size(); ++i) {
        m_probeConfig.test.calibrationElements.append(calArr[i].toInt());
    }

    QJsonObject thresholds = obj.value("thresholds").toObject();
    m_probeConfig.thresholds.sensitivity.nominal = thresholds.value("sensitivity").toObject().value("nominal").toDouble(0.0);
    m_probeConfig.thresholds.sensitivity.tolerance = thresholds.value("sensitivity").toObject().value("tolerance").toDouble(0.0);
    m_probeConfig.thresholds.centerFrequency.nominal = thresholds.value("centerFrequency").toObject().value("nominal").toDouble(0.0);
    m_probeConfig.thresholds.centerFrequency.tolerance = thresholds.value("centerFrequency").toObject().value("tolerance").toDouble(0.0);
    m_probeConfig.thresholds.bandwidth6dB.nominal = thresholds.value("bandwidth6dB").toObject().value("nominal").toDouble(0.0);
    m_probeConfig.thresholds.bandwidth6dB.tolerance = thresholds.value("bandwidth6dB").toObject().value("tolerance").toDouble(0.0);
    m_probeConfig.thresholds.bandwidth20dB.nominal = thresholds.value("bandwidth20dB").toObject().value("nominal").toDouble(0.0);
    m_probeConfig.thresholds.bandwidth20dB.tolerance = thresholds.value("bandwidth20dB").toObject().value("tolerance").toDouble(0.0);
    m_probeConfig.thresholds.pulseLength20dB.nominal = thresholds.value("pulseLength20dB").toObject().value("nominal").toDouble(0.0);
    m_probeConfig.thresholds.pulseLength20dB.tolerance = thresholds.value("pulseLength20dB").toObject().value("tolerance").toDouble(0.0);

    m_probeConfig.sensitivityList = obj.value("sensitivityList").toString();

    m_loaded = true;
    return true;
}

bool ConfigManager::parseWaveformConfig(const QJsonObject& obj)
{
    QJsonObject waveform = obj.value("waveform").toObject();
    m_waveformConfig.waveform.name = waveform.value("name").toString();
    m_waveformConfig.waveform.type = waveform.value("type").toString();
    m_waveformConfig.waveform.txVoltage = waveform.value("txVoltage").toDouble(0.0);
    m_waveformConfig.waveform.frequency = waveform.value("frequency").toDouble(0.0);
    m_waveformConfig.waveform.cycles = waveform.value("cycles").toInt(0);

    QJsonArray pointsArr = waveform.value("points").toArray();
    for (int i = 0; i < pointsArr.size(); ++i) {
        m_waveformConfig.waveform.points.append(pointsArr[i].toDouble(0.0));
    }

    m_loaded = true;
    return true;
}

ProbeConfig ConfigManager::getProbeConfig() const
{
    return m_probeConfig;
}

WaveformConfig ConfigManager::getWaveformConfig() const
{
    return m_waveformConfig;
}

QString ConfigManager::lastError() const
{
    return m_error;
}

bool ConfigManager::isLoaded() const
{
    return m_loaded;
}
