//
// Created by Тимур Ахметзянов on 22.10.2023.
//

#include "Text.h"

std::vector<std::wstring*> Text::toLines(std::wstring &str) {
  std::vector<std::wstring*> lines;
  int sz = int(str.size()) - (str[str.size() - 1] == '\n'), n = 0;
  while (sz > 0) {
    std::wstring s = std::wstring(str.begin() + 70 * n,
                                  str.begin() + 70 * n + std::min(70, sz))
                                          + wchar_t('\n');
    lines.push_back(new std::wstring(s));
    ++n;
    sz -= 70;
  }
  return lines;
}

std::vector<std::wstring*> Text::replace(std::wstring& str, std::wstring& from, std::wstring& to) {
  int start = 0, idx = 0;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == from[idx]) {
      if (idx == 0) start = i;
      ++idx;

      if (idx == from.size()) {
        str.erase(start, from.size());
        str.insert(start, to);
        i = start + int(to.size()) - 2;
      }
    } else {
      idx = 0;
    }
  }

  std::vector<std::wstring*> strs = toLines(str);
  return strs;
}

void Text::removeZeros(std::wstring& str) {
  bool remove = true;
  for (int i = 0; i < str.size();) {
    if (str[i] == '0') {
      if (i == str.size() - 1 || !isDigit(str[i + 1]) || !remove) {
        ++i;
        continue;
      }
      str.erase(str.begin() + i);
      continue;
    }

    if (str[i] > '0' && str[i] <= '9') {
      remove = false;
    } else {
      remove = true;
    }

    ++i;
  }
}

void Text::removeBrackets(std::wstring &str) {
  int start = 0;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '{') {
      start = i;
    }
    if (str[i] == '}') {
      int len = i - start;
      i -= len;
      str.erase(start, len + 1);
    }
  }
}

void Text::onlyGrades(std::wstring &str) {
  int start = !isDigit(str[0]), len = isDigit(str[0]);
  bool remove = false;

  for (int i = 1; i < str.size(); ++i) {
    if (isDigit(str[i])) {
      if (len == 0) {
        start = i;
      }
      if (isDigit(str[i - 1]) && str[i - 1] >= str[i]) {
        remove = true;
      }
      ++len;
    } else {
      if (remove) {
        i -= len;
        str.erase(start, len);
        remove = false;
      }
      len = 0;
    }
  }
}
