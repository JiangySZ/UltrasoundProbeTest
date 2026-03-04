## ADDED Requirements

### Requirement: Scan probe ports
The system SHALL scan ports A/B/C/D to detect connected probes automatically on application startup.

#### Scenario: Probes detected on multiple ports
- **WHEN** application starts and probes are connected to multiple ports
- **THEN** system SHALL display all detected probe IDs with their corresponding port labels

#### Scenario: No probes connected
- **WHEN** application starts and no probes are connected
- **THEN** system SHALL display a message indicating no probes detected

### Requirement: Read probe ID
The system SHALL read the unique identifier from each connected probe.

#### Scenario: Known probe detected
- **WHEN** a probe with matching ID is found in ProbeConfig.json
- **THEN** system SHALL automatically load the corresponding probe configuration

#### Scenario: Unknown probe detected
- **WHEN** a probe with unknown ID is found (not in ProbeConfig.json)
- **THEN** system SHALL prompt user to either burn a new ID or use temporary configuration

### Requirement: Display probe information
The system SHALL display probe details including model, ID, port, and status.

#### Scenario: Probe information display
- **WHEN** a probe is successfully detected
- **THEN** system SHALL show probe model, ID, port location, and connection status in the main window
