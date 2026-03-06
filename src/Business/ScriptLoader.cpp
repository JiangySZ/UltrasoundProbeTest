#include "Business/ScriptLoader.h"
#include "HAL/HardwareFactory.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ScriptLoader::ScriptLoader(QObject* parent)
    : QObject(parent)
{
    m_hardware = HardwareFactory::create(HardwareFactory::Mode::Mock);
    if (m_hardware) {
        m_hardware->initialize();
    }
}

ScriptLoader::~ScriptLoader()
{
    if (m_hardware) {
        delete m_hardware;
    }
}

QString ScriptLoader::lastError() const
{
    return m_lastError;
}

bool ScriptLoader::loadScript(const QString& scriptPath, ScriptInfo& info)
{
    QFile file(scriptPath);
    if (!file.open(QIODevice::ReadOnly)) {
        m_lastError = "Cannot open script file: " + scriptPath;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        m_lastError = "Invalid script JSON format";
        return false;
    }

    QJsonObject obj = doc.object();
    info.name = obj.value("name").toString();
    info.path = scriptPath;
    info.version = obj.value("version").toString("1.0");

    QJsonArray params = obj.value("parameters").toArray();
    for (int i = 0; i < params.size(); ++i) {
        info.parameters.append(params[i].toString());
    }

    emit scriptLoaded(info);
    return true;
}

bool ScriptLoader::validateScript(const ScriptInfo& script)
{
    if (script.name.isEmpty()) {
        m_lastError = "Script name is empty";
        return false;
    }

    if (script.path.isEmpty()) {
        m_lastError = "Script path is empty";
        return false;
    }

    return true;
}

ActivationResult ScriptLoader::activateProbe(const QString& port, const QString& scriptPath)
{
    Q_UNUSED(port);

    ScriptInfo script;
    if (!loadScript(scriptPath, script)) {
        return ActivationResult::InvalidScript;
    }

    if (!validateScript(script)) {
        return ActivationResult::InvalidScript;
    }

    emit activationStarted(port);

    if (!m_hardware->connect()) {
        m_lastError = "Failed to connect hardware";
        return ActivationResult::Failed;
    }

    bool motorResult = m_hardware->motorStart(100);
    if (!motorResult) {
        m_lastError = "Failed to start motor";
        return ActivationResult::Failed;
    }

    emit activationProgress(100);
    emit activationCompleted(port, ActivationResult::Success);

    return ActivationResult::Success;
}
