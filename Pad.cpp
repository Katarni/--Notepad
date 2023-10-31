//
// Created by Тимур Ахметзянов on 22.10.2023.
//

#include "Pad.h"

Pad::Pad(int width, int height) : win_width_(width), win_height_(height) {
  window_ = new QMainWindow();
  window_->setFixedSize(win_width_, win_height_);
  window_->setWindowTitle("--Notepad");
  window_->setStyleSheet("QWidget { background-color: #eee; }");

  header_holder = new QLabel(window_);
  header_holder->setFixedSize(int(win_width_ * 0.18), int(win_height_ * 0.05) + 10);
  header_holder->move(int(win_width_ * 0.4) + 20, 0);
  QFont header_font = header_holder->font();
  header_font.setPixelSize(28);
  header_font.setBold(true);
  header_holder->setFont(header_font);
  header_holder->setText("--Notepad");
  header_holder->setStyleSheet("QLabel { color: #000; }");

  description_header = new QLabel(window_);
  description_header->setFixedSize(int(win_width_ * 0.3), int(win_height_ * 0.05) + 10);
  description_header->move(int(win_width_ * 0.58) + 13, 0);
  description_header->setAlignment(Qt::AlignBottom);
  QFont desc_font = description_header->font();
  desc_font.setPixelSize(14);
  description_header->setFont(desc_font);
  description_header->setStyleSheet("QLabel { padding: 7px;"
                                    "padding-left: 0;"
                                    "color: #000; }");
  description_header->setText("-You don't need it");

  text_win_ = new QTextBrowser(window_);
  text_win_->resize(int(win_width_ * 0.75), int(win_height_ * 0.65));
  text_win_->move(0, int(win_height_ * 0.05) + 10);
  text_win_->setStyleSheet("QTextBrowser { border-radius: 10px;"
                           "margin: 10px;"
                           "margin-top: 0;"
                           "padding: 10px;"
                           "background-color: #fff;"
                           "color: #000; }"
                           "QTextBrowser QScrollBar::handle { background-color: #eddfc6;"
                           "border-radius: 10px; }"
                           "QTextBrowser QScrollBar { border-radius: 10px;"
                           "background: #fff;"
                           "border: 2px solid #eee; }"
                           "QScrollBar:left-arrow, QScrollBar::right-arrow {"
                           "border: 2px solid #eee;"
                           "width: 3px;"
                           "height: 3px;"
                           "background: #fff; }");
  text_win_->setAlignment(Qt::AlignTop);


  buttons_lbl_ver_ = new QWidget(window_);
  buttons_lbl_ver_->resize(int(win_width_ * 0.25), int(win_height_ * 0.65));
  buttons_lbl_ver_->move(int(win_width_ * 0.75), int(win_height_ * 0.05) + 10);
  buttons_lbl_ver_->setStyleSheet("QWidget { background-color: #fff;"
                                  "border-radius: 10px; "
                                  "margin: 10px;"
                                  "margin-top: 0; }");

  buttons_lbl_hor_ = new QWidget(window_);
  buttons_lbl_hor_->resize(int(win_width_), int(win_height_ * 0.15));
  buttons_lbl_hor_->move(0, int(win_height_ * 0.7) + 10);
  buttons_lbl_hor_->setStyleSheet("QWidget { background-color: #fff;"
                                  "border-radius: 10px;"
                                  "margin: 10px; }");

  num_ent_ = new QLineEdit(window_);
  num_ent_->resize(int(win_width_ * 0.25), int(win_height_ * 0.15));
  num_ent_->move(0, int(win_height_ * 0.85));
  num_ent_->setStyleSheet("QLineEdit { background-color: #fff;"
                           "border-radius: 10px;"
                           "margin: 10px;"
                           "padding: 5px;"
                           "color: #000; }");
  num_ent_->setPlaceholderText("Индекс(ы) строк");
  num_ent_->setAlignment(Qt::AlignTop);

  text_ent_ = new QTextEdit(window_);
  text_ent_->resize(int(win_width_ * 0.75), int(win_height_ * 0.15));
  text_ent_->move(int(win_width_ * 0.25), int(win_height_ * 0.85));
  text_ent_->setStyleSheet("QTextEdit { background-color: #fff;"
                                  "border-radius: 10px;"
                                  "margin: 10px;"
                                  "padding: 5px;"
                                  "color: #000; }");
  text_ent_->setPlaceholderText("Строки");

  setButtons();
}

void Pad::render() {
  window_->show();
}

