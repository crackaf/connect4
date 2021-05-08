/**
 * @file bgmacros.h
 * @author Hunzlah Malik @ghostdart
 * @brief
 * @version 0.1
 * @date 2021-05-06
 *
 * @copyright Copyright (c) 2021
 */

#ifndef BG_MACROS_H_
#define BG_MACROS_H_

//----------NAMESPACE-------------

#define BG_NAME bg
#define BG_BEGIN    \
  namespace BG_NAME \
  {
#define BG_END }
#define BG_USING using namespace BG_NAME
#define BG ::BG_NAME::

//-----------USAGE--------------

#define deleteptr(ptr) \
  {                    \
    delete ptr;        \
    ptr = nullptr;     \
  }

#define deletearr(arr) \
  {                    \
    delete[] arr;      \
    arr = nullptr;     \
  }

//-------------DEBUGGING-------------

#ifndef NDEBUG
#define BGDEBUG 1
#else
#define BGDEBUG 0
#endif
#define _ISDBG_ if constexpr (BGDEBUG)
#define _ISDBG \
  if (BGDEBUG) \
  {
#define _ISDBGE }

//#if BG_DEBUG
//constexpr auto BGDEBUG = true;
//#else
//constexpr auto BGDEBUG = false;
//#endif
//
////-----------ASSERTION--------------
//#define BG_ASSERTIONS 0 // 1=>Enable , 0=>Disable
//
//#include "bgassert.h" //for assertion

#endif //BG_MACROS_H_