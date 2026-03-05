## Why

回波测试与DSP分析是系统的核心功能。通过对探头阵元进行激励和采集，分析回波信号的灵敏度、频率、带宽、脉冲长度等指标，判断探头是否合格。本阶段将实现完整的回波测试流程和DSP算法。

## What Changes

- 实现表面回波测试模式（快速检测，仅灵敏度判定）
- 实现标准回波测试模式（全项判定，含校准）
- 实现校准流程（3阵元选取、波形叠加、人工确认）
- 实现阵元扫描（激励、采集、门控）
- 实现DSP分析算法（灵敏度、FFT、带宽、TOF、短路检测）
- 编写DSP算法单元测试

## Capabilities

### New Capabilities
- `echo-test-surface`: 表面回波测试
- `echo-test-standard`: 标准回波测试
- `calibration`: 探头校准
- `element-scanning`: 阵元扫描
- `dsp-analysis`: DSP分析算法

### Modified Capabilities
- 依赖Change 1: project-skeleton
- 依赖Change 2: config-management
- 依赖Change 3: hardware-abstraction
- 依赖Change 4: probe-detection

## Impact

- 完整的回波测试功能
- DSP算法实现（可用于产品）
- 符合FDA/IEC标准的测试流程
