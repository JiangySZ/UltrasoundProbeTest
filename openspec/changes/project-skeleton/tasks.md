## 项目基础框架搭建

### 1.1 创建Qt项目文件

- [x] 1.1.1 创建CMakeLists.txt
  - 设置项目名称 UltrasoundProbeTest
  - 设置C++14标准
  - 配置Qt5模块
  - 添加第三方库路径
- [x] 1.1.2 创建UltrasoundProbeTest.pro
  - 匹配CMakeLists配置
  - 添加Qt模块依赖
- [x] 1.1.3 创建config/Application.json
  - 应用基本配置（名称、版本）

### 1.2 配置开发环境

- [x] 1.2.1 验证Qt 5.9.1安装
- [x] 1.2.2 验证VS 2017安装
- [x] 1.2.3 准备第三方库
  - [x] 1.2.3.1 准备FFTW
    - 使用fftw++-3.03 C++封装库
  - [x] 1.2.3.2 准备QCustomPlot
    - qcustomplot.h 和 qcustomplot.cpp 已放置
  - [x] 1.2.3.3 准备QtPDF
    - 使用QPrinter替代方案
- [x] 1.2.4 验证Qt VS Tools集成

### 1.3 创建目录结构

- [x] 1.3.1 创建src/目录及子目录
  - src/UI/
  - src/Business/
  - src/HAL/
  - src/Config/
- [x] 1.3.2 创建include/目录及子目录
- [x] 1.3.3 创建tests/目录
- [x] 1.3.4 创建config/目录
- [x] 1.3.5 创建thirdparty/目录结构

### 1.4 配置日志系统

- [x] 1.4.1 创建Logger类
  - 单例模式
  - 文件输出
  - 控制台输出
  - 日志级别控制
- [x] 1.4.2 定义日志分类
  - LOG_MAIN: 主流程
  - LOG_CONFIG: 配置管理
  - LOG_HAL: 硬件抽象
  - LOG_TEST: 测试流程
- [x] 1.4.3 配置文件日志开关

### 1.5 实现最小可运行窗口

- [x] 1.5.1 创建main.cpp
  - 初始化日志
  - 创建应用对象
  - 显示主窗口
- [x] 1.5.2 创建MainWindow类
  - 继承QMainWindow
  - 基本窗口配置（标题、尺寸）
- [x] 1.5.3 创建基础UI框架
  - 菜单栏
  - 状态栏

### 1.6 编译测试

- [x] 1.6.1 CMake配置项目
- [x] 1.6.2 编译Debug版本
- [x] 1.6.3 编译Release版本
- [x] 1.6.4 运行程序验证窗口显示
- [x] 1.6.5 配置Qt Test框架
- [x] 1.6.6 编译运行测试（0 tests通过）

## 验收标准

- [x] CMakeLists.txt和.pro文件存在且可编译
- [x] 目录结构完整（UI/Business/HAL/Config/Test）
- [x] thirdparty库准备完整
  - [x] fftw++ 包含头文件和源码
  - [x] qcustomplot 包含 .h 和 .cpp
  - [x] QtPDF 使用QPrinter替代
- [x] 程序可编译运行，显示主窗口
- [x] 日志系统正常工作，日志写入文件
- [x] Qt Test框架可运行（即使0 tests）
