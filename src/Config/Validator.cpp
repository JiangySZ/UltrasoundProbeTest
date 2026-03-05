#include "Config/Validator.h"

ValidationResult Validator::validate(const ProbeConfig& config)
{
    ValidationResult result;
    result.isValid = true;

    ValidationResult probeResult = validateProbe(config.probe);
    if (!probeResult.isValid) {
        result.isValid = false;
        result.errors.append(probeResult.errors);
    }

    ValidationResult testResult = validateTest(config.test);
    if (!testResult.isValid) {
        result.isValid = false;
        result.errors.append(testResult.errors);
    }

    ValidationResult thresholdResult = validateThresholds(config.thresholds);
    if (!thresholdResult.isValid) {
        result.isValid = false;
        result.errors.append(thresholdResult.errors);
    }

    return result;
}

ValidationResult Validator::validate(const WaveformConfig& config)
{
    ValidationResult result;
    result.isValid = true;

    if (config.waveform.name.isEmpty()) {
        result.isValid = false;
        result.errors.append({"waveform.name", "Waveform name is required"});
    }

    if (config.waveform.txVoltage <= 0) {
        result.isValid = false;
        result.errors.append({"waveform.txVoltage", "TX Voltage must be positive"});
    }

    if (config.waveform.frequency <= 0) {
        result.isValid = false;
        result.errors.append({"waveform.frequency", "Frequency must be positive"});
    }

    return result;
}

ValidationResult Validator::validateProbe(const ProbeConfig::Probe& probe)
{
    ValidationResult result;
    result.isValid = true;

    if (probe.id.isEmpty()) {
        result.isValid = false;
        result.errors.append({"probe.id", "Probe ID is required"});
    }

    if (probe.elements <= 0) {
        result.isValid = false;
        result.errors.append({"probe.elements", "Number of elements must be positive"});
    }

    if (probe.frequency <= 0) {
        result.isValid = false;
        result.errors.append({"probe.frequency", "Frequency must be positive"});
    }

    return result;
}

ValidationResult Validator::validateTest(const ProbeConfig::Test& test)
{
    ValidationResult result;
    result.isValid = true;

    if (test.adcRatio <= 0) {
        result.isValid = false;
        result.errors.append({"test.adcRatio", "ADC Ratio must be positive"});
    }

    return result;
}

ValidationResult Validator::validateThresholds(const ProbeConfig::Thresholds& thresholds)
{
    ValidationResult result;
    result.isValid = true;

    if (thresholds.sensitivity.nominal == 0 && thresholds.sensitivity.tolerance == 0) {
        result.warnings.append("Sensitivity thresholds not set");
    }

    if (thresholds.centerFrequency.nominal == 0 && thresholds.centerFrequency.tolerance == 0) {
        result.warnings.append("Center frequency thresholds not set");
    }

    return result;
}
