这份文档将基于你提供的工程结构（一个典型的 MFC 文档/视图架构应用及其配套的 Google Test 单元测试工程）进行编写。

---

# MFC 绘图与多语言管理系统 - 项目讲解文档

本解决方案采用 **C++** 编写，结合了 **MFC (Microsoft Foundation Classes)** 框架构建用户界面，并集成 **Google Test (gtest)** 框架进行自动化单元测试。

---

## 🛠️ 核心架构

项目采用典型的“双工程”模式，确保业务逻辑与测试逻辑的分离。

### 1. MFC 主项目 (Core Application)

基于 **MDI/SDI (文档/视图)** 架构，负责业务逻辑与界面展示。

* **文档/视图架构 (`MFCDoc.h/cpp`, `MFCView.h/cpp`)**:
* `MFCDoc`: 负责数据的存储与序列化。
* `MFCView`: 负责图形的绘制与用户交互，支持撤销重做（Undo/Redo）逻辑的集成。


* **绘图核心 (`DrawShape.h/cpp`)**: 封装了形状绘制的底层逻辑，支持颜色与线宽的自定义。
* **多语言管理器 (`LanguageManager.h/cpp`)**: 负责程序的国际化，管理动态语言切换。
* **框架与资源 (`MainFrm.h`, `Resource.h`)**: 管理主窗口外观、菜单、工具栏以及资源 ID。

### 2. Google-Test 项目 (Unit Testing)

负责验证核心组件的稳定性和准确性。

* **Mock 对象 (`MockLanguageManager.h`)**: 使用 gMock 模拟复杂的语言管理器行为，实现解耦测试。
* **功能测试模块**:
* `ColorAndLineWidthTest.cpp`: 验证颜色选择与线宽设置逻辑。
* `DrawShapeTest.cpp`: 验证形状生成、计算与边界检查逻辑。
* `LanguageManagerTest.cpp`: 验证多语言字符串查找与加载。
* `UndoRedoMFCViewTest.cpp`: 针对视图层的“撤销/重做”功能进行行为测试。



---

## 📂 详细目录结构

### **MFC 项目文件详解**

| 文件名 | 类型 | 说明 |
| --- | --- | --- |
| `MFC.h/cpp` | 应用类 | 项目的入口，初始化 MFC 运行环境。 |
| `DrawShape.h/cpp` | 业务逻辑 | 核心绘图算法，定义形状属性（颜色、粗细）。 |
| `LanguageManager.h/cpp` | 功能模块 | 管理多语言资源加载。 |
| `MainFrm.h/cpp` | 视图容器 | 主框架窗口，管理状态栏和工具栏。 |
| `pch.h/cpp` | 预编译头 | 提高编译速度，包含 `afxwin.h` 等常用头文件。 |

### **Google-Test 项目文件详解**

| 文件名 | 说明 |
| --- | --- |
| `gtest-all.cc / gmock-all.cc` | 单元测试框架核心库。 |
| `test.cpp` | 测试工程入口（包含 `main` 函数）。 |
| `packages.config` | NuGet 插件配置，用于管理 gtest 依赖。 |

---

## 🚀 关键流程说明

### **1. 如何运行测试**

1. 在 Visual Studio 中，将 `Google-Test` 设为 **启动项目**。
2. 编译并运行 (F5)。控制台将输出所有测试用例的执行结果。
3. 通过测试驱动开发 (TDD) 的方式，在修改 `DrawShape` 逻辑后，通过 `DrawShapeTest` 确保没有引入 Bug。

### **2. 绘图与撤销重做逻辑**

系统在 `MFCView` 中捕获鼠标事件，调用 `DrawShape` 进行渲染，并将操作压入撤销栈。`UndoRedoMFCViewTest.cpp` 专门模拟了这一过程，确保在高频操作下内存管理与逻辑状态的正确性。

---

## ⚙️ 环境配置要求

* **IDE**: Visual Studio 2019/2022
* **工作负载**:
* 使用 C++ 的桌面开发
* 用于最新 v14x 生成工具的 C++ MFC (x86 和 x64)


* **依赖管理**: 项目通过 NuGet 管理 `Google Test` 插件，首次编译前请确保自动还原包。

---

**你想针对某个具体的类（例如 `LanguageManager` 或 `DrawShape`）编写更详细的函数级 API 文档吗？**
