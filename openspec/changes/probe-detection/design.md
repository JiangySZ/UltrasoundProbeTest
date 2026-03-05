## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    探头检测与激活架构                          │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌──────────────────────────────────────────────────────┐  │
│  │                   ProbeManager                         │  │
│  │  (探头管理核心类)                                        │  │
│  └──────────────────────────────────────────────────────┘  │
│                              │                               │
│         ┌────────────────────┼────────────────────┐        │
│         ▼                    ▼                    ▼        │
│  ┌────────────┐      ┌────────────┐      ┌────────────┐      │
│  │PortScanner │      │ProbeReader │      │ScriptLoader│      │
│  │            │      │            │      │            │      │
│  └────────────┘      └────────────┘      └────────────┘      │
│                                                             │
│  ┌──────────────────────────────────────────────────────┐  │
│  │                   ProbeInfo                            │  │
│  ├──────────────────────────────────────────────────────┤  │
│  │  port : QString                                       │  │
│  │  id : QString                                         │  │
│  │  model : QString                                      │  │
│  │  config : ProbeConfig*                                │  │
│  │  state : ProbeState                                   │  │
│  └──────────────────────────────────────────────────────┘  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## 核心类设计

### ProbeInfo
```cpp
struct ProbeInfo {
    QString port;           // A, B, C, D
    QString id;            // 探头ID
    QString model;         // 探头型号
    ProbeConfig* config;   // 对应配置
    ProbeState state;     // 未连接/已连接/已激活
};

enum class ProbeState {
    Disconnected,
    Connected,
    Activated,
    Error
};
```

### PortScanner
```cpp
class PortScanner {
public:
    QList<Port> scan();
    PortStatus checkPort(const QString& port);
    
private:
    HardwareInterface* m_hardware;
};
```

### ProbeReader
```cpp
class ProbeReader {
public:
    QString readId(const QString& port);
    bool isKnownProbe(const QString& id);
    ProbeConfig* matchConfig(const QString& id);
};
```

### ScriptLoader
```cpp
class ScriptLoader {
public:
    bool loadScript(const QString& scriptPath);
    bool activateProbe(const QString& port, const QString& probeId);
};
```

### ProbeManager (Facade)
```cpp
class ProbeManager {
public:
    QList<ProbeInfo> scanAndDetect();
    bool activateProbe(const ProbeInfo& probe);
    bool loadScript(const QString& path);
    
    // 已知探头处理
    bool handleKnownProbe(const ProbeInfo& probe);
    
    // 未知探头处理
    enum UnknownProbeAction { BurnId, TemporaryConfig };
    bool handleUnknownProbe(const ProbeInfo& probe, UnknownProbeAction action);
    
private:
    HardwareInterface* m_hardware;
    ConfigManager* m_config;
};
```

## 检测流程

### 流程图

```
┌─────────────┐
│  开始扫描   │
└──────┬──────┘
       ▼
┌─────────────┐
│  扫描A/B/C/D│
│    端口     │
└──────┬──────┘
       ▼
┌─────────────┐    否   ┌─────────────┐
│  有探头连接? │────────▶│  显示无探头  │
└──────┬──────┘         └─────────────┘
       │ 是
       ▼
┌─────────────┐
│  读取ID     │
└──────┬──────┘
       ▼
┌─────────────┐    否   ┌─────────────┐
│  已知探头?   │────────▶│  未知探头   │
└──────┬──────┘         │  处理向导   │
       │ 是             └─────────────┘
       ▼
┌─────────────┐
│  加载配置   │
└──────┬──────┘
       ▼
┌─────────────┐
│  激活探头   │
└──────┬──────┘
       ▼
┌─────────────┐
│  等待测试   │
└─────────────┘
```

### 未知探头处理

```
┌─────────────┐
│  未知探头   │
│   检测到    │
└──────┬──────┘
       ▼
┌─────────────┐
│  选择操作   │
│[烧录] [临时]│
└──────┬──────┘
       │
   ┌───┴───┐
   ▼       ▼
┌─────┐ ┌─────┐
│烧录│ │临时 │
│ ID │ │配置 │
└─────┘ └─────┘
   │     │
   ▼     ▼
┌─────────────┐
│  激活探头   │
└─────────────┘
```

## 单元测试设计

### TestPortScanner
- testScanPorts
- testCheckPort

### TestProbeReader
- testReadId
- testKnownProbeMatching

### TestProbeManager
- testScanAndDetect
- testActivateKnownProbe
- testActivateUnknownProbe
- testLoadScript

## 依赖关系

- 依赖Change 1: project-skeleton
- 依赖Change 2: config-management（配置加载）
- 依赖Change 3: hardware-abstraction（硬件接口）
- 被Change 5: echo-test-dsp 依赖
- 被Change 6: report-ui 依赖
