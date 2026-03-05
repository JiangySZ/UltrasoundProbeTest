## Why

探头检测与激活是测试流程的入口。系统需要自动扫描端口、识别探头ID、判断是否为已知探头并加载对应配置。本阶段将实现完整的探头检测流程，为后续回波测试做好准备。

## What Changes

- 实现端口扫描功能（A/B/C/D端口）
- 实现探头ID读取功能
- 实现已知探头自动匹配
- 实现未知探头处理（烧录/临时配置）
- 实现Probe_Activate函数封装
- 实现System_LoadScript函数封装
- 编写探头检测单元测试

## Capabilities

### New Capabilities
- `probe-detection`: 端口扫描与ID识别
- `probe-activation`: 探头激活与脚本加载

### Modified Capabilities
- 依赖Change 1: project-skeleton
- 依赖Change 2: config-management
- 依赖Change 3: hardware-abstraction

## Impact

- 自动化探头检测流程
- 统一的探头激活接口
- 未知探头的处理方案
