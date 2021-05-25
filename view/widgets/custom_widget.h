#pragma once

#include <QWidget>

#include "view/abstract_controller.h"

class CustomWidget : public QWidget {
  Q_OBJECT
 public:
  CustomWidget(AbstractController* controller, QWidget* parent,
               const QString& path_to_background);
  virtual void Resize(QSize size) = 0;
  virtual void ChangeLanguage(Language language) = 0;

 protected:
  AbstractController* controller_;
  QPixmap* background_;

 private:
  void paintEvent(QPaintEvent* event) override;
};
