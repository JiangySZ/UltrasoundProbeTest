## 硬件抽象层

### 3.1 定义HardwareInterface抽象基类

- [x] 3.1.1 创建include/HAL/HardwareInterface.h
  - 定义Port结构体
  - 声明所有硬件接口方法
- [x] 3.1.2 实现基本错误处理
- [x] 3.1.3 添加文档注释

### 3.2 实现MockHardwareDriver模拟驱动

- [x] 3.2.1 创建include/HAL/MockHardwareDriver.h
- [x] 3.2.2 创建src/HAL/MockHardwareDriver.cpp
- [x] 3.2.3 实现acquireData生成仿真波形
  - 正弦波 + 噪声
  - 采样率 40MHz
- [x] 3.2.4 实现readProbeId模拟
- [x] 3.2.5 实现getTemperature模拟
- [x] 3.2.6 实现motorStart/motorStop模拟

### 3.3 实现硬件模式切换

- [x] 3.3.1 创建HardwareFactory工厂类
- [x] 3.3.2 实现create方法
- [x] 3.3.3 创建config/HardwareMode.json
- [x] 3.3.4 实现模式切换逻辑

### 3.4 实现DLL接口封装（预留）

- [ ] 3.4.1 创建RealHardwareDriver类结构
- [ ] 3.4.2 定义DLL接口声明
- [ ] 3.4.3 预留DLL加载逻辑

### 3.5 单元测试

- [x] 3.5.1 编写MockHardwareDriver测试
  - testAcquireDataReturnsValidSize
  - testAcquireDataWaveformGeneration
  - testReadProbeIdFormat
  - testGetTemperatureInRange
  - testMotorStartStop
- [x] 3.5.2 编写HardwareFactory测试
  - testCreateMockDriver
  - testModeSwitch
- [x] 3.5.3 运行单元测试验证

## 验收标准

- [x] HardwareInterface抽象基类定义完整
- [x] MockHardwareDriver可生成仿真数据
- [x] 硬件模式可切换
- [x] 所有单元测试通过
- [x] 无硬件环境下其他模块可正常开发
