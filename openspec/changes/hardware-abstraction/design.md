## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    硬件抽象层架构                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│                    ┌──────────────────┐                     │
│                    │  HardwareFactory  │                     │
│                    │   (工厂类)        │                     │
│                    └────────┬─────────┘                     │
│                             │                                │
│              ┌──────────────┼──────────────┐               │
│              ▼              ▼              ▼               │
│     ┌────────────┐  ┌────────────┐  ┌────────────┐        │
│     │HardwareInter│  │RealHardware │  │MockHardware │        │
│     │   face     │  │   Driver    │  │   Driver    │        │
│     │ (Abstract) │  │ (Future)    │  │ (Implemented│        │
│     └────────────┘  └────────────┘  └────────────┘        │
│                                                             │
│  ┌──────────────────────────────────────────────────────┐  │
│  │                    HardwareInterface                 │  │
│  ├──────────────────────────────────────────────────────┤  │
│  │ + systemInit() : bool                                │  │
│  │ + scanPorts() : QList<Port>                          │  │
│  │ + readProbeId(port) : QString                         │  │
│  │ + activateProbe(port, id) : bool                     │  │
│  │ + loadScript(script) : bool                          │  │
│  │ + setTxWaveform(waveform) : bool                     │  │
│  │ + acquireData(element) : QVector<double>             │  │
│  │ + getTemperature() : double                          │  │
│  │ + motorStart() : bool                                 │  │
│  │ + motorStop() : bool                                  │  │
│  │ + writeProbeId(id) : bool                            │  │
│  └──────────────────────────────────────────────────────┘  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## 核心接口设计

### HardwareInterface (抽象基类)

```cpp
class HardwareInterface {
public:
    virtual ~HardwareInterface() = default;
    
    // 系统
    virtual bool systemInit() = 0;
    virtual QString lastError() = 0;
    
    // 端口与探头
    virtual QList<Port> scanPorts() = 0;
    virtual QString readProbeId(const QString& port) = 0;
    virtual bool activateProbe(const QString& port, const QString& probeId) = 0;
    
    // 脚本与波形
    virtual bool loadScript(const QString& scriptPath) = 0;
    virtual bool setTxWaveform(const WaveformConfig& config) = 0;
    
    // 数据采集
    virtual QVector<double> acquireData(int element) = 0;
    
    // 温度与电机
    virtual double getTemperature() = 0;
    virtual bool motorStart() = 0;
    virtual bool motorStop() = 0;
    
    // ID烧录
    virtual bool writeProbeId(const QString& id) = 0;
    virtual bool readProbeIdFromEeprom(const QString& port) = 0;
};
```

### MockHardwareDriver

```cpp
class MockHardwareDriver : public HardwareInterface {
private:
    bool m_simulateError = false;
    QVector<double> generateMockWaveform(int element);
    double generateMockTemperature();
    
public:
    void setSimulateError(bool error) { m_simulateError = error; }
    
    // 实现HardwareInterface所有方法
    // 使用随机数/正弦波生成仿真数据
};
```

## Mock数据生成策略

### 采集波形生成
```
acquireData(element):
  - 生成采样率 40MHz 的正弦波
  - 中心频率从配置读取（默认 3.5MHz）
  - 添加高斯噪声模拟真实信号
  - 波形长度 2048 点
  - 灵敏度根据element索引添加递减趋势
```

### 温度模拟
```
getTemperature():
  - 返回 25.0 ~ 35.0 之间的随机值
  - 偶尔返回超出范围的测试异常情况
```

### ID模拟
```
readProbeId(port):
  - 格式: "PROBE-{PORT}-{RANDOM}"
  - 示例: "PROBE-A-12345"
```

## 硬件模式切换

### config/HardwareMode.json
```json
{
  "mode": "mock",  // "mock" | "real"
  "real": {
    "dllPath": "HardwareDLL.dll",
    "deviceId": "USB001"
  },
  "mock": {
    "seed": 12345,
    "errorSimulation": false
  }
}
```

### HardwareFactory
```cpp
class HardwareFactory {
public:
    static std::unique_ptr<HardwareInterface> create(HardwareMode mode);
    static void setMode(HardwareMode mode);
    static HardwareMode currentMode();
};
```

## 单元测试设计

### TestHardwareInterface
- testInterfaceAllMethodsVirtual

### TestMockHardwareDriver
- testSystemInit
- testScanPorts
- testReadProbeId
- testAcquireDataReturnsVector
- testAcquireDataElement0HasHigherSensitivity
- testGetTemperatureInRange
- testMotorStartStop

### TestHardwareFactory
- testCreateMockDriver
- testModeSwitch

## 依赖关系

- 依赖Change 1: project-skeleton（项目基础）
- 依赖Change 2: config-management（配置读取）
- 被Change 4: probe-detection 依赖
- 被Change 5: echo-test-dsp 依赖
