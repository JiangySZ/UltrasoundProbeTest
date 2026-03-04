## ADDED Requirements

### Requirement: Surface echo test mode
The system SHALL support surface echo test mode for quick probe sensitivity verification.

#### Scenario: Start surface echo test
- **WHEN** user selects "Surface Echo Test" mode and enters tester name
- **THEN** system SHALL start testing with fixed start depth of -0.5 mm
- **AND** system SHALL skip calibration step

#### Scenario: Surface test sensitivity calculation
- **WHEN** performing surface echo test
- **THEN** system SHALL calculate sensitivity using formula: dB = 20*log10(Vpeak/Vtx)

#### Scenario: Surface test pass/fail criteria
- **WHEN** surface echo test completes
- **THEN** system SHALL evaluate only sensitivity against pass/fail criteria
- **AND** system SHALL display bandwidth, pulse length, and TOF as reference values (not for pass/fail)

#### Scenario: Surface test result display
- **WHEN** surface echo test completes
- **THEN** system SHALL show real-time waveform and sensitivity trend chart
