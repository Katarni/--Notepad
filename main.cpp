#include "Pad.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Pad notepad(850, 700);

  notepad.render();

  return QApplication::exec();
}
