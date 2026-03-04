## ADDED Requirements

### Requirement: Motor control
The system SHALL provide UI controls for motor start/stop operations.

#### Scenario: Motor start
- **WHEN** user clicks "Motor Start" button
- **THEN** system SHALL send start command to motor
- **AND** display motor status as "Running"

#### Scenario: Motor stop
- **WHEN** user clicks "Motor Stop" button
- **THEN** system SHALL send stop command to motor
- **AND** display motor status as "Stopped"

#### Scenario: Motor status display
- **WHEN** motor state changes
- **THEN** system SHALL update UI to reflect current motor status
