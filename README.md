# Google Test 图形绘制项目

## 项目概述

本项目是一个基于 MFC (Microsoft Foundation Classes) 的图形绘制应用程序，集成了完整的单元测试框架。项目采用命令模式设计，支持基本图形绘制功能，并使用 Google Test 框架进行全面的单元测试。

## 项目特性

- **图形绘制功能**：支持直线、矩形、椭圆等基本图形绘制
- **颜色和线宽设置**：可自定义画笔颜色、线宽和样式
- **命令模式设计**：支持撤销/重做功能
- **完整单元测试**：使用 Google Test 框架进行测试覆盖
- **模拟测试环境**：提供 MockCDC 类用于测试图形绘制逻辑

## 项目结构

```
Project/
├── MFC/                          # MFC 主项目
│   ├── MFC.h                     # 主应用程序头文件
│   ├── MFC.cpp                   # 主应用程序实现
│   ├── MFCDoc.h/.cpp            # 文档类
│   ├── MFCView.h/.cpp           # 视图类
│   ├── MainFrm.h/.cpp           # 主框架窗口
│   ├── CommandManager.h/.cpp     # 命令管理器
│   ├── DrawingCommand.h/.cpp     # 绘图命令类
│   ├── framework.h               # 框架头文件
│   ├── pch.h/.cpp               # 预编译头
│   ├── Resource.h                # 资源定义
│   ├── MFC.rc                    # 资源文件
│   └── res/                      # 资源目录
└── Google-Test/                  # Google Test 项目
    ├── pch.h/.cpp               # 测试预编译头
    ├── MockCDC.h/.cpp           # 模拟 CDC 类
    ├── BasicDrawTest.cpp         # 基础绘制测试
    ├── ColorAndLineWidthTest.cpp # 颜色和线宽测试
    ├── LanguageManagerTest.cpp # 语言切换测试
    ├── UndoRedoMFCViewTest.cpp # 撤销和重做测试
    ├── DrawShapeTest.cpp         # 图形绘制测试
    └── CommandManagerTest.cpp    # 命令管理器测试
```

## 核心类介绍

### 1. MFC 主项目类

#### CMFCView
- **功能**：主要的绘图视图类
- **特性**：
  - 处理鼠标输入事件
  - 执行绘图命令
  - 管理命令历史
  - 支持撤销/重做操作

#### CommandManager
- **功能**：命令模式管理器
- **特性**：
  - 执行绘图命令
  - 维护命令历史栈
  - 支持撤销/重做操作
  - 命令历史大小限制

#### DrawingCommand 系列
- **LineCommand**：直线绘制命令
- **RectangleCommand**：矩形绘制命令
- **EllipseCommand**：椭圆绘制命令

### 2. 测试项目类

#### MockCDC
- **功能**：模拟 Windows CDC 类用于测试
- **特性**：
  - 记录所有绘图操作
  - 模拟画笔和画刷状态
  - 提供查询接口用于验证
  - 支持清空操作

## 环境要求

### 开发环境
- **Visual Studio 2022**
- **Windows 10**
- **C++17 标准**

### 依赖项
- **MFC (Microsoft Foundation Classes)**
- **Google Test 框架**
- **Windows SDK**

## 编译与运行

### 1. 克隆项目
```bash
git clone <repository-url>
cd MFC-Drawing-Project
```

### 2. 安装 Google Test
可以通过以下方式之一安装：

#### 方法一：通过 vcpkg
```bash
vcpkg install gtest
```

