## 回波测试与校准

### 5.1 实现表面回波测试模式

- [ ] 5.1.1 定义TestMode枚举
- [ ] 5.1.2 创建TestRunner类
- [ ] 5.1.3 实现setMode方法
- [ ] 5.1.4 配置表面测试参数
  - 起始深度固定 -0.5mm
  - 跳过校准
- [ ] 5.1.5 实现表面测试判定逻辑

### 5.2 实现标准回波测试模式

- [ ] 5.2.1 配置标准测试参数
  - 起始深度从配置读取
- [ ] 5.2.2 实现强制校准检查
- [ ] 5.2.3 实现全项判定
  - 灵敏度
  - 中心频率
  - 带宽
  - 脉冲长度
  - 短路检测

### 5.3 实现校准流程

- [ ] 5.3.1 创建Calibrator类
- [ ] 5.3.2 实现校准阵元选择
- [ ] 5.3.3 实现校准波形采集
- [ ] 5.3.4 实现波形叠加显示
- [ ] 5.3.5 实现人工确认对话框
- [ ] 5.3.6 实现校准结果处理

### 5.4 实现阵元扫描

- [ ] 5.4.1 创建ScanEngine类
- [ ] 5.4.2 实现扫描范围设置
- [ ] 5.4.3 实现ExcludeElements排除
- [ ] 5.4.4 实现单阵元激励采集
- [ ] 5.4.5 实现电压转换 (Raw * ADCRatio)

### 5.5 实现DSP分析算法

- [ ] 5.5.1 创建DSPAnalyzer类
- [ ] 5.5.2 实现FFT变换（使用FFTW）
- [ ] 5.5.3 实现灵敏度计算
  - dB = 20*log10(Vpeak/Vtx)
- [ ] 5.5.4 实现频域分析
  - 中心频率计算
  - -6dB带宽计算
  - -20dB带宽计算
- [ ] 5.5.5 实现时域分析
  - 脉冲长度计算 (-6dB/-20dB)
- [ ] 5.5.6 实现TOF计算
- [ ] 5.5.7 实现短路检测
  - 相邻5阵元相关系数
  - 阈值判定

### 5.6 单元测试

- [ ] 5.6.1 编写DSPAnalyzer测试
  - testSensitivityCalculation
  - testCenterFrequency
  - testBandwidth6dB
  - testBandwidth20dB
  - testPulseLength
  - testTOF
  - testShortCircuitDetection
- [ ] 5.6.2 编写Calibrator测试
  - testWaveformSuperposition
- [ ] 5.6.3 编写TestRunner测试
  - testSurfaceTestMode
  - testStandardTestMode
- [ ] 5.6.4 运行单元测试验证

## 验收标准

- [ ] 表面回波测试可运行（仅灵敏度判定）
- [ ] 标准回波测试可运行（全项判定）
- [ ] 校准流程完整（3阵元、叠加、确认）
- [ ] 阵元扫描正确（包含/排除逻辑）
- [ ] DSP算法正确
  - 灵敏度计算正确
  - FFT频域分析正确
  - TOF计算正确
  - 短路检测正确
- [ ] 所有单元测试通过
