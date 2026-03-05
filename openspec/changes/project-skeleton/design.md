## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    项目目录结构                               │
├─────────────────────────────────────────────────────────────┤
│  UltrasoundProbeTest/                                       │
│  ├── CMakeLists.txt          # CMake构建配置               │
│  ├── UltrasoundProbeTest.pro # qmake项目文件               │
│  ├── src/                    # 源代码                       │
│  │   ├── main.cpp            # 程序入口                     │
│  │   ├── UI/                 # 界面层                       │
│  │   ├── Business/           # 业务逻辑层                   │
│  │   ├── HAL/                # 硬件抽象层                   │
│  │   └── Config/             # 配置管理                     │
│  ├── include/                # 头文件                       │
│  │   ├── UI/                 │
│  │   ├── Business/           │
│  │   ├── HAL/                │
│  │   └── Config/             │
│  ├── tests/                  # 单元测试                     │
│  ├── config/                 # 配置文件                     │
│  └── thirdparty/             # 第三方库                      │
│      ├── qtpdf/              │
│      ├── qcustomplot/        │
│      └── fftw/               │
└─────────────────────────────────────────────────────────────┘
```

## 技术选型

### 构建系统
- **CMake**: 主要构建系统，跨平台支持好
- **qmake**: 保留.pro文件作为备选

### 第三方库
| 库 | 版本 | 用途 |
|----|------|------|
| Qt | 5.9.1 | UI和核心框架 |
| QtPDF | - | PDF报告生成 |
| QCustomPlot | - | 趋势图绘制 |
| FFTW | 3.x | 频域分析 |

### 日志系统
- 使用Qt QLoggingCategory
- 分模块配置日志级别
- 输出到文件和控制台

## 模块设计

### 1. 项目配置 (CMakeLists.txt)
- 设置C++14标准
- 配置Qt模块（core, gui, widgets, test, pdf, printsupport）
- 添加第三方库include路径
- 配置单元测试框架

### 2. 目录结构
```
src/          # .cpp实现文件
include/      # .h头文件
tests/        # Qt Test单元测试
config/       # 运行时配置文件
```

### 3. 日志模块
```cpp
// 分类日志示例
Q_LOGGING_CATEGORY(LOG_MAIN, "main")
Q_LOGGING_CATEGORY(LOG_CONFIG, "config")
Q_LOGGING_CATEGORY(LOG_HAL, "hal")
```

## 编译验证

### 验证步骤
1. 使用CMake配置项目
2. 编译Release版本
3. 运行可执行文件确认窗口显示
4. 运行单元测试框架确认测试可执行

### 预期结果
- 编译无错误无警告
- 程序启动显示空白主窗口
- 测试框架可执行（0 tests）

## 依赖关系

本变更无外部依赖，是项目的起始点。
