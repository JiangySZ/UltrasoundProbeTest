## Why

项目开发的首要任务是建立可编译、可运行的基础框架。没有稳定的项目骨架，后续功能开发无法进行验证。本阶段将创建Qt项目结构、配置开发环境、搭建目录框架，确保代码可以编译通过并运行基本窗口。

## What Changes

- 创建Qt项目文件（CMakeLists.txt和.pro）
- 配置Qt 5.9.1 + VS 2017开发环境
- 创建标准目录结构（UI/Business/HAL/Config/Test）
- 配置日志系统（Qt QLoggingCategory）
- 实现最小可运行窗口
- 添加项目依赖（QtPDF、FFTW、QCustomPlot）
- 编写编译测试验证项目可构建

## Capabilities

### New Capabilities
- `project-build`: Qt项目构建配置

### Modified Capabilities
（无 - 全新项目基础）

## Impact

- 建立Qt(C++)桌面应用项目结构
- 目录结构清晰，便于后续模块添加
- 编译验证确保后续开发有坚实基础
