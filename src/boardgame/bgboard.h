/**
 * @file bgboard.h
 * @author Hunzlah Malik @ghostdart
 * @brief Implementation of Board Class
 * @version 0.1
 * @date 2021-04-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BG_BOARD_H_
#define BG_BOARD_H_

#include<ostream>
#include <vector>

#include "bgtypes.h"

BG_BEGIN

/**
 * @brief General Board class to store the row x col board of the game
 * @tparam T is the type of which board will be created
 */
template <typename T>
class Board
{
public:
  //-------------------CONSTRUCTORS------------------

  /**
   * @brief Construct a new Board object
   */
  Board();

  /**
   * @brief Construct a new Board object
   * 
   * @param rows number of rows of new Board
   * @param cols number of cols of new Board
   * @param default_val default value to add to empty board
   */
  Board(const std::size_t rows, const std::size_t cols);

  /**
   * @brief Construct a new Board object
   * 
   * @param rows number of rows of new Board
   * @param cols number of cols of new Board
   * @param default_val default value to add to empty board
   */
  Board(const std::size_t rows, const std::size_t cols, const T default_val);

  /**
   * @brief Construct a new Board object with given 2D board
   * 
   * @param board 2D board you want to copy
   * @param rows rows of the given board
   * @param cols cols of the given board
   */
  Board(const T **board, const std::size_t rows, const std::size_t cols);

  /**
   * @brief [virtual] Destroy the Board object
   */
  virtual ~Board();

  //-----------------------GETTERS-------------------------

  /**
   * @brief number of rows
   * 
   * @return std::size_t
   */
  inline std::size_t rows() const;

  /**
   * @brief number of columns
   * 
   * @return std::size_t
   */
  inline std::size_t cols() const;

  /**
   * @brief const reference to value at row,col
   * 
   * @param row 
   * @param col 
   * @return const T& 
   */
  inline const T &at(const std::size_t row, const std::size_t col) const;
  /**
   * @brief reference to value at row,col
   * 
   * @param row 
   * @param col 
   * @return T& 
   */
  inline T &at(const std::size_t row, const std::size_t col);

  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   * 
   * @return T** 
   */
  inline T **data();
  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   * 
   * @return const  T** 
   */
  inline const T **data() const;

  //-----------------------SETTERS-------------------------

  /**
   * @brief resize the board object
   * 
   * @param rows 
   * @param cols 
   */
  inline void resize(const std::size_t rows, const std::size_t col);

  /**
   * @brief resize the board object
   * 
   * @param rows 
   * @param cols 
   */
  inline void resize(const std::size_t rows, const std::size_t col, const T default_val);

  /**
   * @brief Set the board object
   * 
   * @param row 
   * @param col 
   * @param val T
   */
  inline void insert(const std::size_t row, const std::size_t col, const T val);

  /**
   * @brief resets the board
   */
  void clear();

  /**
   * @brief deletes the dynamic array
   * 
   * @param data T**
   * @param rows 
   */
  static void del(T **data, const std::size_t rows);

  //------------------------MEMBER FUNCTIONS-----------------------------

  /**
   * @brief check if the board contains or not
   * 
   * @param val to check in board 
   * @return true | false
   */
  bool isFound(const T &val);

  /**
   * @brief print the current board
   */
  void print() const;

  //-------------------OPERATORS-------------------------

  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   * 
   * @param row 
   * @return T* 
   */
  inline T *operator()(const std::size_t row);
  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   * 
   * @param row 
   * @return const T* 
   */
  inline const T *operator()(const std::size_t row) const;

  /**
   * @brief returns value at [row][col] on the board
   * 
   * @param row 
   * @param col 
   * @return T 
   */
  inline const T &operator()(const std::size_t row, const std::size_t col) const;
  /**
   * @brief returns value at [row][col] on the board
   * 
   * @param row 
   * @param col 
   * @return T 
   */
  inline T &operator()(const std::size_t row, const std::size_t col);

protected:
  std::size_t _rows; //rows size
  std::size_t _cols; //column size
  grid<T> _board;    //2D board for a game

  //-------------------FUNCTIONS--------------------

  /**
   * @brief initiaze the board with rowXcol empty values
   * 
   * @param default_val 
   */
  void _InitBoard(T &default_val);

  /**
   * @brief initiaze the board with rowXcol empty values
   * 
   */
  void _InitBoard();

  /**
   * @brief return the reference to value at row,col
   * 
   * @param row 
   * @param col 
   * @return T& 
   */
  T &_AtRowCol(const std::size_t row, const std::size_t col);

  /**
   * @brief  direct pointer to the memory array used internally by the board to store its owned elements.
   * 
   * @param row 
   * @return <T>* 
   */
  T *_ToPtr(const std::size_t row);

  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   * @return <T>** 
   * @note Used by this->data()
   */
  T **_ToPtr();

