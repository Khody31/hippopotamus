#pragma once

#include <cstdint>
#include <engine/constants.h>
#include <bitset>

using Entity = uint32_t;
using ComponentType = uint32_t;
using Signature = std::bitset<constants::kMaxComponents>;
