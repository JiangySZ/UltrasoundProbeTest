## ADDED Requirements

### Requirement: Write probe ID
The system SHALL write a unique ID to the probe's EEPROM and verify the write operation.

#### Scenario: Write new ID
- **WHEN** user selects "Burn ID" and enters a new ID
- **THEN** system SHALL write the ID to EEPROM
- **AND** system SHALL read back the ID for verification

#### Scenario: Write verification success
- **WHEN** written ID matches the requested ID
- **THEN** system SHALL display success message

#### Scenario: Write verification failure
- **WHEN** written ID does not match requested ID
- **THEN** system SHALL display failure message
- **AND** allow retry of the write operation
