## ADDED Requirements

### Requirement: Probe calibration
The system SHALL perform probe calibration for standard echo test when StartDepth > 0.

#### Scenario: Calibration element selection
- **WHEN** calibration is required
- **THEN** system SHALL select 3 elements specified in configuration

#### Scenario: Calibration waveform acquisition
- **WHEN** performing calibration
- **THEN** system SHALL excite and acquire waveforms from 3 selected elements
- **AND** overlay display the 3 waveforms for visual comparison

#### Scenario: Calibration confirmation
- **WHEN** calibration waveforms are displayed
- **THEN** system SHALL wait for user confirmation
- **AND** user SHALL verify waveform consistency before proceeding

#### Scenario: Calibration pass criteria
- **WHEN** user confirms calibration
- **THEN** system SHALL proceed with full element scanning

#### Scenario: Calibration fail - waveforms inconsistent
- **WHEN** user rejects calibration due to inconsistent waveforms
- **THEN** system SHALL display error and allow retry
