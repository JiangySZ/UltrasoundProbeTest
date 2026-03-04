# Ultrasound Probe Test System

Windows平台超声探头自动化测试与校准软件

## 功能特性

- 探头自动检测与ID识别
- 表面回波测试与标准回波测试
- 自动化阵元扫描与DSP分析
- PDF报告生成（含FDA Traceability）
- 探头ID烧录
- TEE温度监测与电机控制

## 开发环境

- Qt 5.9.1
- Visual Studio 2017 Community
- Qtpdf
- QCustomPlot
- FFTW

## 构建

```bash
# 使用qmake
qmake UltrasoundProbeTest.pro
make

# 或使用CMake
cmake -B build
cmake --build build
```

## 项目结构

```
src/          # 源代码
include/      # 头文件
test/         # 测试代码
docs/         # 文档
config/       # 配置文件
```