#### 方法二：手动下载编译
1. 从 [Google Test GitHub](https://github.com/google/googletest) 下载源码
2. 使用 CMake 编译
3. 将库文件复制到项目目录

### 3. 配置项目
1. 打开 Visual Studio
2. 加载解决方案文件 `MFC.sln`
3. 配置项目属性：
   - 确保包含 Google Test 头文件路径
   - 链接 Google Test 库文件
   - 设置正确的运行时库

### 4. 编译
1. 选择编译配置（Debug/Release）
2. 编译 MFC 主项目
3. 编译 Google-Test 项目

### 5. 运行
- **运行主程序**：启动 MFC 项目
- **运行测试**：启动 Google-Test 项目

## 测试说明

### 测试覆盖范围

#### 1. BasicDrawTest.cpp
- **测试内容**：基础绘制功能
- **覆盖范围**：
  - 基本图形绘制
  - 坐标设置
  - 绘制状态验证

#### 2. ColorAndLineWidthTest.cpp
- **测试内容**：颜色和线宽功能
- **覆盖范围**：
  - 画笔颜色设置
  - 画刷颜色设置
  - 线宽设置
  - 画笔样式设置
  - 综合属性测试

#### 3. DrawShapeTest.cpp
- **测试内容**：图形绘制功能
- **覆盖范围**：
  - 直线绘制
  - 矩形绘制
  - 椭圆绘制
  - 多图形绘制
  - 边界值测试

#### 4. CommandManagerTest.cpp
- **测试内容**：命令管理功能
- **覆盖范围**：
  - 命令执行
  - 撤销操作
  - 重做操作
  - 命令历史管理
  - 边界情况处理

### 运行测试
```bash
# 在 Visual Studio 中
1. 设置 Google-Test 为启动项目
2. 按 F5 运行测试
3. 查看测试输出结果

# 命令行运行
Google-Test.exe
```

### 测试结果示例
```
[==========] Running 45 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 8 tests from BasicDrawTest
[ RUN      ] BasicDrawTest.SetPenColor
[       OK ] BasicDrawTest.SetPenColor (0 ms)
...
[----------] 8 tests from BasicDrawTest (2 ms total)
...
[==========] 45 tests from 4 test suites ran. (15 ms total)
[  PASSED  ] 45 tests.
```

## 使用说明

### 主程序使用
1. **启动程序**：运行 MFC.exe
2. **绘制图形**：
   - 使用鼠标绘制直线、矩形、椭圆
   - 通过菜单或工具栏选择绘图工具
   - 设置颜色和线宽属性
3. **撤销重做**：
   - Ctrl+Z：撤销上一步操作
   - Ctrl+Y：重做操作

### 开发扩展
要添加新的图形类型：

1. **创建命令类**：
```cpp
class NewShapeCommand : public DrawingCommand {
    // 实现必要的虚函数
};
```

2. **添加到视图类**：
```cpp
void CMFCView::DrawNewShape(/* parameters */) {
    auto command = std::make_unique<NewShapeCommand>(/* args */);
    m_commandManager.ExecuteCommand(std::move(command));
}
```

3. **编写测试**：
```cpp
TEST_F(DrawShapeTest, DrawNewShape) {
    // 测试新图形绘制功能
}
```

## 设计模式

### 1. 命令模式 (Command Pattern)
- **优点**：支持撤销/重做、命令队列、日志记录
- **实现**：DrawingCommand 抽象基类及其具体实现

### 2. 模拟对象模式 (Mock Object Pattern)
- **优点**：隔离测试、可控环境、快速执行
- **实现**：MockCDC 类模拟真实的 CDC 对象

### 3. MVC 模式 (Model-View-Controller)
- **Model**：CMFCDoc 文档类
- **View**：CMFCView 视图类
- **Controller**：CommandManager 命令管理器

## 常见问题

### Q1: 编译错误 "无法找到 gtest.h"
**解决方案**：
1. 检查 Google Test 是否正确安装
2. 验证项目属性中的包含目录设置
3. 确保链接了正确的库文件

### Q2: 测试运行失败
**解决方案**：
1. 检查预编译头设置
2. 验证所有必要的头文件是否包含
3. 确保 MockCDC 类正确实现

### Q3: MFC 程序无法启动
**解决方案**：
1. 检查 MFC 库是否正确链接
2. 验证资源文件是否存在
3. 确保运行时库设置正确

## 性能优化

### 1. 绘图性能
- 使用双缓冲技术减少闪烁
- 优化重绘区域计算
- 合并连续的绘图操作

### 2. 内存管理
- 限制命令历史大小
- 使用智能指针管理内存
- 及时释放不需要的资源

### 3. 测试性能
- 使用快速的 MockCDC 替代真实 CDC
- 并行运行独立测试
- 缓存测试数据

## 扩展建议

### 短期改进
1. **添加更多图形类型**：多边形、曲线、文本
2. **增强属性设置**：渐变色、透明度、阴影
3. **改进用户界面**：工具面板、属性窗口

### 长期规划
1. **文件格式支持**：保存/加载绘图文件
2. **图层管理**：支持多图层编辑
3. **插件架构**：支持第三方扩展
4. **网络协作**：多用户协同编辑

### 代码规范
- 遵循项目现有的命名约定
- 添加适当的注释和文档
- 确保新代码有对应的测试

### 提交流程
1. Fork 项目仓库
2. 创建特性分支
3. 实现功能并添加测试
4. 提交 Pull Request
5. 通过代码审查

### 测试要求
- 新功能必须有对应的单元测试
- 测试覆盖率不低于 85%
- 所有测试必须通过



---

**感谢使用本项目！如有问题请及时反馈。**
