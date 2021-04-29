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

BG_BEGIN

/**
 * @brief General Move class to store the move board of the game
 * 
 * @tparam T 
 */
template <typename T>
class Move
{
public:
  //-------------------CONSTRUCTORS------------------

  /**
   * @brief Construct a new Move object
   */
  Move();

  /**
   * @brief Construct a new Move object
   * 
   * @param row 
   * @param col 
   * @param piece 
   */
  Move(const std::size_t row, const std::size_t col, const T &piece);

  /**
   * @brief [virtual] Destroy the Move object
   */
  virtual ~Move();

  //-----------------------GETTERS-------------------------

  /**
   * @brief row
   * 
   * @return std::size_t
   */
  inline std::size_t row() const;

  /**
   * @brief column
   * 
   * @return std::size_t
   */
  inline std::size_t col() const;

  /**
   * @brief piece
   * 
   * @return T
   */
  inline T piece() const;

  //-----------------------SETTERS-------------------------

  //set row
  inline void set_row(const std::size_t row);
  //set col
  inline void set_col(const std::size_t col);
  //set piece
  inline void set_piece(const T &piece);
  //set row, col, piece
  inline void set(const std::size_t row, const std::size_t col, const T &piece);

protected:
  std::size_t _row; //row
  std::size_t _col; //col
  T _piece;         //piece
};

//-------------------------------------------------------------------------------------------------------
//---------------------------------------IMPLEMENTATION--------------------------------------------------
//-------------------------------------------------------------------------------------------------------

template <typename T>
inline Move<T>::Move() {}

template <typename T>
inline Move<T>::Move(const std::size_t row, const std::size_t col, const T &piece) : _row(row), _col(row), _piece(piece) {}

template <typename T>
inline Move<T>::~Move()
{
  _row = -1;
  _col = -1;
  _piece = T();
}

template <typename T>
inline std::size_t Move<T>::row() const
{
  return _row;
}
template <typename T>
inline std::size_t Move<T>::col() const
{
  return _col;
}

template <typename T>
inline T Move<T>::piece() const
{
  return _piece;
}

template <typename T>
inline void Move<T>::set_row(const std::size_t row)
{
  _row = row;
}

template <typename T>
inline void Move<T>::set_col(const std::size_t col)
{
  _col = col;
}

template <typename T>
inline void Move<T>::set_piece(const T &piece)
{
  _piece = piece;
}

template <typename T>
inline void Move<T>::set(const std::size_t row, const std::size_t col, const T &piece)
{
  this->_row = row;
  this->_col = col;
  this->_piece = piece;
}

BG_END

#endif //BG_MOVE_H_