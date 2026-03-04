## Why

目前缺乏标准化的超声探头物理特性测试工具，无法满足FDA和IEC关于设备定期维护、检查及质量控制的要求。人工测试效率低、结果难以追溯。开发自动化测试系统可提升检测效率、确保测试一致性，并生成符合监管要求的可追溯报告。

## What Changes

- 新建完整的超声探头测试系统（Windows桌面应用）
- 实现探头自动检测、激活、ID烧录功能
- 实现表面回波测试和标准回波测试两种测试模式
- 实现自动化阵元扫描和DSP分析（灵敏度、频率、带宽、TOF等）
- 实现带Traceability的PDF报告生成
- 实现TEE温度监测和电机控制等特殊功能
- 使用JSON格式配置文件替代原有XML
- 构建模拟硬件层以便无硬件环境下开发和测试

## Capabilities

### New Capabilities
- `probe-detection`: 探头自动检测与ID识别
- `probe-activation`: 探头激活与脚本加载
- `id-programming`: 探头ID烧录与校验
- `echo-test-surface`: 表面回波测试（快速检测，仅灵敏度判定）
- `echo-test-standard`: 标准回波测试（全项判定，含校准）
- `element-scanning`: 自动化阵元扫描与DSP分析
- `calibration`: 探头校准流程
- `report-generation`: PDF报告生成（含Traceability）
- `temperature-monitoring`: TEE温度监测
- `motor-control`: 电机控制
- `config-management`: JSON配置文件管理
- `hardware-simulation`: 硬件接口模拟层

### Modified Capabilities
（无 - 全新项目）

## Impact

- 新增Qt(C++)桌面应用项目
- 集成Qtpdf库用于PDF生成
- 新增硬件模拟层用于无硬件环境开发
- 配置文件从XML迁移至JSON格式
