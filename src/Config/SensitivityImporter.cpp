#include "Config/SensitivityImporter.h"
#include <QFile>
#include <QTextStream>

QList<double> SensitivityImporter::import(const QString& filePath)
{
    QList<double> values;
    m_valid = false;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_error = QString("Cannot open file: %1").arg(filePath);
        return values;
    }

    QTextStream in(&file);
    int lineNumber = 0;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        lineNumber++;

        if (line.isEmpty() || line.startsWith("#")) {
            continue;
        }

        bool ok;
        double value = parseLine(line, ok);
        if (!ok) {
            m_error = QString("Invalid number at line %1: %2").arg(lineNumber).arg(line);
            file.close();
            return values;
        }

        values.append(value);
    }

    file.close();

    if (values.isEmpty()) {
        m_error = "No valid values found in file";
        return values;
    }

    m_valid = true;
    m_error.clear();
    return values;
}

double SensitivityImporter::parseLine(const QString& line, bool& ok)
{
    ok = false;
    QString trimmed = line.trimmed();
    if (trimmed.isEmpty()) {
        return 0.0;
    }

    bool success;
    double value = trimmed.toDouble(&success);
    if (!success) {
        return 0.0;
    }

    ok = true;
    return value;
}

QString SensitivityImporter::lastError() const
{
    return m_error;
}

bool SensitivityImporter::isValid() const
{
    return m_valid;
}
