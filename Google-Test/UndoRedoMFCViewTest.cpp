#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <memory>
#include <vector>
#include <stack>
#include <chrono>

// 避免Color冲突，使用命名空间
namespace DrawingColor {
    enum Color {
        RED = 0xFF0000,
        GREEN = 0x00FF00,
        BLUE = 0x0000FF,
        BLACK = 0x000000
    };
}

// 简化的绘图形状接口
class IDrawShape {
public:
    virtual ~IDrawShape() = default;
    virtual std::shared_ptr<IDrawShape> Clone() const = 0;
    virtual void Draw(void* pDC) = 0;
    virtual int GetId() const = 0;
};

// Mock绘图形状类
class MockDrawShape : public IDrawShape {
private:
    int id_;
    DrawingColor::Color color_;

public:
    MockDrawShape(int id, DrawingColor::Color color = DrawingColor::BLACK)
        : id_(id), color_(color) {
    }

    std::shared_ptr<IDrawShape> Clone() const override {
        return std::make_shared<MockDrawShape>(id_, color_);
    }

    void Draw(void* pDC) override {
        // 模拟绘制操作
    }

    int GetId() const override {
        return id_;
    }

    DrawingColor::Color GetColor() const {
        return color_;
    }
};

// 简化的命令UI类
class MockCmdUI {
public:
    bool m_bEnabled = true;
    unsigned int m_nID = 0;

    void Enable(bool bOn = true) {
        m_bEnabled = bOn;
    }
};

// 修复后的撤销/重做管理器类
class UndoRedoManager {
private:
    std::vector<std::shared_ptr<IDrawShape>> m_shapes;
    std::shared_ptr<IDrawShape> m_pCurrentShape;
    std::stack<std::vector<std::shared_ptr<IDrawShape>>> m_undoStack;
    std::stack<std::vector<std::shared_ptr<IDrawShape>>> m_redoStack;

    static const size_t MAX_UNDO_STACK_SIZE = 50;

    // 深拷贝形状列表的辅助函数
    std::vector<std::shared_ptr<IDrawShape>> CloneShapes(const std::vector<std::shared_ptr<IDrawShape>>& shapes) {
        std::vector<std::shared_ptr<IDrawShape>> cloned;
        for (const auto& shape : shapes) {
            if (shape) {
                cloned.push_back(shape->Clone());
            }
        }
        return cloned;
    }

public:
    UndoRedoManager() = default;
    ~UndoRedoManager() = default;

    // 公共接口
    void AddShape(std::shared_ptr<IDrawShape> shape) {
        if (shape) {
            m_shapes.push_back(shape);
        }
    }

    void ClearShapes() {
        m_shapes.clear();
    }

    size_t GetShapeCount() const {
        return m_shapes.size();
    }

    const std::vector<std::shared_ptr<IDrawShape>>& GetShapes() const {
        return m_shapes;
    }

    void SetCurrentShape(std::shared_ptr<IDrawShape> shape) {
        m_pCurrentShape = shape;
    }

    std::shared_ptr<IDrawShape> GetCurrentShape() const {
        return m_pCurrentShape;
    }

    size_t GetUndoStackSize() const {
        return m_undoStack.size();
    }

    size_t GetRedoStackSize() const {
        return m_redoStack.size();
    }

    // 修复后的保存状态方法
    void SaveState() {
        // 克隆当前状态
        std::vector<std::shared_ptr<IDrawShape>> currentState = CloneShapes(m_shapes);
        m_undoStack.push(currentState);

        // 限制撤销栈大小 - 修复栈大小限制逻辑
        while (m_undoStack.size() > MAX_UNDO_STACK_SIZE) {
            // 创建临时栈来保存需要保留的元素
            std::stack<std::vector<std::shared_ptr<IDrawShape>>> tempStack;

            // 保存除了最底层的所有元素
            for (size_t i = 0; i < MAX_UNDO_STACK_SIZE - 1; ++i) {
                if (!m_undoStack.empty()) {
                    tempStack.push(m_undoStack.top());
                    m_undoStack.pop();
                }
            }

            // 清空原栈
            while (!m_undoStack.empty()) {
                m_undoStack.pop();
            }

            // 将元素放回，但顺序是反的，需要再次反转
            std::stack<std::vector<std::shared_ptr<IDrawShape>>> tempStack2;
            while (!tempStack.empty()) {
                tempStack2.push(tempStack.top());
                tempStack.pop();
            }

            while (!tempStack2.empty()) {
                m_undoStack.push(tempStack2.top());
                tempStack2.pop();
            }
        }

        // 清空重做栈（新操作会清除重做历史）
        while (!m_redoStack.empty()) {
            m_redoStack.pop();
        }
    }

