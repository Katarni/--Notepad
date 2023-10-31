//
// Created by Тимур Ахметзянов on 22.10.2023.
//

#pragma once
#include "Text.h"


class Pad : public QMainWindow {
  Q_OBJECT

 public:
  Pad(int width, int height);

  void render();

 private slots:
  void insertAfterLine();
  void multiInsertAfterLine();
  void eraseLine();
  void replaceSymbol();
  void insertSubSeq();
  void replaceSubSeq();
  void removeZeros();
  void onlyGradesNums();
  void replaceStars();
  void removeBrackets();
  void saveToFile();
  void loadFromFile();

 private:
  int win_width_, win_height_;

  QWidget* window_;
  QWidget* buttons_lbl_ver_;
  QWidget* buttons_lbl_hor_;
  QTextBrowser* text_win_;
  QTextEdit* text_ent_;
  QLabel* header_holder;
  QLabel* description_header;

  QPushButton* save_btn_;
  QPushButton* load_btn_;

  std::vector<std::wstring*> lines_;
  std::vector<QPushButton*> buttons_;

  void setButtons();
  void showText();
};
