## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    回波测试与DSP架构                          │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌──────────────────────────────────────────────────────┐  │
│  │                   TestManager                          │  │
│  │  (测试管理核心)                                         │  │
│  └──────────────────────────────────────────────────────┘  │
│                              │                               │
│         ┌────────────────────┼────────────────────┐        │
│         ▼                    ▼                    ▼        │
│  ┌────────────┐      ┌────────────┐      ┌────────────┐   │
│  │ TestRunner │      │Calibrator │      │ScanEngine  │   │
│  │            │      │            │      │            │   │
│  └────────────┘      └────────────┘      └────────────┘   │
│                              │                │            │
│                              │                ▼            │
│                              │      ┌────────────┐         │
│                              │      │DSPAnalyzer │         │
│                              │      │            │         │
│                              │      └────────────┘         │
│                                                             │
│  ┌──────────────────────────────────────────────────────┐  │
│  │                   TestResult                          │  │
│  ├──────────────────────────────────────────────────────┤  │
│  │  element : int                                        │  │
│  │  sensitivity : double                                  │  │
│  │  centerFrequency : double                              │  │
│  │  bandwidth6dB : double                                 │  │
│  │  bandwidth20dB : double                                │  │
│  │  pulseLength : double                                  │  │
│  │  tof : double                                          │  │
│  │  shortCircuit : bool                                   │  │
│  │  pass : bool                                          │  │
│  └──────────────────────────────────────────────────────┘  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## 测试模式

### 表面回波测试 (Surface Echo Test)
- **场景**: 快速检测，通常对空或简单反射
- **起始深度**: 固定 -0.5mm
- **流程**: 跳过校准
- **判定**: 仅"灵敏度"参与Pass/Fail判定

### 标准回波测试 (Standard Echo Test)
- **场景**: 严格QC或认证测试（ACR/FDA自检）
- **起始深度**: 读取配置 `<StartDepth>`
- **流程**: 若 StartDepth > 0，强制执行校准
- **判定**: 灵敏度、中心频率、带宽、脉冲长度、短路检测全项参与

## 核心类设计

### TestMode
```cpp
enum class TestMode {
    Surface,   // 表面回波测试
    Standard   // 标准回波测试
};
```

### TestRunner
```cpp
class TestRunner {
public:
    void setMode(TestMode mode);
    void setProbe(const ProbeInfo& probe);
    void setTester(const QString& tester);
    
    TestResult runElement(int element);
    QList<TestResult> runAllElements();
    
signals:
    void elementTested(TestResult result);
    void progressChanged(int percent);
    void testCompleted(QList<TestResult> results);
    
private:
    TestMode m_mode;
    ProbeInfo m_probe;
    QString m_tester;
};
```

### Calibrator
```cpp
class Calibrator {
public:
    // 校准阵元从配置读取（3个）
    QList<double> calibrate(QList<int> elements);
    
    // 波形叠加
    QVector<double>叠加(QList<QVector<double>> waveforms);
    
    // 人工确认
    bool userConfirm(const QList<QVector<double>>& waveforms);
};
```

### ScanEngine
```cpp
class ScanEngine {
public:
    void setRange(int startElement, int endElement);
    void excludeElements(QList<int> elements);
    
    QVector<double> acquire(int element);
    
private:
    int m_startElement;
    int m_endElement;
    QList<int> m_excludeElements;
};
```

### DSPAnalyzer
```cpp
class DSPAnalyzer {
public:
    // 灵敏度: dB = 20*log10(Vpeak/Vtx)
    double calculateSensitivity(const QVector<double>& data, double vtx);
    
    // 频域分析
    double calculateCenterFrequency(const QVector<double>& data);
    double calculateBandwidth(const QVector<double>& data, double threshold_db);
    
    // 时域分析
    double calculatePulseLength(const QVector<double>& data, double threshold_db);
    
    // TOF (Time of Flight)
    double calculateTOF(const QVector<double>& data);
    
    // 短路检测（相关系数）
    double calculateCorrelation(const QVector<double>& a, const QVector<double>& b);
    bool isShortCircuit(const QVector<double>& element, 
                        const QList<QVector<double>>& neighbors);
    
private:
    QVector<double> fft(const QVector<double>& data);
    QVector<double> ifft(const QVector<double>& data);
    double findPeak(const QVector<double>& data);
};
```

### TestResult
```cpp
struct TestResult {
    int element;
    double sensitivity;        // dB
    double centerFrequency;    // MHz
    double bandwidth6dB;       // %
    double bandwidth20dB;      // %
    double pulseLength20dB;   // ns
    double tof;                // ns
    bool shortCircuit;
    
    // 判定结果
    bool sensitivityPass;
    bool frequencyPass;
    bool bandwidthPass;
    bool pulsePass;
    bool shortCircuitPass;
    bool overallPass;
};
```

## DSP算法详解

### 灵敏度计算
```
sensitivity_dB = 20 * log10(V_peak / V_tx)
V_peak: 采集波形峰值电压
V_tx: 发射电压 (从配置读取)
```

### FFT频域分析
```
1. 对时域信号做FFT
2. 计算幅度谱 |X(k)|
3. 找峰值频率（中心频率）
4. 计算-6dB和-20dB带宽
```

### TOF计算
```
1. 找第一个阵元的主峰极性作为基准
2. 计算后续阵元主峰相对时延
3. TOF = (index_peak - index_start) / sample_rate
```

### 短路检测
```
1. 对每个阵元，采集其与相邻5个阵元的波形
2. 计算相关系数: corr = sum(x*y) / sqrt(sum(x^2)*sum(y^2))
3. 若相关系数 > 0.95，判定为短路
```

## 单元测试设计

### TestDSPAnalyzer
- testSensitivityCalculation
- testCenterFrequency
- testBandwidth6dB
- testBandwidth20dB
- testPulseLength
- testTOF
- testCorrelation
- testShortCircuitDetection

### TestCalibrator
- testSelectCalibrationElements
- testWaveformSuperposition
- testUserConfirm

### TestRunner
- testSurfaceTestMode
- testStandardTestMode
- testExcludeElements

## 依赖关系

- 依赖Change 1: project-skeleton
- 依赖Change 2: config-management
- 依赖Change 3: hardware-abstraction
- 依赖Change 4: probe-detection
- 被Change 6: report-ui 依赖
