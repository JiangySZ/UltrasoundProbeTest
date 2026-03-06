#ifndef SCRIPT_LOADER_H
#define SCRIPT_LOADER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "HAL/HardwareInterface.h"

enum class ActivationResult
{
    Success,
    Failed,
    Timeout,
    InvalidScript
};

struct ScriptInfo
{
    QString name;
    QString path;
    QString version;
    QStringList parameters;
};

class ScriptLoader : public QObject
{
    Q_OBJECT

public:
    explicit ScriptLoader(QObject* parent = nullptr);
    ~ScriptLoader();

    bool loadScript(const QString& scriptPath, ScriptInfo& info);
    bool validateScript(const ScriptInfo& script);
    ActivationResult activateProbe(const QString& port, const QString& scriptPath);

    QString lastError() const;

signals:
    void scriptLoaded(const ScriptInfo& script);
    void activationStarted(const QString& port);
    void activationCompleted(const QString& port, ActivationResult result);
    void activationProgress(int percent);

private:
    HardwareInterface* m_hardware;
    QString m_lastError;
};

#endif // SCRIPT_LOADER_H
