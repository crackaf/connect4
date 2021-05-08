
#ifndef BG_TYPES_H_
#define BG_TYPES_H_

#include <cassert>

#include <string>
#include <iostream>

#include "bgmacros.h"

BG_BEGIN

using size_t = std::size_t;
using csize_t = const std::size_t;
using int_t = signed long long;
using cint_t = const int_t;
using dec_t = double;
using cdec_t = const dec_t;

BG_END

inline void bgdebug(std::string _where, std::string _detail = "", bool _exit = false) noexcept
{
  printf("%s%s%s\n", _where.c_str(), " --> ", _detail.c_str());
  //std::cout << _where << " --> " << _detail << std::endl;
  if (_exit)
    std::exit(1);
}

#endif //BG_TYPES_H_
