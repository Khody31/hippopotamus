#include "custom_widget.h"

CustomWidget::CustomWidget(AbstractController* controller, QWidget* parent)
    : QWidget(parent), controller_(controller) {
}
