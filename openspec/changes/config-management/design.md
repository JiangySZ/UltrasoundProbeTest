## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    配置管理模块架构                           │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐    │
│  │ ConfigManager│───▶│JsonLoader   │    │             │    │
│  │   (Facade)   │    │             │    │  Validator  │    │
│  └─────────────┘    └─────────────┘    └─────────────┘    │
│         │                                      │           │
│         ▼                                      ▼           │
│  ┌─────────────┐                       ┌─────────────┐    │
│  │ProbeConfig  │                       │ValidationErr│    │
│  │WaveformConfig                      │             │    │
│  └─────────────┘                       └─────────────┘    │
│                                                             │
│  ┌─────────────────────────────────────────────────────┐  │
│  │              SensitivityImporter                     │  │
│  │              (TXT -> List<double>)                   │  │
│  └─────────────────────────────────────────────────────┘  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## 数据模型

### ProbeConfig.json Schema

```json
{
  "probe": {
    "id": "string",
    "model": "string",
    "type": "linear| phased| convex",
    "elements": "number",
    "frequency": "number (MHz)"
  },
  "test": {
    "startDepth": "number (mm)",
    "adcRatio": "number",
    "excludeElements": ["number"],
    "calibrationElements": ["number", "number", "number"]
  },
  "thresholds": {
    "sensitivity": {
      "nominal": "number (dB)",
      "tolerance": "number (dB)"
    },
    "centerFrequency": {
      "nominal": "number (MHz)",
      "tolerance": "number (MHz)"
    },
    "bandwidth6dB": {
      "nominal": "number (%)",
      "tolerance": "number (%)"
    },
    "bandwidth20dB": {
      "nominal": "number (%)",
      "tolerance": "number (%)"
    },
    "pulseLength20dB": {
      "nominal": "number (ns)",
      "tolerance": "number (ns)"
    }
  },
  "sensitivityList": "string (filename)"
}
```

### WaveformConfig.json Schema

```json
{
  "waveform": {
    "name": "string",
    "type": "pulser| arbitrary",
    "txVoltage": "number (V)",
    "frequency": "number (MHz)",
    "cycles": "number",
    "points": ["number"]
  }
}
```

## 核心类设计

### ConfigManager (外观类)
```
职责: 统一配置管理入口
方法:
  - loadProbeConfig(path) -> ProbeConfig
  - loadWaveformConfig(path) -> WaveformConfig
  - validate() -> ValidationResult
  - getSensitivityList() -> QList<double>
  - importSensitivityFromTxt(path) -> QList<double>
```

### JsonLoader
```
职责: JSON文件加载和解析
方法:
  - load(path) -> QJsonObject
  - parseError() -> QString
```

### Validator
```
职责: 配置验证
方法:
  - validate(config) -> ValidationResult
  - validateProbe(probe) -> ValidationResult
  - validateThresholds(thresholds) -> ValidationResult
```

### ValidationResult
```
职责: 验证结果封装
属性:
  - isValid: bool
  - errors: QList<ValidationError>
  - warnings: QList<ValidationWarning>
```

### SensitivityImporter
```
职责: TXT灵敏度列表导入
方法:
  - import(path) -> QList<double>
  - parseLine(line) -> double
```

## 单元测试设计

### TestConfigManager
- testLoadValidProbeConfig
- testLoadInvalidJson
- testValidateMissingField
- testValidateOutOfRange
- testSensitivityImport
- testSensitivityImportInvalid

### TestValidator
- testValidConfig
- testInvalidElementCount
- testInvalidFrequency
- testInvalidThreshold

### TestSensitivityImporter
- testImportValidFile
- testImportEmptyFile
- testImportInvalidFormat

## 依赖关系

- 依赖Change 1: project-skeleton
- 被Change 3: hardware-abstraction 依赖
- 被Change 4: probe-detection 依赖
- 被Change 5: echo-test-dsp 依赖
