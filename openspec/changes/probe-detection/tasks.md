## 探头检测与激活

### 4.1 实现端口扫描功能

- [x] 4.1.1 创建Port结构体
  - port: QString (A/B/C/D)
  - status: PortStatus (Connected/Disconnected)
- [x] 4.1.2 创建PortScanner类
- [x] 4.1.3 实现scan方法遍历A/B/C/D
- [x] 4.1.4 实现checkPort单个端口检查

### 4.2 实现探头ID读取功能

- [x] 4.2.1 创建ProbeReader类
- [x] 4.2.2 实现readId方法
- [x] 4.2.3 实现ID格式验证
- [x] 4.2.4 实现ID回读校验

### 4.3 实现已知探头自动匹配

- [x] 4.3.1 创建ProbeInfo结构体
  - port, id, model, config, state
- [x] 4.3.2 实现isKnownProbe方法
- [x] 4.3.3 实现matchConfig自动匹配
- [x] 4.3.4 加载匹配的配置

### 4.4 实现未知探头处理向导

- [ ] 4.4.1 定义UnknownProbeAction枚举
- [ ] 4.4.2 实现BurnId操作
- [ ] 4.4.3 实现TemporaryConfig操作
- [ ] 4.4.4 创建探头选择UI接口

### 4.5 实现Probe_Activate封装

- [x] 4.5.1 创建ScriptLoader类
- [x] 4.5.2 实现activateProbe方法
- [x] 4.5.3 实现激活状态管理
- [x] 4.5.4 实现激活结果反馈

### 4.6 实现System_LoadScript封装

- [x] 4.6.1 定义脚本结构
- [x] 4.6.2 实现loadScript方法
- [x] 4.6.3 实现脚本验证
- [x] 4.6.4 实现脚本错误处理

### 4.7 单元测试

- [ ] 4.7.1 编写PortScanner测试
  - testScanPorts
- [ ] 4.7.2 编写ProbeReader测试
  - testReadId
  - testKnownProbeMatching
- [ ] 4.7.3 编写ProbeManager测试
  - testScanAndDetect
  - testActivateProbe
- [ ] 4.7.4 运行单元测试验证

## 验收标准

- [ ] 可扫描A/B/C/D端口并显示结果
- [ ] 可读取探头ID
- [ ] 已知探头可自动匹配配置
- [ ] 未知探头可选择烧录或临时配置
- [ ] 探头激活成功
- [ ] 脚本加载成功
- [ ] 所有单元测试通过
