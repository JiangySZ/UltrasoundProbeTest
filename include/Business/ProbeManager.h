#ifndef PROBE_MANAGER_H
#define PROBE_MANAGER_H

#include <QObject>
#include <QString>
#include <QMap>
#include "Config/ProbeConfig.h"

enum class ProbeState
{
    Unknown,
    Detected,
    Activated,
    Error
};

struct ProbeInfo
{
    QString port;
    QString id;
    QString model;
    QString configPath;
    ProbeState state;
};

class ProbeManager : public QObject
{
    Q_OBJECT

public:
    explicit ProbeManager(QObject* parent = nullptr);
    ~ProbeManager();

    bool isKnownProbe(const QString& probeId) const;
    bool matchConfig(const QString& probeId, ProbeConfig& config);
    void loadKnownProbes(const QString& filePath);

    ProbeInfo getProbeInfo(const QString& port) const;
    QList<ProbeInfo> getAllProbes() const;

signals:
    void probeDetected(const ProbeInfo& info);
    void probeActivated(const ProbeInfo& info);
    void probeError(const QString& port, const QString& error);

private:
    QMap<QString, QString> m_knownProbes;
    QMap<QString, ProbeInfo> m_detectedProbes;
};

#endif // PROBE_MANAGER_H
