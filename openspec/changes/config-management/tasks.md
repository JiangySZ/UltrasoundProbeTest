## 配置管理系统

### 2.1 实现JSON配置文件读取器

- [ ] 2.1.1 创建ConfigManager类
  - 单例模式
  - 配置加载接口
- [ ] 2.1.2 创建JsonLoader类
  - JSON文件读取
  - 错误处理
- [ ] 2.1.3 实现ProbeConfig数据结构
- [ ] 2.1.4 实现WaveformConfig数据结构

### 2.2 创建ProbeConfig.json schema

- [ ] 2.2.1 定义probe字段
  - id, model, type, elements, frequency
- [ ] 2.2.2 定义test字段
  - startDepth, adcRatio, excludeElements, calibrationElements
- [ ] 2.2.3 定义thresholds字段
  - sensitivity, centerFrequency, bandwidth6dB, bandwidth20dB, pulseLength20dB
- [ ] 2.2.4 创建示例配置文件 config/ProbeConfig.json

### 2.3 创建WaveformConfig.json schema

- [ ] 2.3.1 定义waveform字段
  - name, type, txVoltage, frequency, cycles, points
- [ ] 2.3.2 创建示例配置文件 config/WaveformConfig.json

### 2.4 实现配置文件验证功能

- [ ] 2.4.1 创建Validator类
- [ ] 2.4.2 实现必填字段验证
- [ ] 2.4.3 实现数值范围验证
- [ ] 2.4.4 实现阈值逻辑验证
- [ ] 2.4.5 实现ValidationResult返回

### 2.5 实现TXT灵敏度列表导入

- [ ] 2.5.1 创建SensitivityImporter类
- [ ] 2.5.2 实现TXT文件解析
- [ ] 2.5.3 实现每行一个数值格式
- [ ] 2.5.4 实现数值校验
- [ ] 2.5.5 创建示例TXT文件 config/SensitivityList.txt

### 2.6 单元测试

- [ ] 2.6.1 编写ConfigManager测试
  - testLoadValidProbeConfig
  - testLoadInvalidJson
- [ ] 2.6.2 编写Validator测试
  - testValidateMissingField
  - testValidateOutOfRange
- [ ] 2.6.3 编写SensitivityImporter测试
  - testImportValidFile
  - testImportInvalidFormat
- [ ] 2.6.4 运行单元测试验证

## 验收标准

- [ ] ConfigManager可正确加载JSON配置
- [ ] Validator可验证配置并返回错误
- [ ] SensitivityImporter可导入TXT灵敏度列表
- [ ] 所有单元测试通过
- [ ] 配置文件格式符合schema定义
