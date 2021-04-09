#include "component_manager.h"

std::unordered_map<std::type_index, const char*> ComponentManager::type_names_ = {
{typeid(PhysicsComponent), "PhysicsComponent"},
{typeid(PixmapComponent), "PixmapComponent"},
{typeid(TransformationComponent), "TransformationComponent"}
};