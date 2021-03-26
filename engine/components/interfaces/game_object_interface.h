#pragma once

class TransformationComponentInterface;
class PixmapComponentInterface;

class GameObjectInterface {
 public:
  virtual void SetTransformationComponent(TransformationComponentInterface* component) = 0;
  virtual void SetPixmapComponent(PixmapComponentInterface* component) = 0;

  [[nodiscard]] virtual TransformationComponentInterface* GetTransformationComponent() const = 0;
  [[nodiscard]] virtual PixmapComponentInterface* GetPixmapComponent() const = 0;
};

