## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    报告与UI架构                              │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌──────────────────────────────────────────────────────┐  │
│  │                   MainWindow                           │  │
│  │  (主窗口)                                              │  │
│  └──────────────────────────────────────────────────────┘  │
│                              │                               │
│         ┌────────────────────┼────────────────────┐        │
│         ▼                    ▼                    ▼        │
│  ┌────────────┐      ┌────────────┐      ┌────────────┐   │
│  │ProbePanel  │      │ Waveform   │      │ TrendChart │   │
│  │            │      │ Widget     │      │ Widget     │   │
│  └────────────┘      └────────────┘      └────────────┘   │
│         │                                               │   │
│         │              ┌────────────┐                   │   │
│         └─────────────▶│ TestPanel  │◀──────────────────┘   │
│                        └────────────┘                      │
│                              │                               │
│                        ┌────────────┐                       │
│                        │SpecialPanel│                       │
│                        │(Temp/Motor)│                       │
│                        └────────────┘                       │
│                                                             │
│  ┌──────────────────────────────────────────────────────┐  │
│  │                   ReportGenerator                      │  │
│  │                   (PDF报告生成)                         │  │
│  └──────────────────────────────────────────────────────┘  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## 主窗口布局

```
┌────────────────────────────────────────────────────────────┐
│  菜单栏 [文件] [测试] [工具] [帮助]                          │
├────────────────────────────────────────────────────────────┤
│ ┌──────────────────┐ ┌──────────────────────────────────┐ │
│ │   端口/探头显示   │ │        实时波形显示               │ │
│ │   [A] [B] [C] [D]│ │                                  │ │
│ │   探头: XYZ-123  │ │                                  │ │
│ │   状态: 已激活    │ │                                  │ │
│ └──────────────────┘ └──────────────────────────────────┘ │
├────────────────────────────────────────────────────────────┤
│ ┌──────────────────────────────────────────────────────────┐│
│ │                    趋势图表 (5张)                        ││
│ │  [灵敏度] [中心频率] [带宽] [脉冲长度] [TOF]            ││
│ └──────────────────────────────────────────────────────────┘│
├────────────────────────────────────────────────────────────┤
│ ┌──────────────────┐ ┌──────────────────────────────────┐ │
│ │   测试控制面板    │ │        特殊功能面板               │ │
│ │ [表面测试][标准]  │ │ 温度: 28.5°C  [电机启动][停止]   │ │
│ │ 测试者: ________ │ │                                  │ │
│ │ [开始测试][停止]  │ │ [ID烧录]                          │ │
│ └──────────────────┘ └──────────────────────────────────┘ │
├────────────────────────────────────────────────────────────┤
│ 状态栏: 就绪                                                │
└────────────────────────────────────────────────────────────┘
```

## 核心类设计

### MainWindow
```cpp
class MainWindow : public QMainWindow {
private:
    ProbePanel* m_probePanel;
    WaveformWidget* m_waveformWidget;
    TrendChartWidget* m_trendWidget;
    TestPanel* m_testPanel;
    SpecialPanel* m_specialPanel;
    QStatusBar* m_statusBar;
    
public slots:
    void onProbeDetected(ProbeInfo probe);
    void onTestProgress(TestResult result);
    void onTestCompleted(QList<TestResult> results);
    void onError(QString error);
};
```

### ReportGenerator
```cpp
class ReportGenerator {
public:
    // PDF报告结构
    struct ReportData {
        QString probeModel;
        QString probeId;
        QString tester;
        QDateTime testTime;
        QString systemSN;
        QString softwareVersion;
        TestMode mode;
        QList<TestResult> results;
        bool overallPass;
    };
    
    bool generate(const ReportData& data, const QString& outputPath);
    
private:
    void addHeader(PdfDocument& doc, const ReportData& data);
    void addTraceability(PdfDocument& doc, const ReportData& data);
    void addCharts(PdfDocument& doc, const ReportData& data);
    void addConclusion(PdfDocument& doc, const ReportData& data);
};
```

### WaveformWidget (QCustomPlot)
```cpp
class WaveformWidget : public QWidget {
public:
    void setData(const QVector<double>& waveform);
    void clear();
    void setTitle(const QString& title);
};
```

### TrendChartWidget
```cpp
class TrendChartWidget : public QWidget {
public:
    // 5个子图
    enum ChartType { Sensitivity, Frequency, Bandwidth, Pulse, TOF };
    
    void addData(ChartType type, int element, double value);
    void clear();
    void exportToImage(const QString& path);
};
```

### SpecialPanel
```cpp
class SpecialPanel : public QWidget {
private:
    QLabel* m_temperatureLabel;
    QPushButton* m_motorStartBtn;
    QPushButton* m_motorStopBtn;
    QPushButton* m_idBurnBtn;
    
public slots:
    void onTemperatureUpdated(double temp);
    void onMotorStarted();
    void onMotorStopped();
    void onIdBurnRequested();
};
```

### IdBurnWizard
```cpp
class IdBurnWizard : public QWizard {
public:
    enum { Page_Select, Page_Input, Page_Burn, Page_Result };
    
    void setProbe(const ProbeInfo& probe);
    QString getBurnedId() const;
};
```

## PDF报告结构

### Header
- 探头型号 (Probe Model)
- 探头ID (Probe ID)
- 测试者 (Tester Name)
- 测试时间 (Test Date/Time)

### Traceability (FDA要求)
- 测试系统序列号 (System SN)
- 测试软件版本 (Software Version vX.X)

### Body
- 5张指标折线图
  - 灵敏度 vs 阵元
  - 中心频率 vs 阵元
  - 带宽 vs 阵元
  - 脉冲长度 vs 阵元
  - TOF vs 阵元

### Conclusion
- 整体Pass/Fail
- 故障阵元列表
- 表面测试特别标注

## 集成测试设计

### TestIntegration
- testFullWorkflow 从探头检测到报告生成
- testReportGeneration
- testWaveformDisplay
- testTrendCharts
- testSpecialFunctions

## 依赖关系

- 依赖Change 1: project-skeleton
- 依赖Change 2: config-management
- 依赖Change 3: hardware-abstraction
- 依赖Change 4: probe-detection
- 依赖Change 5: echo-test-dsp

## 部署

- Change 6完成后，项目完整可用
