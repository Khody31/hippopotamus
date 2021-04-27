#pragma once

#include <QVector2D>
#include <memory>

class Connector;

class Functions {
 public:
  static QPoint GameToWidgetCoord(const QVector2D& coord);
  static QVector2D WidgetToGameCoord(const QPoint& coord);

  static Connector* connector_; // This field is initialized with Connector.
};