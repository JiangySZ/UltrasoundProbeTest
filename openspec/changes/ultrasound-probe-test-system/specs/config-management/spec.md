## ADDED Requirements

### Requirement: Probe configuration management
The system SHALL manage probe configurations stored in JSON format (ProbeConfig.json).

#### Scenario: Load probe configuration
- **WHEN** known probe is detected
- **THEN** system SHALL automatically load corresponding configuration from ProbeConfig.json

#### Scenario: Configuration parameters
- **WHEN** loading probe configuration
- **THEN** system SHALL read:
  - ID (probe identifier)
  - StartDepth (test start depth)
  - ADCRatio (voltage conversion ratio)
  - SensitivityList (sensitivity thresholds)
  - Standard thresholds (frequency, bandwidth, pulse length at -6dB and -20dB)
  - ExcludeElements (elements to skip during testing)

#### Scenario: Import sensitivity list
- **WHEN** user imports sensitivity list from TXT file
- **THEN** system SHALL parse TXT file and update SensitivityList in configuration

### Requirement: Waveform configuration management
The system SHALL manage waveform configurations stored in JSON format (WaveformConfig.json).

#### Scenario: Load waveform configuration
- **WHEN** loading test parameters
- **THEN** system SHALL read waveform configuration from WaveformConfig.json

#### Scenario: Waveform configuration parameters
- **WHEN** loading waveform configuration
- **THEN** system SHALL read:
  - TxVoltage (transmit voltage)
  - Type (Pulser or Arbitrary)
  - DataPoints (waveform data for arbitrary type)
