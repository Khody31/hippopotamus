#pragma once

class TransformationComponentInterface;
class PixmapComponentInterface;

class GameObjectInterface {
 public:
  virtual void SetTransformationComponent(TransformationComponentInterface* component) = 0;
  virtual void SetPixmapComponent(PixmapComponentInterface* component) = 0;

  virtual TransformationComponentInterface* GetTransformationComponent() const = 0;
  virtual PixmapComponentInterface* GetPixmapComponent() const = 0;
};

