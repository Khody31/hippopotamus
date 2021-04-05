#include "physics_component.h"
#include "system_comp_ids.h"

PhysicsComponent::PhysicsComponent(
    GameObject* parent,
    double mass,
    QVector2D size) :
    Component(ComponentIDs::kPhysicsID, parent),
    mass_(mass),
    size_(size) {}

QVector2D PhysicsComponent::GetVelocity() const {
  return velocity_;
}

double PhysicsComponent::GetMass() const {
  return mass_;
}

void PhysicsComponent::SetVelocity(QVector2D new_velocity) {
  velocity_ = new_velocity;
}

QVector2D PhysicsComponent::GetSize() const {
  return size_;
}

double PhysicsComponent::GetRestitution() const {
  return restitution_;
}
