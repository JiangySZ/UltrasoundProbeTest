## ADDED Requirements

### Requirement: Automated element scanning
The system SHALL automatically scan all valid probe elements (excluding those in ExcludeElements list).

#### Scenario: Element scanning workflow
- **WHEN** test mode is started
- **THEN** system SHALL iterate through all elements except excluded ones
- **AND** for each element: excite single element -> gated acquisition -> voltage conversion (Raw * ADCRatio)

#### Scenario: DSP analysis - sensitivity
- **WHEN** acquiring element data
- **THEN** system SHALL calculate sensitivity: dB = 20*log10(Vpeak/Vtx)

#### Scenario: DSP analysis - frequency domain
- **WHEN** acquiring element data
- **THEN** system SHALL calculate:
  - Center frequency (-6dB)
  - Bandwidth (-6dB and -20dB)

#### Scenario: DSP analysis - time domain
- **WHEN** acquiring element data
- **THEN** system SHALL calculate:
  - Pulse length at -6dB and -20dB thresholds

#### Scenario: DSP analysis - TOF
- **WHEN** acquiring element data
- **THEN** system SHALL calculate Time of Flight using first element's main peak polarity as reference

#### Scenario: Short circuit detection
- **WHEN** scanning each element
- **THEN** system SHALL calculate correlation coefficient with 5 neighboring elements
- **AND** flag element as short circuit if correlation exceeds threshold

#### Scenario: Real-time UI update
- **WHEN** scanning elements
- **THEN** system SHALL update waveform display in real-time
- **AND** update 5 trend charts (sensitivity/bandwidth/pulse/frequency/TOF) progressively
