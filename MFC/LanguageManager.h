#pragma once

#include <map>
#include <string>

enum class Language
{
    Chinese = 0,
    English = 1,
    Japanese = 2
};

class CLanguageManager
{
public:
    static CLanguageManager& GetInstance();

    void SetLanguage(Language lang);
    Language GetCurrentLanguage() const { return m_currentLanguage; }

    CString GetString(UINT nID) const;
    void UpdateMenuText(CMenu* pMenu);

private:
    CLanguageManager();
    ~CLanguageManager() = default;

    void InitializeStrings();

    Language m_currentLanguage;
    std::map<Language, std::map<UINT, CString>> m_strings;

    // ½ûÖ¹¿½±´
    CLanguageManager(const CLanguageManager&) = delete;
    CLanguageManager& operator=(const CLanguageManager&) = delete;
};