  //----------------------OVERLOADING----------------

  /**
   * @brief overloading of stream operator
   * 
   * @param ostream&
   * @param Board& 
   * @return ostream& 
   */
  friend std::ostream &operator<<(std::ostream &, const Board &);
};

//-------------------------------------------------------------------------------------------------------
//---------------------------------------IMPLEMENTATION--------------------------------------------------
//-------------------------------------------------------------------------------------------------------

template <typename T>
inline Board<T>::Board() : _rows(0), _cols(0) {}

template <typename T>
inline Board<T>::Board(const std::size_t rows, const std::size_t cols) : _rows(rows), _cols(cols)
{
  _InitBoard();
}

template <typename T>
inline Board<T>::Board(const std::size_t rows, const std::size_t cols, const T default_val) : _rows(rows), _cols(cols)
{
  _InitBoard(default_val);
}

template <typename T>
inline Board<T>::Board(const T **board, const std::size_t rows, const std::size_t cols)
{
  _InitBoard();
  for (auto row = 0; row < _rows; ++row)
    for (auto col = 0; col < _cols; ++col)
      _board.at(row).at(col) = board[row][col];
}

template <typename T>
inline Board<T>::~Board()
{
  clear();
}

template <typename T>
inline std::size_t Board<T>::rows() const
{
  return rows;
}

template <typename T>
inline std::size_t Board<T>::cols() const
{
  return cols;
}

template <typename T>
inline const T &Board<T>::at(const std::size_t row, const std::size_t col) const
{
  return _AtRowCol(row, col);
}

template <typename T>
inline T &Board<T>::at(const std::size_t row, const std::size_t col)
{
  return _AtRowCol(row, col);
}

template <typename T>
inline T **Board<T>::data()
{
  return _ToPtr();
}

template <typename T>
inline const T **Board<T>::data() const
{
  return _ToPtr();
}

template <typename T>
inline void Board<T>::resize(const std::size_t rows_, const std::size_t cols_)
{
  _rows = rows_;
  _cols = cols_;
  _board.resize(_rows);
  for (auto &row : _board)
    row.resize(_cols);
}

template <typename T>
inline void Board<T>::resize(const std::size_t rows_, const std::size_t cols_, const T default_val)
{
  _rows = rows_;
  _cols = cols_;
  _board.resize(_rows);
  for (auto &row : _board)
    row.resize(_cols, default_val);
}

template <typename T>
inline void Board<T>::insert(const std::size_t row, const std::size_t col, const T val)
{
  _board.at(row).at(col) = val;
}

template <typename T>
inline void Board<T>::clear()
{
  for (auto &row : _board)
  {
    row.clear();
    row.shrink_to_fit();
  }

  _rows = _cols = 0;

  _board.clear();
  _board.shrink_to_fit();
}

template <typename T>
inline void Board<T>::del(T **data, const std::size_t rows)
{
  for (auto row = 0; row < rows; ++row)
    delete[] data[row];
  delete[] data;
  return true;
}

template <typename T>
inline bool Board<T>::isFound(const T &val)
{
  for (auto &row : _board)
    for (auto &elem : row)
      if (elem == val)
        return true;
  return false;
}

template <typename T>
inline void Board<T>::print() const
{
}

template <typename T>
inline T *Board<T>::operator()(const std::size_t row)
{
  return _ToPtr(row);
}

template <typename T>
inline const T *Board<T>::operator()(const std::size_t row) const
{
  return _ToPtr(row);
}

template <typename T>
inline const T &Board<T>::operator()(const std::size_t row, const std::size_t col) const
{
  return _AtRowCol(row, col);
}

template <typename T>
inline T &Board<T>::operator()(const std::size_t row, const std::size_t col)
{
  return _AtRowCol(row, col);
}

template <typename T>
inline void Board<T>::_InitBoard(T &default_val)
{
  _board.clear();
  _board.resize(_rows);
  for (auto &row : _board)
    row.resize(_cols, default_val);
}

template <typename T>
inline void Board<T>::_InitBoard()
{
  _board.clear();
  _board.resize(_rows);
  for (auto &row : _board)
    row.resize(_cols);
}

template <typename T>
inline T &Board<T>::_AtRowCol(const std::size_t row, const std::size_t col)
{
  return _board.at(row).at(col);
}

template <typename T>
inline T *Board<T>::_ToPtr(const std::size_t row)
{
  return row < _rows ? _board.at(row).data() : nullptr;
}

template <typename T>
inline T **Board<T>::_ToPtr()
{
  return _board.data();
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Board<T> &B)
{
  B.print();
  return out;
}

BG_END

#endif //BG_BOARD_H_