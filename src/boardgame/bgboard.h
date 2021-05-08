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

#include <vector>
#include <utility>

#include "bgtypes.h"

BG_BEGIN

/* sample board
  rows
  ^
  |
  5   50  51  52  54  54  55
  4   40  41  42  43  44  45
  3   30  31  32  33  34  35
  2   20  21  22  23  24  25
  1   10  11  12  13  14  15
  0   00  01  02  03  04  05

      0   1   2   3   4   5 --> cols
*/

/**
 * @brief new type defined for board
 * @details std::vector<std::vector<class T *>>
 * @code .cpp
 * virtual ~Board();
 * virtual Board* copy() const;
 * virtual Board* move();
 * @endcode
 * 
 * @tparam T
 */
template <class T>
using grid = std::vector<std::vector<T>>;

struct Point
{
  int_t row{0}, col{0};
};

/**
 * @brief General Board class to store the row x col board of the game
 * @tparam T is the type of which board will be created
 */
template <class T>
class Board
{
public:
  //-------------------CONSTRUCTORS------------------

  Board() {}

  /**
   * @brief [deep copy] Construct a new Board object
   */
  Board(const Board<T> &other) : _rows{other._rows}, _cols{other._cols}
  {
    _board.resize(_rows);
    for (auto r = 0; r < _rows; ++r)
      for (auto c = 0; c < _cols; ++c)
        _board.at(r).push_back(other._board.at(r).at(c) ? new T{*(other._board.at(r).at(c))} : nullptr);
  }

  Board<T> &operator=(const Board<T> &other)
  {
    if (this != &other)
    {
      // Free the existing resource.
      clear();

      // Copy the data pointer from the source object.
      _rows = other._rows;
      _cols = other._cols;

      _board.resize(_rows);
      for (auto r = 0; r < _rows; ++r)
        for (auto c = 0; c < _cols; ++c)
          _board.at(r).push_back(other._board.at(r).at(c) ? new T{*(other._board.at(r).at(c))} : nullptr); //shallow copying
    }
    return *this;
  }

  /**
  * @brief Move to a new Board object
  */
  Board(Board<T> &&other) noexcept : _rows{other._rows}, _cols{other._cols} { *this = std::move(other); }
  Board<T> &operator=(Board<T> &&other)
  {
    if (this != &other)
    {
      // Free the existing resource.
      clear();

      // Copy the data pointer from the source object.
      _rows = other._rows;
      _cols = other._cols;

      _board.resize(_rows);
      for (auto r = 0; r < _rows; ++r)
        for (auto c = 0; c < _cols; ++c)
          _board.at(r).push_back(other._board.at(r).at(c)); //shallow copyinh

      // Release the data pointer from the source object so that
      // the destructor does not free the memory multiple times.
      other._board.clear();
      other._rows = other._cols = 0;
    }
    return *this;
  }

  /**
   * @brief Construct a new Board object
   *
   * @param rows number of rows of new Board
   * @param cols number of cols of new Board
   */
  Board(size_t rows, size_t cols) : _rows{rows}, _cols{cols} { _InitBoard(); }

  /**
   * @brief Construct a new Board object with given 2D board
   *
   * @param board [deep copy of T] 2D board you want to copy
   * @param rows rows of the given board
   * @param cols cols of the given board
   */
  Board(const T **board, size_t rows, size_t cols) : _rows{rows}, _cols{cols}
  {
    _InitBoard();
    for (auto row = 0; row < _rows; ++row)
      for (auto col = 0; col < _cols; ++col)
        _board.at(row).at(col) = new T{board[row][col]};
  }

  /**
   * @brief [virtual] Destroy the Board object
   */
  virtual ~Board() { clear(); }

  //-----------------------GETTERS-------------------------

  /**
   * @brief number of rows
   * @return size_t
   */
  inline auto rows() const noexcept { return _rows; }

  /**
   * @brief number of columns
   *
   * @return size_t
   */
  inline auto cols() const noexcept { return _cols; }

  /**
   * @brief const reference to value at row,col
   *
   * @param row
   * @param col
   * @return const T*
   */
  inline const auto &at(size_t row, size_t col) const { return _board.at(row).at(col); }

  /**
   * @brief reference to value at row,col
   * @param row
   * @param col
   * @return T&
   */
  inline auto &at(size_t row, size_t col) { return _board.at(row).at(col); }

  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   * @return const  T**
   */
  inline const auto &data() const { return _ToPtr(); }

  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   * @return T**
   */
  inline auto &data() { return _ToPtr(); }

  //-----------------------SETTERS-------------------------

  /**
   * @brief resize the board object
   *
   * @param rows
   * @param cols
   */
  inline void resize(size_t myrows, size_t mycols) noexcept
  {
    _rows = _board.size();
    if (myrows < _rows)
      for (auto r = myrows; r < _rows; ++r)
        for (auto &c : _board[r])
          deleteptr(c); //delete extra

    _board.resize(myrows);

    if(_board.size()>0)
    _cols = _board.at(0).size();

    for (auto &row : _board)
    {
      if (mycols < _cols)
        for (auto c = mycols; c < _cols; ++c)
          deleteptr(row[c]);       //delete extra
      row.resize(mycols, nullptr); //resize
    }
    _rows = myrows;
    _cols = mycols;
    if (_rows == 0 && _cols == 0)
      _board.clear();
  }