void Pad::setButtons() {
  // save to file
  save_btn_ = new QPushButton(window_);

  QFont resized_font = save_btn_->font();
  resized_font.setPixelSize(11);

  save_btn_->setFont(resized_font);
  save_btn_->resize(int(win_width_ * 0.1) + 5, int(win_height_ * 0.05) + 10);
  connect(save_btn_, SIGNAL (released()), this, SLOT (saveToFile()));
  save_btn_->setStyleSheet("QPushButton { background-color: #eddfc6;"
                           "margin: 5px 5px 5px 10px;"
                           "border-radius: 10px;"
                           "color: #000; }"
                           "QPushButton::hover { margin: 3px 3px 3px 8px; }");
  save_btn_->setText("сохранить\n в файл");

  // load from file
  load_btn_ = new QPushButton(window_);
  load_btn_->setFont(resized_font);
  load_btn_->resize(int(win_width_ * 0.1) + 5, int(win_height_ * 0.05) + 10);
  load_btn_->move(int(win_width_ * 0.1), 0);
  connect(load_btn_, SIGNAL (released()), this, SLOT (loadFromFile()));
  load_btn_->setStyleSheet("QPushButton { background-color: #eddfc6;"
                           "margin: 5px 5px 5px 10px;"
                           "border-radius: 10px;"
                           "color: #000; }"
                           "QPushButton::hover { margin: 3px 3px 3px 8px; }");
  load_btn_->setText("загрузить\n из файла");

  buttons_.resize(10);
  for (int i = 0; i < 6; ++i) {
    buttons_[i] = new QPushButton(buttons_lbl_ver_);
    buttons_[i]->resize(buttons_lbl_ver_->width(), int(buttons_lbl_ver_->height() * 0.12) + 14);
    buttons_[i]->move(0, int(buttons_lbl_ver_->height() * 0.12 * i) + 14 * (i + 1));
    buttons_[i]->setStyleSheet("QPushButton { background-color: #eddfc6;"
                               "margin: 7px 20px 7px 20px;"
                               "color: #000; }"
                               "QPushButton::hover { margin: 5px 18px 5px 18px; }");
  }

  // insert line after N line
  connect(buttons_[0], SIGNAL (released()), this, SLOT (insertAfterLine()));
  buttons_[0]->setText("Вставить строку\nпосле строки N");

  // insert M lines after N line
  connect(buttons_[1], SIGNAL (released()), this, SLOT (multiInsertAfterLine()));
  buttons_[1]->setText("Вставить M строк\nпосле строки N");

  // erase N line
  connect(buttons_[2], SIGNAL (released()), this, SLOT (eraseLine()));
  buttons_[2]->setText("Удалить строку N");

  // replace M symbol in N line
  connect(buttons_[3], SIGNAL (released()), this, SLOT (replaceSymbol()));
  buttons_[3]->setText("Заменить символ M\nв N-ой строке");

  // insert subsequence to N line in M pos
  connect(buttons_[4], SIGNAL (released()), this, SLOT (insertSubSeq()));
  buttons_[4]->setText("Вставить подстроку в\nN строку на M позицию");

  // replace subsequence s to subsequence t in lines N-M
  connect(buttons_[5], SIGNAL (released()), this, SLOT (replaceSubSeq()));
  buttons_[5]->setText("Заменить подстроку s\nна t в строках N - M");

  for (int i = 6; i < 10; ++i) {
    buttons_[i] = new QPushButton(buttons_lbl_hor_);
    buttons_[i]->resize(int(buttons_lbl_hor_->width() * 0.25), buttons_lbl_hor_->height());
    buttons_[i]->move(int(buttons_lbl_hor_->width() * 0.25) * (i - 6), 0);
    buttons_[i]->setStyleSheet("QPushButton { background-color: #eddfc6;"
                               "margin: 20px;"
                               "color: #000; }"
                               "QPushButton::hover { margin: 18px; }");
  }

  // remove zeros
  connect(buttons_[6], SIGNAL (released()), this, SLOT (removeZeros()));
  buttons_[6]->setText("Удалить ведущие нули\nв строках N - M");

  // remove no-grades number subsequences
  connect(buttons_[7], SIGNAL (released()), this, SLOT (onlyGradesNums()));
  buttons_[7]->setText("Оставить только\nвозрастающие группы\nчисел в строках N - M");

  // replace * with +
  connect(buttons_[8], SIGNAL (released()), this, SLOT (replaceStars()));
  buttons_[8]->setText("Заменить C '*' на C/2 '+'\nв строках N - M");

  // remove {...}
  connect(buttons_[9], SIGNAL (released()), this, SLOT (removeBrackets()));
  buttons_[9]->setText("Удалить значения в\nфигурных скобках\nв строках N - M");
}

