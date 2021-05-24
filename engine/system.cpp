#include "system.h"
#include "constants.h"

System::System() : entities_{} {
  entities_.reserve(constants::kMaxEntities);
}