  /**
   * @brief Set the board object
   *
   * @param row
   * @param col
   * @param val [deel copy of T]
   */
  inline void insert(size_t row, size_t col, const T &val)
  {
    erase(row, col);
    if(&val)
    _board.at(row).at(col) = new T{val};
  }

  /**
   * @brief Set the board object
   *
   * @param row
   * @param col
   * @param val [copy of T] (move constructor)
   */
  inline void insert(size_t row, size_t col, T &&val)
  {
    erase(row, col);
    _board.at(row).at(col) = new T{std::forward<T>(val)};
  }

  /**
   * @brief resets the board
   */
  void clear() noexcept { resize(0, 0); }

  inline void erase(size_t row, size_t col) { deleteptr(_board.at(row).at(col));}

  /**
   * @brief deletes the dynamic array
   *
   * @param data T**
   * @param rows
   */
  static void del(T **data, size_t rows)
  {
    for (auto row = 0; row < rows; ++row)
      deletearr(data[row]);
    deletearr(data);
  }

  //------------------------MEMBER FUNCTIONS-----------------------------

  /**
   * @brief check if the board contains or not
   *
   * @param val to check in board
   * @return true | false
   */
  bool IsFound(const T &val) const
  {
    for (const auto &row : _board)
      for (const auto &elem : row)
        if (elem && *elem == val)
          return true;
    return false;
  }

  /**
   * @brief returns the first position found of val
   *
   * @param val to check in board
   * @return {row,col}
   */
  auto &Find(const T &val) const
  {
    for (auto row = 0; row < _rows; ++row)
      for (auto col = 0; col < _cols; ++col)
        if (_board.at(row).at(col) && *(_board.at(row).at(col)) == val)
          return {row, col};
    return {-1, -1};
  }

  /**
   * @brief copy of array used internally by the board to store its owned elements.
   *
   * @param row
   * @return T*
   */
  inline auto &GetRow(size_t row) const { return _ToPtrRow(row); }

  /**
   * @brief copy of array used internally by the board to store its owned elements.
   *
   * @param row
   * @return T*
   */
  inline auto &GetCol(size_t col) const { return _ToPtrCol(col); }

  //-------------------OPERATORS-------------------------

  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   *
   * @param row
   * @return T** or nullptr
   */
  inline auto &operator[](size_t row) { return _board.at(row).data(); }

  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   *
   * @param row
   * @return const T** or nullptr
   */
  inline const auto &operator[](size_t row) const { return _board.at(row).data(); }

  /**
   * @brief returns reference value at [row][col] on the board
   *
   * @param row
   * @param col
   * @return T* or nullptr
   */
  inline const auto &operator()(size_t row, size_t col) const { return _board.at(row).at(col); }

  /**
   * @brief returns reference value at [row][col] on the board
   *
   * @param row
   * @param col
   * @return T* or nullptr
   */
  inline auto &operator()(size_t row, size_t col) { return _board.at(row).at(col); }

  //--------------------VIRTUAL--------------------------

  virtual Board<T> *copy() const { return new Board<T>{*this}; }
  virtual Board<T> *move() { return new Board<T>{std::forward<Board<T>>(*this)}; }

protected:
  size_t _rows{0};  //rows size
  size_t _cols{0};  //column size
  grid<T *> _board; //2D board for a game

private:
  //-------------------FUNCTIONS--------------------

  /**
   * @brief initiaze the board with rowXcol empty values
   *
   */
  void _InitBoard()
  {
    auto drow = _rows, dcol = _cols;
    _rows = _cols = 0;
    clear();
    resize(drow, dcol);
  }

  /**
   * @brief  copy of array used internally by the board to store its owned elements.
   *
   * @param row
   * @return <T>*
   */
  auto _ToPtrRow(size_t row) const
  {
    if (row >= _rows || row < 0)
      return nullptr;

    T *ptr = new T[_cols];
    int index = 0;
    for (const auto &ele : _board.at(row))
      ptr[index++] = ele? T{*ele}:T{};
    return ptr;
  }

  /**
   * @brief  copy of array used internally by the board to store its owned elements.
   *
   * @param col
   * @return <T>*
   */
  auto _ToPtrCol(size_t col) const
  {
    if (col >= _cols || col < 0)
      return nullptr;

    T *ptr = new T[_rows];

    int index = 0;
    for (auto &row : _board)
      ptr[index++] = row.at(col)? T{*(row.at(col))}:T{};

    return ptr;
  }

  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   * @return <T>***
   * @note Used by this->data()
   */
  auto &_ToPtr(){return _board.data();}

  /**
   * @brief direct pointer to the memory array used internally by the board to store its owned elements.
   * @return <T>**
   * @note Used by this->data()
   */
  inline auto &_ToPtr(size_t row) { return row < _rows && row >= 0 ? _board.at(row).data() : nullptr;}

  //----------------------OVERLOADING----------------

  /**
   * @brief overloading of stream operator
   *
   * @param ostream&
   * @param Board&
   * @return ostream&
   */
  // friend std::ostream &operator<<(std::ostream &, const Board<T> &);
};

BG_END

#endif //BG_BOARD_H_