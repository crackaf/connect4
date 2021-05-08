#ifndef C4_TYPES_H_
#define C4_TYPES_H_

#include "../boardgame/boardgame.h"

using C4Players = ::bg::Players<char>;
using C4Player = ::bg::Player<char>;
using C4Move = ::bg::Move<char>;
using C4Piece = ::bg::Piece<char>;
using C4Pieces = ::bg::Pieces<char>;
using C4Board = ::bg::PBoard<char>;
using BGame = ::bg::Game<char>;

#endif //C4_TYPES_H_