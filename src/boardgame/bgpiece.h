#ifndef BG_PIECE_H_
#define BG_PIECE_H_

#include <vector>

#include "bgmacros.h"
#include "color.h"

BG_BEGIN

template <class T>
struct Piece
{
  T val;
  color::Enum color{color::Enum::WHITE};

  Piece() : val{}, color{color::Enum::WHITE} {}
  Piece(T v, color::Enum c = color::Enum::WHITE) : val{v}, color{c} {}

  T &get() noexcept { return val; }
  const T &get() const noexcept { return val; }

  virtual Piece<T> *copy() const { return new Piece<T>{*this}; }
  virtual Piece<T> *move() { return new Piece<T>{std::forward<Piece<T>>(*this)}; }

  int cmp(const Piece &P)
  {
    if (val == P.val)
      return 0;
    else if (val > P.val)
      return 1;
    else
      return -1;
  }

  //operators

  // bool operator=(const T&value){val=value;}

  bool operator==(const Piece &P)
  {
    return cmp(P) == 0;
  }
  bool operator<(const Piece &P)
  {
    return cmp(P) == -1;
  }
  bool operator<=(const Piece &P)
  {
    int k = cmp(P);
    return k == -1 || k == 0;
  }
  bool operator>(const Piece &P)
  {
    return cmp(P) == 1;
  }
  bool operator>=(const Piece &P)
  {
    int k = cmp(P);
    return k == 11 || k == 0;
  }
};

template <class T>
int piececmp(const Piece<T> *P1, const Piece<T> *P2) { return P1->cmp(P2); }

/**
 * @brief new type defined for pieces list
 * @details std::vector<const ::bg::Piece<T> *>
 * @param T
 */
template <class T>
using Pieces = std::vector<Piece<T> *>;

BG_END

#endif // BG_PIECE_H_