void Pad::showText() {
  QString str;
  for (std::wstring* line : lines_) {
    str.append(QString::fromWCharArray(line->c_str()));
  }

  text_win_->setText(str);
}

void Pad::insertAfterLine() {
  int n = 0;
  QString num = num_ent_->text();
  num_ent_->clear();
  for (char c : num.toStdString()) {
    if (c == ' ') break;

    n = n * 10 + c - '0';
  }
  n = std::max(0, std::min(n, (int)lines_.size()));

  QString data = text_ent_->toPlainText();
  text_ent_->clear();
  if (data.isEmpty()) return;
  QStringList text = data.split(QRegularExpression("[\n]"), Qt::SkipEmptyParts);

  std::wstring line = text[0].toStdWString();
  std::vector<std::wstring*> strs = Text::toLines(line);
  for (int j = 0; j < strs.size(); ++j) {
    lines_.insert(lines_.begin() + n + j, strs[j]);
  }

  showText();
}

void Pad::multiInsertAfterLine() {
  int n = 0, m = 0;
  QString nums = num_ent_->text();
  num_ent_->clear();
  bool space = false;
  for (char c : nums.toStdString()) {
    if (c == ' ') {
      space = true;
      continue;
    }

    if (space) {
      m = m * 10 + c - '0';
    } else {
      n = n * 10 + c - '0';
    }
  }
  n = std::max(0, std::min(n, (int)lines_.size()));

  QString data = text_ent_->toPlainText();
  text_ent_->clear();
  if (data.isEmpty()) return;
  QStringList text = data.split(QRegularExpression("[\n]"), Qt::SkipEmptyParts);

  for (int i = 0; i < std::min((int)text.size(), m); ++i) {
    std::wstring str = text[i].toStdWString();
    std::vector<std::wstring*> strs = Text::toLines(str);

    int j;
    for (j = 0; j < strs.size(); ++j) {
      lines_.insert(lines_.begin() + n + j, strs[j]);
    }

    n += j;
  }

  showText();
}

void Pad::eraseLine() {
  int n = 0;
  QString num = num_ent_->text();
  num_ent_->clear();
  text_ent_->clear();
  for (char c : num.toStdString()) {
    if (c == ' ') break;

    n = n * 10 + c - '0';
  }
  --n;
  if (n < 0 || n >= lines_.size()) return;

  delete lines_[n];
  lines_.erase(lines_.begin() + n);

  showText();
}

void Pad::replaceSymbol() {
  int n = 0, m = 0;
  QString nums = num_ent_->text();
  num_ent_->clear();
  bool space = false;
  for (char c : nums.toStdString()) {
    if (c == ' ') {
      space = true;
      continue;
    }

    if (space) {
      m = m * 10 + c - '0';
    } else {
      n = n * 10 + c - '0';
    }
  }
  --n;
  --m;
  if (n < 0 || n >= lines_.size()) return;
  if (m < 0 || m >= lines_[n]->size()) return;

  QString data = text_ent_->toPlainText();
  text_ent_->clear();
  if (data.isEmpty()) return;
  wchar_t rep =data.toStdWString()[0];
  int i = 0;
  for (wchar_t& c : *lines_[n]) {
    if (i == m) {
      c = rep;
      break;
    }
    ++i;
  }

  showText();
}

void Pad::insertSubSeq() {
  int n = 0, m = 0;
  QString nums = num_ent_->text();
  num_ent_->clear();
  bool space = false;
  for (char c : nums.toStdString()) {
    if (c == ' ') {
      space = true;
      continue;
    }

    if (space) {
      m = m * 10 + c - '0';
    } else {
      n = n * 10 + c - '0';
    }
  }
  --n;
  if (n < 0 || n >= lines_.size()) return;
  if (m < 0 || m > lines_[n]->size()) return;

  QString data = text_ent_->toPlainText();
  text_ent_->clear();
  if (data.isEmpty()) return;
  QStringList text = data.split(QRegularExpression("[\n]"), Qt::SkipEmptyParts);

  std::wstring str = text[0].toStdWString();
  std::wstring target = *lines_[n];
  lines_.erase(lines_.begin() + n);
  const wchar_t* paste = str.c_str();
  target.insert(m, paste);
  std::vector<std::wstring*> strs = Text::toLines(target);
  for (int j = 0; j < strs.size(); ++j) {
    lines_.insert(lines_.begin() + n + j, strs[j]);
  }

  showText();
}

