#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <QString>
#include <QJsonObject>
#include "Config/ProbeConfig.h"

class ConfigManager
{
public:
    static ConfigManager* instance();

    bool loadProbeConfig(const QString& filePath);
    bool loadWaveformConfig(const QString& filePath);

    ProbeConfig getProbeConfig() const;
    WaveformConfig getWaveformConfig() const;

    QString lastError() const;
    bool isLoaded() const;

private:
    ConfigManager();
    ~ConfigManager();
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    bool parseProbeConfig(const QJsonObject& obj);
    bool parseWaveformConfig(const QJsonObject& obj);

    static ConfigManager* s_instance;
    ProbeConfig m_probeConfig;
    WaveformConfig m_waveformConfig;
    QString m_error;
    bool m_loaded;
};

#endif // CONFIG_MANAGER_H
