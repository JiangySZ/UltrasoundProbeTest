#include "Business/ProbeManager.h"
#include "Config/ConfigManager.h"

ProbeManager::ProbeManager(QObject* parent)
    : QObject(parent)
{
    m_knownProbes.insert("MOCK-PROBE-128E", "config/ProbeConfig.json");
}

ProbeManager::~ProbeManager()
{
}

bool ProbeManager::isKnownProbe(const QString& probeId) const
{
    return m_knownProbes.contains(probeId);
}

bool ProbeManager::matchConfig(const QString& probeId, ProbeConfig& config)
{
    if (!isKnownProbe(probeId)) {
        return false;
    }

    QString configPath = m_knownProbes.value(probeId);
    ConfigManager* cm = ConfigManager::instance();
    
    if (cm->loadProbeConfig(configPath)) {
        config = cm->getProbeConfig();
        return true;
    }

    return false;
}

void ProbeManager::loadKnownProbes(const QString& filePath)
{
    Q_UNUSED(filePath);
}

ProbeInfo ProbeManager::getProbeInfo(const QString& port) const
{
    return m_detectedProbes.value(port);
}

QList<ProbeInfo> ProbeManager::getAllProbes() const
{
    return m_detectedProbes.values();
}