void Pad::replaceSubSeq() {
  int n = 0, m = int(lines_.size());
  QString nums = num_ent_->text();
  num_ent_->clear();
  bool space = false;

  if (!nums.isEmpty()) {
    m = 0;
    for (char c : nums.toStdString()) {
      if (c == ' ') {
        space = true;
        continue;
      }

      if (space) {
        m = m * 10 + c - '0';
      } else {
        n = n * 10 + c - '0';
      }
    }
    --n;
    if (n < 0 || n >= lines_.size()) return;
    m = std::max(0, std::min(m, (int)lines_.size()));
  }

  QString data = text_ent_->toPlainText();
  text_ent_->clear();
  if (data.isEmpty()) return;
  QStringList text = data.split(QRegularExpression("[ ]"), Qt::SkipEmptyParts);

  std::wstring from = text[0].toStdWString(), to = text[1].toStdWString();

  for (int j = n; j < m; ++j) {
    Text::replace(*lines_[j], from, to);
  }

  showText();
}

void Pad::removeZeros() {
  int n = 0, m = int(lines_.size());
  QString nums = num_ent_->text();
  num_ent_->clear();
  bool space = false;

  if (!nums.isEmpty()) {
    m = 0;
    for (char c : nums.toStdString()) {
      if (c == ' ') {
        space = true;
        continue;
      }

      if (space) {
        m = m * 10 + c - '0';
      } else {
        n = n * 10 + c - '0';
      }
    }
    --n;
    if (n < 0 || n >= lines_.size()) return;
    m = std::max(0, std::min(m, (int)lines_.size()));
  }

  for (int i = n; i < m; ++i) {
    Text::removeZeros(*lines_[i]);
  }

  showText();
}

void Pad::onlyGradesNums() {
  int n = 0, m = int(lines_.size());
  QString nums = num_ent_->text();
  num_ent_->clear();
  bool space = false;

  if (!nums.isEmpty()) {
    m = 0;
    for (char c : nums.toStdString()) {
      if (c == ' ') {
        space = true;
        continue;
      }

      if (space) {
        m = m * 10 + c - '0';
      } else {
        n = n * 10 + c - '0';
      }
    }
    --n;
    if (n < 0 || n >= lines_.size()) return;
    m = std::max(0, std::min(m, (int)lines_.size()));
  }

  for (int i = n; i < m; ++i) {
    Text::onlyGrades(*lines_[i]);
  }

  showText();
}

void Pad::replaceStars() {
  int n = 0, m = int(lines_.size());
  QString nums = num_ent_->text();
  num_ent_->clear();
  bool space = false;

  if (!nums.isEmpty()) {
    m = 0;
    for (char c : nums.toStdString()) {
      if (c == ' ') {
        space = true;
        continue;
      }

      if (space) {
        m = m * 10 + c - '0';
      } else {
        n = n * 10 + c - '0';
      }
    }
    --n;
    if (n < 0 || n >= lines_.size()) return;
    m = std::max(0, std::min(m, (int)lines_.size()));
  }

  for (int i = n; i < m; ++i) {
    Text::replaceStars(*lines_[i]);
  }

  showText();
}

void Pad::removeBrackets() {
  int n = 0, m = int(lines_.size());
  QString nums = num_ent_->text();
  num_ent_->clear();
  bool space = false;

  if (!nums.isEmpty()) {
    m = 0;
    for (char c : nums.toStdString()) {
      if (c == ' ') {
        space = true;
        continue;
      }

      if (space) {
        m = m * 10 + c - '0';
      } else {
        n = n * 10 + c - '0';
      }
    }
    --n;
    if (n < 0 || n >= lines_.size()) return;
    m = std::max(0, std::min(m, (int)lines_.size()));
  }

  for (int i = n; i < m; ++i) {
    Text::removeBrackets(*lines_[i]);
  }

  showText();
}

void Pad::saveToFile() {
  QString file = QFileDialog::getSaveFileName(nullptr, "Сохранить в файл", "", "*.txt");
  QFile outFile(file);
  if (!outFile.open(QIODevice::WriteOnly)) return;
  QTextStream ostream(&outFile);

  for (std::wstring* line : lines_) {
    ostream << QString::fromStdWString(*line);
  }
  outFile.close();
}

void Pad::loadFromFile() {
  for (auto& line : lines_) {
    delete line;
  }
  lines_.resize(0);

  QString file = QFileDialog::getOpenFileName(nullptr, "Выбрать txt файл", "", "*.txt");
  QFile in(file);
  if (!in.open(QIODevice::ReadOnly)) return;
  QString data = in.readAll();
  in.close();

  if (data.isEmpty()) return;
  QStringList text = data.split(QRegularExpression("[\n]"), Qt::SkipEmptyParts);
  for (const auto& i : text) {
    std::wstring line = i.toStdWString();
    std::vector<std::wstring*> lines = Text::toLines(line);
    for (auto s : lines) {
      lines_.push_back(s);
    }
  }

  showText();
}
