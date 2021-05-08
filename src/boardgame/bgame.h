/**
 * @file bgame.h
 * @author Hunzlah Malik @ghostdart
 * @brief Implementation of Game Class
 * @version 0.1
 * @date 2021-05-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BG_GAME_H_
#define BG_GAME_H_

#include <vector>

#include "bgtypes.h"
#include "bgmove.h"
#include "bgboard.h"
#include "bgplayer.h"
#include "bgplayers.h"
#include "bgpiece.h"

BG_BEGIN

template <class T>
class Player;

template <class T>
class Players;

using ::bg::Board;
using ::bg::Move;
using ::bg::Player;
using ::bg::Players;

template <class T>
using BNode = Piece<T>; //piece

template <class T>
using PBoard = Board<BNode<T>>; //pieces board

namespace game
{
  enum class Enum
  {
    DRAW,   //no more moves
    OVER,   //someone won
    NOTOVER //running state
  };
} //namespace game

/**
 * @brief Abstract Game State
 * @code .cpp
 * MUST override these
 * 
 * virtual size_t NextPlayer(size_t playerid) const = 0;
 * virtual const std::vector<Move<T> *> GetPossibleMoves(size_t playerid) const = 0;
 * virtual bool IsWinningState(size_t playerid) const = 0;
 * virtual bool IsValid(const Move<T> &, size_t playerid) const = 0;
 * virtual bool IsWinning(const Move<T> &, size_t playerid) const = 0;
 * virtual bool IsNoMoreMoves() const = 0;
 * virtual bool Apply(const Move<T> &) = 0;
 * virtual Game *copy() const = 0;
 * virtual Game *move() = 0;
 *
 * CAN override these
 *
 * virtual ~Game();
 * virtual int MakeMove();
 * virtual bool IsWinningStateRecheck();
 * virtual bool IsDrawStateRecheck();
 *
 * @endcode
 * 
 * @tparam T
 */
template <class T>
class Game
{
public:
  //-----------------------CONSTRUCTORS--------------------------

  Game() = delete;

  Game(size_t turning_player, const Players<T> &P, const PBoard<T> &B)
      : _turning_player{0}, _winner{-1}, _state{game::Enum::NOTOVER},
        _players{P.copy()},
        _board{B.copy()} {}

  Game(size_t turning_player, Players<T> &&P, PBoard<T> &&B)
      : _turning_player{0}, _winner{-1}, _state{game::Enum::NOTOVER},
        _players{P.move()},
        _board{B.move()} {}

  Game(const Game &other)
      : _turning_player{other._turning_player}, _winner{other._winner}, _state{other._state},
        _players{other._players->copy()},
        _board{other._board->copy()}
  {
    for (const auto &[key, val] : other._moves)
      _moves.push_back({key, val->copy()});
  }

  Game<T> &operator=(const Game<T> &other)
  {
    if (this != &other)
    {
      // Free the existing resource.
      deleteptr(_players);

      deleteptr(_board); //calling the destructor

      for (auto &[key, value] : _moves)
        delete value;
      _moves.clear();

      // Copy the data pointer from the source object.
      _turning_player = other._turning_player;
      _winner = other._winner;
      _state = other._state;
      _players = other._players->copy(); //deep copy
      _board = other._board->copy();     //deep copy

      for (const auto &[key, val] : other._moves)
        _moves.push_back({key, val->copy()}); //deep copy
    }
    return *this;
  }

  Game(Game &&other)
      : _turning_player{other._turning_player}, _winner{other._winner}, _state{other._state}
  {
    *this = std::move(other);
  }
  Game<T> &operator=(Game<T> &&other)
  {
    if (this != &other)
    {
      // Free the existing resource.
      deleteptr(_players);
      deleteptr(_board);

      for (auto &[key, value] : _moves)
        delete value;
      _moves.clear();

      // Copy the data pointer from the source object.
      _turning_player = other._turning_player;
      _winner = other._winner;
      _state = other._state;
      _players = other._players->move(); //shallow copy
      _board = other._board->move();     //shallow copy

      for (const auto &[key, val] : other._moves)
        _moves.push_back({key, val}); //shallow copy

      // Release the data pointer from the source object so that
      // the destructor does not free the memory multiple times.
      other._turning_player = other._winner = -1;
      other._state = game::Enum::NOTOVER;
      other._players = nullptr;
      other._board = nullptr;
      other._moves.clear();
    }
    return *this;
  }

  virtual ~Game()
  {
    _turning_player = _winner = -1;
    _state = game::Enum::NOTOVER;

    deleteptr(_players);
    deleteptr(_board); //calling the destructor

    for (auto &[key, value] : _moves)
      delete value; //deleting moves
    _moves.clear();
  }

  //----------------------GETTERS-----------------------

  inline auto winner() const noexcept { return _winner; }
  inline auto turning_player() const noexcept { return _turning_player; }
  inline auto state() const noexcept { return _state; }

  //PLAYER getter
  inline const auto players() const noexcept { return _players; }
  inline auto players() noexcept { return _players; }
  inline const auto &at(size_t playerid) const { return _players->at(playerid); }
  //BOARD getters
  inline const auto board() const noexcept { return _board; }
  inline auto board() noexcept { return _board; }
  inline const auto &at(size_t row, size_t col) const { return _board->at(row, col); }

  inline const auto &moves() const noexcept { return _moves; }
  inline const auto &moves(size_t playerid) const
  {
    std::vector<const Move<T> *> ret;
    for (const auto &[key, value] : _moves)
      if (playerid == key)
        ret.push_back(value);
    return ret;
  }

