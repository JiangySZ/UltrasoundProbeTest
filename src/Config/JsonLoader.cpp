#include "Config/JsonLoader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>

JsonLoader::JsonLoader()
    : m_valid(false)
{
}

bool JsonLoader::load(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_error = QString("Cannot open file: %1").arg(filePath);
        m_valid = false;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        m_error = QString("JSON parse error: %1").arg(parseError.errorString());
        m_valid = false;
        return false;
    }

    if (!doc.isObject()) {
        m_error = "Root element must be an object";
        m_valid = false;
        return false;
    }

    m_root = doc.object();
    m_valid = true;
    m_error.clear();
    return true;
}

QJsonObject JsonLoader::getRoot() const
{
    return m_root;
}

QString JsonLoader::errorString() const
{
    return m_error;
}

bool JsonLoader::isValid() const
{
    return m_valid;
}
