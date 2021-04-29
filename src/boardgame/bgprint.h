#ifndef BG_PRINT_H_
#define BG_PRINT_H_

#include "bgtypes.h"
#include "bgmove.h"
#include "bgplayers.h"
#include "bgboard.h"

BG_BEGIN

//---------------------BOARD-------------------------

template <typename T>
void print(const T** bgrid, const int rows, const int cols);

template<typename T>
void print(const grid<T> bgrid);

template <typename T>
void print(Board<T>*& board);

//---------------------MOVE----------------------------

template <typename T>
void print(Move<T>*& board);

//---------------------PLAYER-------------------------

// template <typename T>

BG_END

#endif //BG_PRINT_H_