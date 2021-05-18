#pragma once

#include <QWidget>

#include "view/abstract_controller.h"

class CustomWidget : public QWidget {
  Q_OBJECT
 public:
  CustomWidget(AbstractController* controller, QWidget* parent);
  virtual void Resize(QSize size) = 0;

 protected:
  AbstractController* controller_;
};
