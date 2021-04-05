#include "physics_governor.h"
#include "engine/comp/physics_component.h"

#include "engine/comp/transformation_component.h"

PhysicsGovernor::PhysicsGovernor(int type_id)
    : Governor(type_id) {}

void PhysicsGovernor::OnTick() {
  // TODO(Khody31):  implement physics processing

  // detect collisions
  for (auto fst_comp : components_) {
    auto fst_physics_comp = dynamic_cast<PhysicsComponent*>(fst_comp);
    auto fst_transform_comp = dynamic_cast<TransformationComponent*>(
        fst_comp->GetParent()->GetComponent(ComponentIDs::kTransformationID));
    QVector2D fst_coordinates = fst_transform_comp->GetPos();

    for (auto scd_comp : components_) {
      auto scd_physics_comp = dynamic_cast<PhysicsComponent*>(scd_comp);
      auto scd_transform_comp = dynamic_cast<TransformationComponent*>(
          scd_comp->GetParent()->GetComponent(ComponentIDs::kTransformationID));
      QVector2D scd_coordinates = scd_transform_comp->GetPos();

      // check if collision exists
      if ((fst_physics_comp->GetSize().x() / 2 + fst_coordinates.x() <
          -scd_physics_comp->GetSize().x() / 2 + scd_coordinates.x()) ||
          (-fst_physics_comp->GetSize().x() / 2 + fst_coordinates.x() <
              scd_physics_comp->GetSize().x() / 2 + scd_coordinates.x())) {
        continue;
      }

      if ((fst_physics_comp->GetSize().y() / 2 + fst_coordinates.y() <
          -scd_physics_comp->GetSize().y() / 2 + scd_coordinates.y()) ||
          (-fst_physics_comp->GetSize().y() / 2 + fst_coordinates.y() <
              scd_physics_comp->GetSize().y() / 2 + scd_coordinates.y())) {
        continue;
      }

      QVector2D fst_velocity = fst_transform_comp->GetVelocity();
      QVector2D scd_velocity = scd_transform_comp->GetVelocity();

      // process vertical collision
      {
        double fst_vertical_speed = fst_velocity.x();
        double scd_vertical_speed = scd_velocity.x();

        double n = (fst_vertical_speed > 0 ? 1 : -1);

        double rel_velocity = (fst_vertical_speed - scd_vertical_speed) * n;

        if (rel_velocity < 0) {
          double e = std::min(
              fst_physics_comp->GetRestitution(),
              scd_physics_comp->GetRestitution());
          double j = -(1 + e) * rel_velocity;
          j /=
              1 / fst_physics_comp->GetMass() + 1 / scd_physics_comp->GetMass();

          double impulse = n * j;
          fst_velocity += QVector2D(impulse / fst_physics_comp->GetMass(), 0);
          scd_velocity -= QVector2D(impulse / fst_physics_comp->GetMass(), 0);
        }
      }

      // process horizontal collision

      {
        double fst_horizontal_velocity = fst_velocity.y();
        double scd_horizontal_velocity = scd_velocity.y();

        double n = (fst_horizontal_velocity > 0 ? 1 : -1);

        double rel_velocity =
            (fst_horizontal_velocity - scd_horizontal_velocity) * n;

        if (rel_velocity < 0) {
          double e = std::min(
              fst_physics_comp->GetRestitution(),
              scd_physics_comp->GetRestitution());
          double j = -(1 + e) * rel_velocity;
          j /=
              1 / fst_physics_comp->GetMass() + 1 / scd_physics_comp->GetMass();

          double impulse = n * j;
          fst_velocity += QVector2D(0, impulse / fst_physics_comp->GetMass());
          scd_velocity -= QVector2D(0, impulse / fst_physics_comp->GetMass());
        }
      }
    }
  }

  Governor::OnTick();
}
