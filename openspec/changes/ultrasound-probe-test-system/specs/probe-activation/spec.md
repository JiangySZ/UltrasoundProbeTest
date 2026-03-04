## ADDED Requirements

### Requirement: Activate probe
The system SHALL activate the selected probe by calling the Probe_Activate function.

#### Scenario: Successful probe activation
- **WHEN** user selects a probe port and clicks "Activate"
- **THEN** system SHALL call Probe_Activate and display success message

#### Scenario: Activation failure
- **WHEN** Probe_Activate fails (e.g., hardware error)
- **THEN** system SHALL display an error message with failure reason

### Requirement: Load test script
The system SHALL load the PW mode script using System_LoadScript function.

#### Script: Script loading
- **WHEN** probe is successfully activated
- **THEN** user SHALL be able to load the test script
- **AND** system SHALL enter a frozen/ready state after script loading

#### Scenario: Script load failure
- **WHEN** System_LoadScript fails
- **THEN** system SHALL display error and remain in previous state
