#ifndef SENSITIVITY_IMPORTER_H
#define SENSITIVITY_IMPORTER_H

#include <QString>
#include <QList>

class SensitivityImporter
{
public:
    QList<double> import(const QString& filePath);
    QString lastError() const;
    bool isValid() const;

private:
    double parseLine(const QString& line, bool& ok);
    QString m_error;
    bool m_valid;
};

#endif // SENSITIVITY_IMPORTER_H
