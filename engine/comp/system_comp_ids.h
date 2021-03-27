#ifndef SYSTEM_COMP_IDS_H_
#define SYSTEM_COMP_IDS_H_

#include "user_comp_ids.h"

namespace ComponentIDs {

enum SystemComponentIDs {
  kTransformationID = kUserEnumSize,

  kSystemEnumSize
};

constexpr uint64_t kNumOfComponents{kSystemEnumSize};

}

#endif  // SYSTEM_COMP_IDS_H_
