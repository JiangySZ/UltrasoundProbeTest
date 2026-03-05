## Why

配置文件管理是系统的核心基础。探头参数、测试阈值、波形配置等都需要通过配置文件管理。本阶段将实现JSON格式的配置管理系统，支持配置读取、验证、导入功能，为后续所有功能提供稳定的数据支撑。

## What Changes

- 实现JSON配置文件读取器
- 定义ProbeConfig.json schema（探头参数、测试阈值）
- 定义WaveformConfig.json schema（波形参数）
- 实现配置文件验证器
- 实现TXT灵敏度列表导入功能
- 编写配置管理单元测试

## Capabilities

### New Capabilities
- `config-management`: JSON配置文件管理
- `config-validation`: 配置验证
- `sensitivity-import`: TXT灵敏度列表导入

### Modified Capabilities
- 依赖Change 1的project-build

## Impact

- 统一的配置管理接口
- 配置验证确保数据正确
- 为探头测试提供参数支撑
