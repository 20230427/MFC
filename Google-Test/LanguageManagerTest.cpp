// LanguageManagerTest.cpp
#include "pch.h"
#include "MockLanguageManager.h"

class LanguageManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // ÖØÖÃµ¥ÀýÊµÀýÒÔÈ·±£Ã¿¸ö²âÊÔµÄ¶ÀÁ¢ÐÔ
        MockLanguageManager::ResetInstance();
        manager = &MockLanguageManager::GetInstance();
    }

    void TearDown() override {
        MockLanguageManager::ResetInstance();
    }

    MockLanguageManager* manager;
};

// ²âÊÔµ¥ÀýÄ£Ê½
TEST_F(LanguageManagerTest, SingletonPattern) {
    MockLanguageManager& instance1 = MockLanguageManager::GetInstance();
    MockLanguageManager& instance2 = MockLanguageManager::GetInstance();

    EXPECT_EQ(&instance1, &instance2);
}

// ²âÊÔÄ¬ÈÏÓïÑÔ
TEST_F(LanguageManagerTest, DefaultLanguage) {
    EXPECT_EQ(manager->GetCurrentLanguage(), Language::CHINESE);
}

// ²âÊÔÓïÑÔÇÐ»»
TEST_F(LanguageManagerTest, LanguageSwitching) {
    manager->SetLanguage(Language::ENGLISH);
    EXPECT_EQ(manager->GetCurrentLanguage(), Language::ENGLISH);

    manager->SetLanguage(Language::CHINESE);
    EXPECT_EQ(manager->GetCurrentLanguage(), Language::CHINESE);
}

// ²âÊÔ×Ö·û´®»ñÈ¡ - ÖÐÎÄ
TEST_F(LanguageManagerTest, GetStringChinese) {
    manager->SetLanguage(Language::CHINESE);

    EXPECT_EQ(manager->GetString(L"MENU_FILE"), L"ÎÄ¼þ(&F)");
    EXPECT_EQ(manager->GetString(L"MENU_EDIT"), L"±à¼­(&E)");
    EXPECT_EQ(manager->GetString(L"MENU_VIEW"), L"ÊÓÍ¼(&V)");
    EXPECT_EQ(manager->GetString(L"TOOL_PENCIL"), L"Ç¦±Ê");
    EXPECT_EQ(manager->GetString(L"TOOL_LINE"), L"Ö±Ïß");
}

// ²âÊÔ×Ö·û´®»ñÈ¡ - Ó¢ÎÄ
TEST_F(LanguageManagerTest, GetStringEnglish) {
    manager->SetLanguage(Language::ENGLISH);

    EXPECT_EQ(manager->GetString(L"MENU_FILE"), L"&File");
    EXPECT_EQ(manager->GetString(L"MENU_EDIT"), L"&Edit");
    EXPECT_EQ(manager->GetString(L"MENU_VIEW"), L"&View");
    EXPECT_EQ(manager->GetString(L"TOOL_PENCIL"), L"Pencil");
    EXPECT_EQ(manager->GetString(L"TOOL_LINE"), L"Line");
}

// ²âÊÔ²»´æÔÚµÄ¼ü
TEST_F(LanguageManagerTest, NonExistentKey) {
    std::wstring result = manager->GetString(L"NON_EXISTENT_KEY");
    EXPECT_EQ(result, L"NON_EXISTENT_KEY");
}

// ²âÊÔÓïÑÔÇÐ»»ºó×Ö·û´®±ä»¯
TEST_F(LanguageManagerTest, StringChangeAfterLanguageSwitch) {
    manager->SetLanguage(Language::CHINESE);
    std::wstring chineseText = manager->GetString(L"TOOL_PENCIL");

    manager->SetLanguage(Language::ENGLISH);
    std::wstring englishText = manager->GetString(L"TOOL_PENCIL");

    EXPECT_NE(chineseText, englishText);
    EXPECT_EQ(chineseText, L"Ç¦±Ê");
    EXPECT_EQ(englishText, L"Pencil");
}
