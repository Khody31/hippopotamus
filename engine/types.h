#pragma once

#include <bitset>

#include "constants.h"

using Entity = uint32_t;
using ComponentType = uint32_t;
using Signature = std::bitset<constants::kMaxComponents>;
