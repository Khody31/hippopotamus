#pragma once

#include <cstdint>
#include <engine/constants.h>
#include <bitset>

using Entity = uint8_t;
using ComponentType = uint8_t;
using Signature = std::bitset<constants::kMaxComponents>;
