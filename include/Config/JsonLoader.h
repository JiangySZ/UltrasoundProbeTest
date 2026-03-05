#ifndef JSON_LOADER_H
#define JSON_LOADER_H

#include <QJsonObject>
#include <QString>

class JsonLoader
{
public:
    JsonLoader();

    bool load(const QString& filePath);
    QJsonObject getRoot() const;
    QString errorString() const;
    bool isValid() const;

private:
    QJsonObject m_root;
    QString m_error;
    bool m_valid;
};

#endif // JSON_LOADER_H