    // 修复后的撤销操作
    bool Undo() {
        if (m_undoStack.empty()) {
            return false;
        }

        // 保存当前状态到重做栈
        std::vector<std::shared_ptr<IDrawShape>> currentState = CloneShapes(m_shapes);
        m_redoStack.push(currentState);

        // 恢复上一个状态
        auto restoredState = m_undoStack.top();
        m_undoStack.pop();

        // 更新当前形状列表
        m_shapes = restoredState;

        return true;
    }

    // 修复后的重做操作
    bool Redo() {
        if (m_redoStack.empty()) {
            return false;
        }

        // 保存当前状态到撤销栈
        std::vector<std::shared_ptr<IDrawShape>> currentState = CloneShapes(m_shapes);
        m_undoStack.push(currentState);

        // 恢复重做状态
        auto restoredState = m_redoStack.top();
        m_redoStack.pop();

        // 更新当前形状列表
        m_shapes = restoredState;

        return true;
    }

    // 清除所有内容
    void ClearAll() {
        SaveState(); // 保存当前状态以便撤销
        m_shapes.clear();
        m_pCurrentShape.reset();
    }

    // UI状态更新
    bool CanUndo() const {
        return !m_undoStack.empty();
    }

    bool CanRedo() const {
        return !m_redoStack.empty();
    }

    void UpdateUndoUI(MockCmdUI* pCmdUI) {
        if (pCmdUI) {
            pCmdUI->Enable(CanUndo());
        }
    }

    void UpdateRedoUI(MockCmdUI* pCmdUI) {
        if (pCmdUI) {
            pCmdUI->Enable(CanRedo());
        }
    }
};

// 测试固件
class UndoRedoManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        manager_ = std::make_unique<UndoRedoManager>();
    }

    void TearDown() override {
        manager_.reset();
    }

    std::unique_ptr<UndoRedoManager> manager_;
};

// 基本状态测试
TEST_F(UndoRedoManagerTest, InitialState) {
    EXPECT_TRUE(manager_->GetShapes().empty());
    EXPECT_EQ(manager_->GetShapeCount(), 0);
    EXPECT_EQ(manager_->GetUndoStackSize(), 0);
    EXPECT_EQ(manager_->GetRedoStackSize(), 0);
    EXPECT_EQ(manager_->GetCurrentShape(), nullptr);
    EXPECT_FALSE(manager_->CanUndo());
    EXPECT_FALSE(manager_->CanRedo());
}

// SaveState功能测试
TEST_F(UndoRedoManagerTest, SaveState_EmptyShapes) {
    manager_->SaveState();

    EXPECT_EQ(manager_->GetUndoStackSize(), 1);
    EXPECT_FALSE(manager_->CanRedo()); // 新操作清除重做历史
}

TEST_F(UndoRedoManagerTest, SaveState_WithShapes) {
    // 添加一些形状
    auto shape1 = std::make_shared<MockDrawShape>(1, DrawingColor::RED);
    auto shape2 = std::make_shared<MockDrawShape>(2, DrawingColor::BLUE);

    manager_->AddShape(shape1);
    manager_->AddShape(shape2);

    manager_->SaveState();

    EXPECT_EQ(manager_->GetUndoStackSize(), 1);
    EXPECT_EQ(manager_->GetShapeCount(), 2);
    EXPECT_TRUE(manager_->CanUndo());
}

TEST_F(UndoRedoManagerTest, SaveState_ClearsRedoStack) {
    // 创建一些撤销/重做历史
    manager_->SaveState(); // 空状态

    auto shape = std::make_shared<MockDrawShape>(1);
    manager_->AddShape(shape);
    manager_->SaveState(); // 有形状的状态

    manager_->Undo(); // 撤销，创建重做历史
    EXPECT_TRUE(manager_->CanRedo());

    // 新的保存操作应该清除重做历史
    manager_->SaveState();
    EXPECT_FALSE(manager_->CanRedo());
}

// 撤销功能测试
TEST_F(UndoRedoManagerTest, Undo_EmptyStack) {
    bool result = manager_->Undo();

    EXPECT_FALSE(result);
    EXPECT_EQ(manager_->GetShapeCount(), 0);
    EXPECT_EQ(manager_->GetUndoStackSize(), 0);
    EXPECT_EQ(manager_->GetRedoStackSize(), 0);
}

TEST_F(UndoRedoManagerTest, Undo_WithHistory) {
    // 准备初始状态 - 空的shapes
    manager_->SaveState();

    // 添加形状
    auto shape1 = std::make_shared<MockDrawShape>(1);
    manager_->AddShape(shape1);

    EXPECT_EQ(manager_->GetShapeCount(), 1);
    EXPECT_EQ(manager_->GetUndoStackSize(), 1); // 只有初始的空状态
    EXPECT_EQ(manager_->GetRedoStackSize(), 0);

    // 执行撤销
    bool result = manager_->Undo();

    EXPECT_TRUE(result);
    EXPECT_EQ(manager_->GetShapeCount(), 0); // 恢复到空状态
    EXPECT_EQ(manager_->GetUndoStackSize(), 0); // 撤销栈为空
    EXPECT_EQ(manager_->GetRedoStackSize(), 1); // 重做栈有当前状态
}

