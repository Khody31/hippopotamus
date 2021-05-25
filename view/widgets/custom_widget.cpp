#include <QPainter>

#include "custom_widget.h"

CustomWidget::CustomWidget(AbstractController* controller, QWidget* parent,
                           const QString& path_to_background)
    : QWidget(parent),
      controller_(controller),
      background_(new QPixmap(path_to_background)) {
}

void CustomWidget::paintEvent(QPaintEvent* event) {
  QPainter* painter = new QPainter(this);
  painter->drawPixmap(event->rect(), *background_);
  delete painter;
}
