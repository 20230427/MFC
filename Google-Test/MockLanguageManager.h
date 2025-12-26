// MockLanguageManager.h
#pragma once
#include "pch.h"

// 语言枚举 - 使用 enum class 提供更好的类型安全
enum class Language : int {
    CHINESE = 0,
    ENGLISH = 1
};

// 简化的LanguageManager类用于测试
class MockLanguageManager {
private:
    Language currentLang;
    std::map<std::wstring, std::map<Language, std::wstring>> strings;
    static MockLanguageManager* instance;

    MockLanguageManager() : currentLang(Language::CHINESE) {
        InitializeStrings();
    }

    void InitializeStrings() {
        // 中英文字符串映射
        strings[L"MENU_FILE"][Language::CHINESE] = L"文件(&F)";
        strings[L"MENU_FILE"][Language::ENGLISH] = L"&File";

        strings[L"MENU_EDIT"][Language::CHINESE] = L"编辑(&E)";
        strings[L"MENU_EDIT"][Language::ENGLISH] = L"&Edit";

        strings[L"MENU_VIEW"][Language::CHINESE] = L"视图(&V)";
        strings[L"MENU_VIEW"][Language::ENGLISH] = L"&View";

        strings[L"TOOL_PENCIL"][Language::CHINESE] = L"铅笔";
        strings[L"TOOL_PENCIL"][Language::ENGLISH] = L"Pencil";

        strings[L"TOOL_LINE"][Language::CHINESE] = L"直线";
        strings[L"TOOL_LINE"][Language::ENGLISH] = L"Line";

        strings[L"TOOL_RECTANGLE"][Language::CHINESE] = L"矩形";
        strings[L"TOOL_RECTANGLE"][Language::ENGLISH] = L"Rectangle";

        strings[L"TOOL_CIRCLE"][Language::CHINESE] = L"圆形";
        strings[L"TOOL_CIRCLE"][Language::ENGLISH] = L"Circle";
    }



public:
    static MockLanguageManager& GetInstance() {
        if (instance == nullptr) {
            instance = new MockLanguageManager();
        }
        return *instance;
    }

    void SetLanguage(Language lang) {
        currentLang = lang;
    }

    Language GetCurrentLanguage() const {
        return currentLang;
    }

    std::wstring GetString(const std::wstring& key) const {
        auto it = strings.find(key);
        if (it != strings.end()) {
            auto langIt = it->second.find(currentLang);
            if (langIt != it->second.end()) {
                return langIt->second;
            }
        }
        return key; // 如果找不到，返回原键值
    }

    // 测试辅助方法
    static void ResetInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

    // 析构函数
    ~MockLanguageManager() = default;
};

// 静态成员定义需要放在cpp文件中或者使用inline
inline MockLanguageManager* MockLanguageManager::instance = nullptr;

// 为了兼容，定义别名
using LanguageManager = MockLanguageManager;