TEST_F(UndoRedoManagerTest, Undo_MultipleOperations) {
    // 保存初始空状态
    manager_->SaveState();

    // 添加第一个形状并保存状态
    auto shape1 = std::make_shared<MockDrawShape>(1);
    manager_->AddShape(shape1);
    manager_->SaveState();

    // 添加第二个形状并保存状态
    auto shape2 = std::make_shared<MockDrawShape>(2);
    manager_->AddShape(shape2);
    manager_->SaveState();

    // 添加第三个形状（但不保存状态）
    auto shape3 = std::make_shared<MockDrawShape>(3);
    manager_->AddShape(shape3);

    EXPECT_EQ(manager_->GetShapeCount(), 3);
    EXPECT_EQ(manager_->GetUndoStackSize(), 3); // 空状态 + 1个形状状态 + 2个形状状态

    // 撤销一次：应该回到2个形状的状态
    bool result1 = manager_->Undo();
    EXPECT_TRUE(result1);
    EXPECT_EQ(manager_->GetShapeCount(), 2);
    EXPECT_EQ(manager_->GetUndoStackSize(), 2);
    EXPECT_EQ(manager_->GetRedoStackSize(), 1);

    // 撤销二次：应该回到1个形状的状态
    bool result2 = manager_->Undo();
    EXPECT_TRUE(result2);
    EXPECT_EQ(manager_->GetShapeCount(), 1);
    EXPECT_EQ(manager_->GetUndoStackSize(), 1);
    EXPECT_EQ(manager_->GetRedoStackSize(), 2);
}

// 重做功能测试
TEST_F(UndoRedoManagerTest, Redo_EmptyStack) {
    bool result = manager_->Redo();

    EXPECT_FALSE(result);
    EXPECT_EQ(manager_->GetShapeCount(), 0);
    EXPECT_EQ(manager_->GetUndoStackSize(), 0);
    EXPECT_EQ(manager_->GetRedoStackSize(), 0);
}

TEST_F(UndoRedoManagerTest, Redo_AfterUndo) {
    // 准备测试数据
    manager_->SaveState(); // 保存空状态

    auto shape = std::make_shared<MockDrawShape>(1);
    manager_->AddShape(shape);

    EXPECT_EQ(manager_->GetShapeCount(), 1);
    EXPECT_EQ(manager_->GetRedoStackSize(), 0);

    // 撤销
    bool undoResult = manager_->Undo();
    EXPECT_TRUE(undoResult);
    EXPECT_EQ(manager_->GetShapeCount(), 0); // 回到空状态
    EXPECT_EQ(manager_->GetRedoStackSize(), 1);

    // 重做
    bool redoResult = manager_->Redo();
    EXPECT_TRUE(redoResult);
    EXPECT_EQ(manager_->GetShapeCount(), 1); // 恢复到有一个形状
    EXPECT_EQ(manager_->GetUndoStackSize(), 1); // 现在有空状态可以撤销
    EXPECT_EQ(manager_->GetRedoStackSize(), 0); // 重做栈为空
}

TEST_F(UndoRedoManagerTest, UndoRedo_CompleteSequence) {
    // 完整的撤销重做序列测试

    // 1. 保存初始空状态
    manager_->SaveState();

    // 2. 添加形状并保存
    auto shape1 = std::make_shared<MockDrawShape>(1);
    manager_->AddShape(shape1);
    manager_->SaveState();

    auto shape2 = std::make_shared<MockDrawShape>(2);
    manager_->AddShape(shape2);

    EXPECT_EQ(manager_->GetShapeCount(), 2);

    // 3. 撤销一次：应该回到只有1个形状的状态
    manager_->Undo();
    EXPECT_EQ(manager_->GetShapeCount(), 1);

    // 4. 重做一次：应该回到2个形状的状态
    manager_->Redo();
    EXPECT_EQ(manager_->GetShapeCount(), 2);

    // 5. 撤销两次：回到1个形状，再回到0个形状
    manager_->Undo(); // 回到1个形状
    EXPECT_EQ(manager_->GetShapeCount(), 1);

    manager_->Undo(); // 回到0个形状
    EXPECT_EQ(manager_->GetShapeCount(), 0);

    // 6. 重做两次：回到1个形状，再回到2个形状
    manager_->Redo(); // 回到1个形状
    EXPECT_EQ(manager_->GetShapeCount(), 1);

    manager_->Redo(); // 回到2个形状
    EXPECT_EQ(manager_->GetShapeCount(), 2);
}

