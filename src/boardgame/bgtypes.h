#ifndef BG_TYPES_H_
#define BG_TYPES_H_

#include <vector>

#include "bgmacros.h"

BG_BEGIN

/**
  * @brief new type defined for board
  * @details std::vector<std::vector<typename T>>
  */
template <typename T>
using grid = std::vector<std::vector<T>>;


BG_END

#endif //BG_TYPES_H_
