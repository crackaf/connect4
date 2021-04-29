#ifndef BG_STATE_H_
#define BG_STATE_H_

#include <vector>
#include <map>

#include "bgtypes.h"
#include "bgmove.h"
#include "bgboard.h"
#include "bgplayer.h"
#include "bgplayers.h"

BG_BEGIN

template <typename T>
class Player;

template <typename T>
class State
{
public:
  //-----------------------CONSTRUCTORS--------------------------

  State();
  virtual ~State();

  //----------------------GETTERS-----------------------

  //returns index of the turning player
  inline std::size_t turning_player() const;
  //returns index of the next turning player
  inline std::size_t next_player() const;
  //returns index of the next player with respective to the index given
  inline std::size_t next_player(const std::size_t player_index) const;

  inline const Players<T> &players() const;
  inline Players<T> &players();

  inline const Board<T> &board() const;
  inline Board<T> &board();
  inline const std::map<std::size_t, Move<T> *> &moves() const;
  inline const Move<T> *moves(const std::size_t player_index) const;

  //----------------------SETTERS--------------------------

  inline void set_turning_player(const std::size_t player_index);
  inline bool add_move(const Move<T> &, const int player_index);

  //--------------------------VIRTUAL FUNCTIONS--------------------

  virtual State *Clone() = 0;

  virtual std::vector<Move<T> *> GetPossibleMoves() = 0;

  virtual bool isGameOver() = 0;

  virtual bool isWinningState() = 0;
  virtual bool isWinningState(const int player_index) = 0;

  virtual bool isValidMove(Move<T> *, const int player_index = -1) = 0;

  virtual bool isWinningMove(Move<T> *, const int player_index = -1) = 0;

  //-------------------------FUNCTIONS---------------------------------

  bool MakeMove();

  //--------------------------OPERATORS--------------------------------

  /**
   * @brief direct pointer to the memory array used internally by the Players
   * 
   * @param index 
   * @return const Player<T>* 
   */
  inline const Player<T> *operator()(const std::size_t index) const;
  /**
   * @brief direct pointer to the memory array used internally by the Players
   * 
   * @param index 
   * @return Player<T>* 
   */
  inline Player<T> *operator()(const std::size_t index);

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
  Players<T> _players;                     //players list
  Board<T> _board;                         //game board
  std::map<std::size_t, Move<T> *> _moves; //game moves with player index
  std::size_t _turning_player;             //index of player making a move

  //--------------------------FUNCTIONS----------------------------------

  virtual State *_StaticCast(State *ptr) = 0;

  inline bool _SetMove(Move<T> *move);
  inline T &_BoardAt(const std::size_t row, const std::size_t col);
  inline Player<T> *_PlayerAt(const std::size_t index);
};

//-------------------------------------------------------------------------------------------------------
//---------------------------------------IMPLEMENTATION--------------------------------------------------
//-------------------------------------------------------------------------------------------------------

template <typename T>
inline State<T>::State() : _turning_player(0) {}

template <typename T>
inline State<T>::~State()
{
    _turning_player = 0;
    //delete _players;
    //delete _board;
    //delete _moves;
}

template <typename T>
inline std::size_t State<T>::turning_player() const
{
  return _turning_player;
}

template <typename T>
inline std::size_t State<T>::next_player() const
{
  return next_player(_turning_player);
}

template <typename T>
inline std::size_t State<T>::next_player(const std::size_t player_index) const
{
  return (player_index + 1) % _players.size();
}

template <typename T>
inline const Players<T> &State<T>::players() const
{
  return _players;
}

template <typename T>
inline Players<T> &State<T>::players()
{
  return _players;
}

template <typename T>
inline const Board<T> &State<T>::board() const
{
  return _board;
}

template <typename T>
inline Board<T> &State<T>::board()
{
  return _board;
}

template <typename T>
inline const std::map<std::size_t, Move<T> *> &State<T>::moves() const
{
  return _moves;
}

template <typename T>
const Move<T> *State<T>::moves(const std::size_t player_index) const
{
  return nullptr;
}

template <typename T>
inline void State<T>::set_turning_player(const std::size_t player_index)
{
  return this->_turning_player = player_index;
}

template <typename T>
inline bool State<T>::add_move(const Move<T> &, const int player_index)
{
  return false;
}

template <typename T>
inline bool State<T>::MakeMove()
{
  Move<T> *move = this->_players(_turning_player)->SuggestMove(this->Clone());
  if (!this->isValidMove(move))
    return false;
  this->_SetMove(move);
  return true;
}

template <typename T>
inline const Player<T> *State<T>::operator()(const std::size_t index) const
{
  return _PlayerAt(index);
}

template <typename T>
inline Player<T> *State<T>::operator()(const std::size_t index)
{
  return _PlayerAt(index);
}

template <typename T>
inline const T &State<T>::operator()(const std::size_t row, const std::size_t col) const
{
  return _BoardAt(row, col);
}

template <typename T>
inline T &State<T>::operator()(const std::size_t row, const std::size_t col)
{
  return _BoardAt(row, col);
}

template <typename T>
inline bool State<T>::_SetMove(Move<T> *move)
{
  if (_board.insert(move->row(), move->col(), move->piece()))
  {
    this->add_move(move, this);
    return true;
  }
  return false;
}

template <typename T>
inline T &State<T>::_BoardAt(const std::size_t row, const std::size_t col)
{
  return _board.at(row, col);
}

template <typename T>
inline Player<T>*State<T>::_PlayerAt(const std::size_t index)
{
  return _players.at(index);
}

BG_END

#endif //BG_STATE_H_
