#pragma once

#include <QPushButton>
#include <QString>

class MenuButton : public QPushButton {
 public:
  explicit MenuButton(const QString& text, QWidget* parent = nullptr);
};