  //----------------------SETTERS--------------------------

  inline void set_turning_player(size_t playerid) { _turning_player = playerid; }
  inline void insert(size_t playerid, const Move<T> &mov) { _moves.push_back({playerid, mov.copy()}); }
  inline void insert(size_t playerid, Move<T> &&mov) { _moves.push_back({playerid, mov.move()}); }

  //PLAYERS setters
  inline bool insert(const Player<T> &P) { return _players->insert(P); }
  inline bool insert(Player<T> &&P) { return _players->insert(std::forward<Player<T>>(P)); }
  //BOARD setters
  inline bool insert(size_t row, size_t col, const BNode<T> &P) { return _board->insert(row, col, P); }
  inline bool insert(size_t row, size_t col, BNode<T> &&P) { return _board->insert(row, col, std::forward<BNode<T>>(P)); }

  //--------------------------VIRTUAL FUNCTIONS--------------------

  //returns playerid of the next player with respective to the playerid given
  virtual size_t NextPlayer(size_t playerid) const = 0;
  virtual const std::vector<Move<T> *> GetPossibleMoves(size_t playerid) const = 0;
  virtual bool IsWinningState(size_t playerid) const = 0;
  virtual bool IsValid(const Move<T> &, size_t playerid) const = 0;
  virtual bool IsWinning(const Move<T> &, size_t playerid) const = 0;
  virtual bool IsNoMoreMoves() const = 0;
  virtual bool Apply(const Move<T> &) = 0;
  virtual Game *copy() const = 0;
  virtual Game *move() = 0;

  //-------------------------FUNCTIONS---------------------------------

  //returns playerid of the next turning player
  inline auto NextPlayer() const { return NextPlayer(_turning_player); }
  bool Apply(Move<T> &&mov) { return Apply(mov.copy()); }
  inline const auto &GetPossibleMoves() const { return GetPossibleMoves(_turning_player); }
  inline bool IsValid(const Move<T> &mov) const { return IsValid(mov, _turning_player); }
  inline bool IsWinning(const Move<T> &mov) const { return IsWinning(mov, _turning_player); }
  inline bool IsWinningState() const noexcept { return _state == game::Enum::OVER; }
  inline bool IsDrawState() const noexcept { return _state == game::Enum::DRAW; }

  /**
 * @brief makes the next move and changes the `turning_player`
 * @return 0==>INVALID | 1==>VALID | 2==>WINNING
 */
  virtual size_t MakeMove()
  {
    if (!(_state == game::Enum::NOTOVER))
      return 0;

    Move<T> *move = _players->at(_turning_player)->SuggestMove(*this);

    if (!IsValid(*move))
      return 0;
    else if (IsWinning(*move))
    {
      _state = game::Enum::OVER;
      _winner = _turning_player;
    }

    int ret = _state == game::Enum::OVER ? int(Apply(*move)) * 2 : Apply(*move);
    deleteptr(move);
    return ret;
  }

  virtual bool IsWinningStateRecheck()

  {
    for (const auto &player : _players->data())
      if (IsWinningState(player->id()))
      {
        _state = game::Enum::OVER;
        _winner = player->id();
        return true;
      }
    return false;
  }

  virtual bool IsDrawStateRecheck()
  {
    if (IsWinningStateRecheck())
      return false;
    else if (IsNoMoreMoves())
      return true;

    _state = game::Enum::NOTOVER;
    return false;
  }

  //--------------------------OPERATORS--------------------------------

  /**
 * @brief direct pointer to the memory array used internally by the Players
 *
 * @param playerid
 * @return const Player<T>*
 */
  inline const auto &operator[](size_t playerid) const { return _players->at(playerid); }
  /**
 * @brief direct pointer to the memory array used internally by the Players
 *
 * @param playerid
 * @return Player<T>*
 */
  inline auto &operator[](size_t playerid) { return _players->at(playerid); }

  /**
 * @brief returns value at [row][col] on the board
 *
 * @param row
 * @param col
 * @return Piece<T>* can be nullptr
 */
  inline const auto &operator()(size_t row, size_t col) const { return _board->at(row, col); }

  /**
 * @brief returns value at [row][col] on the board
 *
 * @param row
 * @param col
 * @return Piece<T>* can be nullptr
 */
  inline auto &operator()(size_t row, size_t col) { return _board->at(row, col); }

protected:
  //--------------------------FUNCTIONS----------------------------------

  inline void _SetMove(const Move<T> &mov)
  {
    _board->insert(mov->row(), mov->col(), mov->piece());
    insert(mov, _turning_player);
  }

  inline void _SetMove(Move<T> &&mov)
  {
    _board->insert(mov->row(), mov->col(), mov->piece());
    insert(mov, _turning_player);
  }

  inline void _set_state(game::Enum se) { _state = se; }
  inline auto &_BoardAt(size_t row, size_t col) { return _board->at(row, col); }
  inline auto &_PlayerAt(size_t playerid) { return _players->at(playerid); }

protected:
  int_t _turning_player{-1};                              //id of player making a move
  int_t _winner{-1};                                      //winner id
  game::Enum _state{game::Enum::NOTOVER};                 //game state |OVER, NOTOVER, WINNING
  Players<T> *_players{nullptr};                          //players list
  PBoard<T> *_board{nullptr};                             //game pieces board
  std::vector<std::pair<size_t, const Move<T> *>> _moves; //in order game moves with player id
};

BG_END

#endif //BG_GAME_H_
