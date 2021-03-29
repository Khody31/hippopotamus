#ifndef GOVERNORS_HANDLER_H_
#define GOVERNORS_HANDLER_H_

#include <map>
#include <vector>

#include "engine/comp/system_comp_ids.h"

class Governor;

class GovernorsHandler {
 public:
  GovernorsHandler(const GovernorsHandler&) = delete;
  void operator=(const GovernorsHandler&) = delete;

  [[nodiscard]] static GovernorsHandler& Get() ;
  void SetGovernor(Governor* governor, int type_id);

  [[nodiscard]] Governor* GetGovernor(int type_id) const;

  void Subscribe(int subscriber_id, int source_id);
  [[nodiscard]] const std::vector<int>& GetSubscribers(int source_id);

  void OnTick();

 private:
  GovernorsHandler() = default;

  std::map<int, Governor*> governors_{};
  std::map<int, std::vector<int>> subscribers_lists_{};
};

#endif  // GOVERNORS_HANDLER_H_
