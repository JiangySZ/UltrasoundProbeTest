## ADDED Requirements

### Requirement: PDF report generation
The system SHALL generate a PDF report for each test session with full traceability information.

#### Scenario: Report header
- **WHEN** generating PDF report
- **THEN** report SHALL include:
  - Probe model
  - Probe ID
  - Tester name
  - Test date/time

#### Scenario: Report traceability
- **WHEN** generating PDF report
- **THEN** report SHALL include:
  - Test system serial number (System SN)
  - Test software version (vX.X)

#### Scenario: Report body - trend charts
- **WHEN** generating PDF report
- **THEN** report SHALL include 5 metric line charts:
  - Sensitivity
  - Bandwidth
  - Pulse length
  - Center frequency
  - TOF

#### Scenario: Report conclusion
- **WHEN** generating PDF report
- **THEN** report SHALL include:
  - Overall Pass/Fail conclusion
  - List of failed elements (if any)
  - Note for surface test (indicating sensitivity-only criteria)

#### Scenario: Report format compliance
- **WHEN** generating PDF report
- **THEN** report SHALL comply with FDA Guidance Section 4.5.3 traceability requirements
