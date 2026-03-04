## ADDED Requirements

### Requirement: Standard echo test mode
The system SHALL support standard echo test mode for full QC verification following ACR/FDA guidelines.

#### Scenario: Start standard echo test
- **WHEN** user selects "Standard Echo Test" mode and enters tester name
- **THEN** system SHALL start testing with start depth from configuration (StartDepth)
- **AND** if StartDepth > 0, system SHALL perform calibration first

#### Scenario: Standard test pass/fail criteria
- **WHEN** standard echo test completes
- **THEN** system SHALL evaluate ALL metrics for pass/fail:
  - Sensitivity
  - Center frequency
  - Bandwidth (-6dB and -20dB)
  - Pulse length (-6dB and -20dB)
  - Short circuit detection

#### Scenario: Full metrics display
- **WHEN** standard echo test completes
- **THEN** system SHALL display 5 trend charts:
  - Sensitivity
  - Bandwidth
  - Pulse length
  - Center frequency
  - TOF (Time of Flight)
