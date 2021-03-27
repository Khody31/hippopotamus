#include "governor.h"

Governor::Governor(uint64_t type_id) {
  GovernorsHandler::Get().AddGovernor(this, type_id);
}
void Governor::StartTracking(AbstractComponent* comp) {
  components_.insert(comp);
}
void Governor::StopTracking(AbstractComponent* comp) {
  components_.erase(comp);
}
