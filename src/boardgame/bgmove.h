/**
 * @file bgmove.h
 * @author Hunzlah Malik @ghostdart
 * @brief Implementation of Move Class
 * @version 0.1
 * @date 2021-04-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef BG_MOVE_H_
#define BG_MOVE_H_

#include "bgtypes.h"
#include "bgpiece.h"

BG_BEGIN

namespace move
{
  enum class Enum
  {
    INVALID,
    VALID,
    WINNING,
  };
} // namespace move

/**
 * @brief General Move class to store the move board of the game
 * @code .cpp
 * virtual ~Move();
 * virtual Move * copy();
 * virtual Move * move();
 * @endcode
 * 
 * @tparam T
 */
template <class T>
class Move
{
public:
  //-------------------CONSTRUCTORS------------------

  Move() = delete;

  /**
   * @brief Construct a new Move object
   *
   * @param row
   * @param col
   * @param piece [no copy] [direct pointer] [lifetime] [deletes after]
   */
  Move(int_t row, int_t col, const Piece<T> &piece) noexcept : _row{row}, _col{col}, _piece{piece.copy()}
  {
    _ISDBG_ bgdebug("Move::Move(int,int,ptr)", "row=" + std::to_string(row) + "|_row=" + std::to_string(_row) + "|col=" + std::to_string(col) + "|_col=" + std::to_string(_col));
  }

  Move(int_t row, int_t col, Piece<T> &&piece) noexcept : _row{row}, _col{col}, _piece{piece.move()}
  {
    _ISDBG_ bgdebug("Move::Move(int,int,ptr)", "row=" + std::to_string(row) + "|_row=" + std::to_string(_row) + "|col=" + std::to_string(col) + "|_col=" + std::to_string(_col));
  }

  Move(const Move<T> &other) : _row{other._row}, _col{other._col}, _piece{other._piece->copy()} {}

  Move<T> &operator=(const Move<T> &other) noexcept
  {
    if (this != &other)
    {
      // Free the existing resource.
      deleteptr(_piece);

      // Copy the data pointer and its length from the
      // source object.
      _piece = new Piece<T>{other._piece};
      _row = other._row;
      _col = other._col;
    }
    return *this;
  }

  Move(Move<T> &&other) noexcept : _row{other._row}, _col{other._col}
  {
    *this = std::move(other);
  }

  Move<T> &operator=(Move<T> &&other) noexcept
  {
    if (this != &other)
    {
      // Free the existing resource.
      deleteptr(_piece);

      // Copy the data pointer from the source object.
      _piece = other._piece;
      _row = other._row;
      _col = other._col;

      // Release the data pointer from the source object so that
      // the destructor does not free the memory multiple times.
      other._piece = nullptr;
      other._row = other._col = -1;
    }
    return *this;
  }

  /**
   * @brief [virtual] Destroy the Move object
   */
  virtual ~Move()
  {
    _ISDBG_ bgdebug("Move::~Move");

    _row = -1;
    _col = -1;

    deleteptr(_piece);
  }

  //-----------------------GETTERS-------------------------

  /**
   * @brief row
   * @return int_t
   */
  inline auto row() const noexcept { return _row; }

  /**
   * @brief column
   * @return int_t
   */
  inline auto col() const noexcept { return _col; }

  /**
   * @brief piece
   * @return T
   */
  inline const auto &piece() const noexcept { return _piece; }

  /**
   * @brief piece
   * @return T
   */
  inline auto &piece() noexcept { return _piece; }

  //-----------------VIRTUAL--------------------

  virtual Move<T> *copy() const { return new Move<T>{*this}; }
  virtual Move<T> *move() { return new Move<T>{std::forward<Move<T>>(*this)}; }

protected:
  int_t _row{-1};            //row
  int_t _col{-1};            //col
  Piece<T> *_piece{nullptr}; //piece
};

BG_END

#endif //BG_MOVE_H_