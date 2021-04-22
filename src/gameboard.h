#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include <vector>

namespace boardgame
{
  template <typename T>
  class Board
  {
  public:
    using BOARD = std::vector<std::vector<T>>; // new type defined for board

    //Default Constructor
    Board();
    //Construct Board with rows, cols and default value in board
    Board(const int rows, const int cols, const T default_val = NULL);
    //Construct Board with a 2D board given with rows and cols
    Board(const T **board, const int rows, const int cols);

    //copy constructor
    Board(const Board &);
    Board(Board *&);

    //Destructor
    ~Board();

    //getters
    inline int rows() const;                            //get number of rows
    inline int cols() const;                            //get number of cols
    inline T board(const int row, const int col) const; //get val at row,col
    T **board() const;                                  //get copy of whole board

    //setters
    inline int set_rows(const int rows);
    inline int set_cols(const int cols);
    inline bool board(int row, int col, T val);

    //reset board
    bool reset();
    // delete pointers
    static bool del(T **data, const int rows);

    //operator overloading using () and (,) for indexing
    inline T *operator()(const int row) const;
    inline T operator()(const int row, const int col) const;

  protected:
    int kRows;    //rows size
    int kCols;    //column size
    BOARD _board; //2D board for a game

    void initialize_board(bool useVal = false, const T default_val = NULL);
  };

  template <typename T>
  inline Board<T>::Board() : kRows(0), kCols(0) {}

  template <typename T>
  Board<T>::Board(const int rows, const int cols, const T default_val) : kRows(rows), kCols(cols)
  {
    this->initialize_board(true, default_val);
  }

  template <typename T>
  Board<T>::Board(const T **board, const int rows, const int cols) : kRows(rows), kCols(cols)
  {
    this->initialize_board();
    for (auto row = 0; row < kRows; ++row)
      for (auto col = 0; col < kCols; ++col)
        this->_board.at(row).at(col) = board[row][col];
  }

  template <typename T>
  inline Board<T>::Board(const Board &game_board)
  {
    this->kRows = game_board.kRows;
    this->kCols = game_board.kCols;
    this->_board = game_board._board;
  }

  template <typename T>
  inline Board<T>::Board(Board *&game_board)
  {
    this->kRows = game_board->kRows;
    this->kCols = game_board->kCols;
    this->_board = game_board->_board;
  }

  template <typename T>
  Board<T>::~Board()
  {
    this->reset();
  }

  template <typename T>
  inline int Board<T>::rows() const
  {
    return kRows;
  }

  template <typename T>
  inline int Board<T>::cols() const
  {
    return kCols;
  }

  template <typename T>
  inline T Board<T>::board(int row, int col) const
  {
    if (row < kRows && col < kCols)
      return _board.at(row).at(col);
    return NULL;
  }

  template <typename T>
  T **Board<T>::board() const
  {
    T **ret_board = new T *[kRows];
    for (auto row = 0; row < kRows; ++row)
    {
      ret_board[row] = new T[kCols];
      for (auto col = 0; col < kCols; ++col)
        ret_board[row][col] = _board.at(row).at(col);
    }
    return ret_board;
  }

  template <typename T>
  inline int Board<T>::set_rows(const int rows)
  {
    kRows = rows;
    _board.resize(rows);
    return kRows;
  }

  template <typename T>
  inline int Board<T>::set_cols(const int cols)
  {
    kCols = cols;
    for (auto row = 0; row < kRows; ++row)
      _board.at(row).resize(kCols);
    return kCols;
  }

  template <typename T>
  bool Board<T>::board(int row, int col, T val)
  {
    if (row < kRows && col < kCols)
    {
      _board.at(row).at(col) = val;
      return true;
    }
    return false;
  }

  template <typename T>
  bool Board<T>::reset()
  {
    for (auto row = 0; row < kRows; ++row)
      _board.at(row).clear();
    kRows = kCols = 0;

    _board.clear();
    _board.shrink_to_fit();

    return true;
  }

  template <typename T>
  bool Board<T>::del(T **data, const int rows)
  {
    for (auto row = 0; row < rows; ++row)
      delete[] data[row];
    delete[] data;
    return true;
  }

  template <typename T>
  inline T *Board<T>::operator()(const int row) const
  {
    if (row < kRows)
      return _board.at(row).data();
    return nullptr;
  }

  template <typename T>
  inline T Board<T>::operator()(const int row, const int col) const
  {
    return this->board(row, col);
  }

  template <typename T>
  void Board<T>::initialize_board(bool useVal, const T default_val)
  {
    _board.resize(kRows);
    for (auto row = 0; row < kRows; ++row)
      if (useVal)
        _board.at(row).resize(kCols, default_val);
      else
        _board.at(row).resize(kCols);
  }

} // namespace boardgame

#endif //GAMEBOARD_H_
