#ifndef BG_MACROS_H_
#define BG_MACROS_H_

//----------NAMESPACE-------------
#define BG_NAME bg
#define BG_BEGIN    \
  namespace BG_NAME \
  {
#define BG_END }
#define BG_USING using namespace BG_NAMESPACE_NAME
#define BG ::BG_NAME::

//-----------ASSERTION--------------
#define BG_ASSERTIONS 1 // 1=>Enable , 0=>Disable

#if BG_ASSERTIONS
#include <cassert> //for assertion
#define BG_ASSERT(expr) \
  ((expr) ? (void)0 : CDA_assert_(__LINE__, __FILE__, #expr))
#else
#define BG_ASSERT(expr) ((void)0)
#endif

#endif //BG_MACROS_H_