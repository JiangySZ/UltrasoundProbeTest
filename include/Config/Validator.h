#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <QList>
#include "Config/ProbeConfig.h"

struct ValidationError {
    QString field;
    QString message;
};

struct ValidationResult {
    bool isValid;
    QList<ValidationError> errors;
    QList<QString> warnings;
};

class Validator
{
public:
    ValidationResult validate(const ProbeConfig& config);
    ValidationResult validate(const WaveformConfig& config);

private:
    ValidationResult validateProbe(const ProbeConfig::Probe& probe);
    ValidationResult validateTest(const ProbeConfig::Test& test);
    ValidationResult validateThresholds(const ProbeConfig::Thresholds& thresholds);
};

#endif // VALIDATOR_H
