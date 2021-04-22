#ifndef GAMEMOVE_H_
#define GAMEMOVE_H_

namespace boardgame
{
  template <typename T>
  class Move
  {
  public:
    //Default Constructor
    Move();
    //Construct with row, col and value
    Move(const int row, const int col, const T &piece);

    //copy constructor
    Move(const Move &);
    Move(Move *&);

    //Destructor
    ~Move();

    //getters
    inline int row() const;
    inline int col() const;
    inline T piece() const;

    //setters
    inline bool set_row(const int row);
    inline bool set_col(const int col);
    inline bool set_piece(const T &piece);

  protected:
    int _row;
    int _col;
    T _piece;
  };

  template <typename T>
  inline Move<T>::Move() : _row(-1), _col(-1), _piece() {}

  template <typename T>
  inline Move<T>::Move(const int row, const int col, const T &piece) : _row(row), _col(row), _piece(piece) {}

  template <typename T>
  inline Move<T>::Move(const Move &game_move)
  {
    this->_row = game_move._row;
    this->_col = game_move._col;
    this->_piece = game_move._piece;
  }

  template <typename T>
  inline Move<T>::Move(Move *&game_move)
  {
    this->_row = game_move->_row;
    this->_col = game_move->_col;
    this->_piece = game_move->_piece;
  }

  template <typename T>
  inline Move<T>::~Move()
  {
    _row = -1;
    _col = -1;
    _piece = T();
  }

  template <typename T>
  inline int Move<T>::row() const
  {
    return _row;
  }
  template <typename T>
  inline int Move<T>::col() const
  {
    return _col;
  }
  template <typename T>
  inline T Move<T>::piece() const
  {
    return _piece;
  }

  template <typename T>
  inline bool Move<T>::set_row(const int row)
  {
    _row = row;
    return true;
  }

  template <typename T>
  inline bool Move<T>::set_col(const int col)
  {
    _col = col;
    return true;
  }

  template <typename T>
  inline bool Move<T>::set_piece(const T &piece)
  {
    _piece = piece;
    return true;
  }

} // namespace boardgame

#endif //GAMEMOVE_H_