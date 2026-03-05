## 硬件抽象层

### 3.1 定义HardwareInterface抽象基类

- [ ] 3.1.1 创建include/HAL/HardwareInterface.h
  - 定义Port结构体
  - 声明所有硬件接口方法
- [ ] 3.1.2 实现基本错误处理
- [ ] 3.1.3 添加文档注释

### 3.2 实现MockHardwareDriver模拟驱动

- [ ] 3.2.1 创建include/HAL/MockHardwareDriver.h
- [ ] 3.2.2 创建src/HAL/MockHardwareDriver.cpp
- [ ] 3.2.3 实现acquireData生成仿真波形
  - 正弦波 + 噪声
  - 采样率 40MHz
- [ ] 3.2.4 实现readProbeId模拟
- [ ] 3.2.5 实现getTemperature模拟
- [ ] 3.2.6 实现motorStart/motorStop模拟

### 3.3 实现硬件模式切换

- [ ] 3.3.1 创建HardwareFactory工厂类
- [ ] 3.3.2 实现create方法
- [ ] 3.3.3 创建config/HardwareMode.json
- [ ] 3.3.4 实现模式切换逻辑

### 3.4 实现DLL接口封装（预留）

- [ ] 3.4.1 创建RealHardwareDriver类结构
- [ ] 3.4.2 定义DLL接口声明
- [ ] 3.4.3 预留DLL加载逻辑

### 3.5 单元测试

- [ ] 3.5.1 编写MockHardwareDriver测试
  - testAcquireDataReturnsValidSize
  - testAcquireDataWaveformGeneration
  - testReadProbeIdFormat
  - testGetTemperatureInRange
  - testMotorStartStop
- [ ] 3.5.2 编写HardwareFactory测试
  - testCreateMockDriver
  - testModeSwitch
- [ ] 3.5.3 运行单元测试验证

## 验收标准

- [ ] HardwareInterface抽象基类定义完整
- [ ] MockHardwareDriver可生成仿真数据
- [ ] 硬件模式可切换
- [ ] 所有单元测试通过
- [ ] 无硬件环境下其他模块可正常开发