// 修复栈大小限制测试
TEST_F(UndoRedoManagerTest, EdgeCase_StackLimitBoundary) {
    auto shape = std::make_shared<MockDrawShape>(1);
    manager_->AddShape(shape);

    // 保存恰好50个状态
    for (int i = 0; i < 50; ++i) {
        manager_->SaveState();
    }

    EXPECT_EQ(manager_->GetUndoStackSize(), 50);

    // 再保存一个，应该限制为50
    manager_->SaveState();
    EXPECT_LE(manager_->GetUndoStackSize(), 50);
}

// UI状态更新测试
TEST_F(UndoRedoManagerTest, UpdateUI_InitialState) {
    MockCmdUI undoCmdUI, redoCmdUI;

    manager_->UpdateUndoUI(&undoCmdUI);
    manager_->UpdateRedoUI(&redoCmdUI);

    EXPECT_FALSE(undoCmdUI.m_bEnabled);
    EXPECT_FALSE(redoCmdUI.m_bEnabled);
}

TEST_F(UndoRedoManagerTest, UpdateUI_AfterSaveState) {
    manager_->SaveState();

    MockCmdUI undoCmdUI, redoCmdUI;

    manager_->UpdateUndoUI(&undoCmdUI);
    manager_->UpdateRedoUI(&redoCmdUI);

    EXPECT_TRUE(undoCmdUI.m_bEnabled);
    EXPECT_FALSE(redoCmdUI.m_bEnabled);
}

TEST_F(UndoRedoManagerTest, UpdateUI_AfterUndo) {
    manager_->SaveState(); // 空状态

    auto shape = std::make_shared<MockDrawShape>(1);
    manager_->AddShape(shape);

    manager_->Undo(); // 撤销到空状态

    MockCmdUI undoCmdUI, redoCmdUI;

    manager_->UpdateUndoUI(&undoCmdUI);
    manager_->UpdateRedoUI(&redoCmdUI);

    EXPECT_FALSE(undoCmdUI.m_bEnabled); // 撤销栈为空
    EXPECT_TRUE(redoCmdUI.m_bEnabled);  // 有重做历史
}

// ClearAll功能测试
TEST_F(UndoRedoManagerTest, ClearAll_WithShapes) {
    // 添加一些形状
    for (int i = 1; i <= 3; ++i) {
        auto shape = std::make_shared<MockDrawShape>(i);
        manager_->AddShape(shape);
    }

    auto currentShape = std::make_shared<MockDrawShape>(99);
    manager_->SetCurrentShape(currentShape);

    EXPECT_EQ(manager_->GetShapeCount(), 3);
    EXPECT_NE(manager_->GetCurrentShape(), nullptr);

    manager_->ClearAll();

    EXPECT_EQ(manager_->GetShapeCount(), 0);
    EXPECT_EQ(manager_->GetCurrentShape(), nullptr);
    EXPECT_TRUE(manager_->CanUndo()); // ClearAll操作可以被撤销
}

TEST_F(UndoRedoManagerTest, ClearAll_CanBeUndone) {
    // 添加形状
    auto shape1 = std::make_shared<MockDrawShape>(1);
    auto shape2 = std::make_shared<MockDrawShape>(2);
    manager_->AddShape(shape1);
    manager_->AddShape(shape2);

    EXPECT_EQ(manager_->GetShapeCount(), 2);

    manager_->ClearAll();
    EXPECT_EQ(manager_->GetShapeCount(), 0);

    // 撤销ClearAll操作
    bool result = manager_->Undo();
    EXPECT_TRUE(result);
    EXPECT_EQ(manager_->GetShapeCount(), 2);
}

// 边界条件测试
TEST_F(UndoRedoManagerTest, EdgeCase_NullShapes) {
    // 测试添加空指针
    manager_->AddShape(nullptr);
    EXPECT_EQ(manager_->GetShapeCount(), 0);

    // 添加有效形状
    auto shape = std::make_shared<MockDrawShape>(1);
    manager_->AddShape(shape);
    EXPECT_EQ(manager_->GetShapeCount(), 1);

    // 再次添加空指针
    manager_->AddShape(nullptr);
    EXPECT_EQ(manager_->GetShapeCount(), 1);
}

// 性能测试
TEST_F(UndoRedoManagerTest, Performance_LargeNumberOfShapes) {
    const int shapeCount = 1000;
    for (int i = 0; i < shapeCount; ++i) {
        auto shape = std::make_shared<MockDrawShape>(i);
        manager_->AddShape(shape);
    }

    auto start = std::chrono::high_resolution_clock::now();

    manager_->SaveState();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    EXPECT_LT(duration.count(), 1000); // 应该在1秒内完成
}
