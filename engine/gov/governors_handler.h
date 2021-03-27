#ifndef GOVERNORS_HANDLER_H_
#define GOVERNORS_HANDLER_H_

#include <array>

#include "engine/comp/system_comp_ids.h"

class Governor;

class GovernorsHandler {
 public:
  GovernorsHandler(const GovernorsHandler&) = delete;
  void operator=(const GovernorsHandler&) = delete;

  [[nodiscard]] static GovernorsHandler& Get() ;
  void AddGovernor(Governor*, uint64_t type_id);

  [[nodiscard]] Governor* GetGovernor(uint64_t type_id) const;

 private:
  GovernorsHandler() = default;

  std::array<Governor*, ComponentIDs::kNumOfComponents> governors_{};
};

#endif  // GOVERNORS_HANDLER_H_
