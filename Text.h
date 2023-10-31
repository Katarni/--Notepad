//
// Created by Тимур Ахметзянов on 22.10.2023.
//

#pragma once
#include "header.h"


class Text {
 public:
  static std::vector<std::wstring*> toLines(std::wstring& str);
  static std::vector<std::wstring*> replace(std::wstring& str, std::wstring& from, std::wstring& to);
  static void removeZeros(std::wstring& str);
  static void removeBrackets(std::wstring& str);
  static void onlyGrades(std::wstring& str);
  static void replaceStars(std::wstring& str);
 private:
  inline static bool isDigit(wchar_t c) {
    return c >= '0' && c <= '9';
  }

  static std::wstring getNPlus(int n) {
    std::wstring s;
    while (n--) {
      s += '+';
    }
    return s;
  }
};
