/**
 * @file bgplayer.h
 * @author Hunzlah Malik @ghostdart
 * @brief Implementation of Player Class
 * @version 0.1
 * @date 2021-04-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef BG_PLAYER_H_
#define BG_PLAYER_H_

#include <string>
#include <vector>
#include <algorithm>

#include "bgtypes.h"
#include "bgame.h"
#include "bgpiece.h"
#include "bgmove.h"

BG_BEGIN

template <class T>
class Game;

//using ::bg::Game;
//using ::bg::Move;

/**
 * @brief Abstract Player class for boardgame
 * @code .cpp
 * virtual ~Player();
 * virtual Move* SuggestMove(const Game<T> &) const = 0;
 * virtual Player* copy() const = 0;
 * virtual Player* move() = 0;
 * @endcode
 * 
 * @tparam T
 */
template <class T>
class Player
{
public:
  //-------------------CONSTRUCTORS------------------

  Player() = delete;

  /**
   * @brief Construct a new Player object
   *
   * @param name
   * @param diff_level
   */
  Player(const std::string name, size_t diff_level) : _id{_next_id++}, _name{name}, _diff_level{diff_level}
  {
    _ISDBG_ bgdebug("Player::Player(name,diff)", "_id=" + std::to_string(_id) + "|_name=" + _name + "|_diff" + std::to_string(_diff_level));
  }

  /**
   * @brief Construct a new Player object
   *
   * @param name
   * @param difficulty_level
   * @param Pieces [deep copy] of Piece<T>* [lifetime] [deletes after]
   */
  Player(const std::string name, size_t diff_level, const Piece<T> &piece) : _id{_next_id++}, _name{name}, _diff_level{diff_level}
  {
    _ISDBG_ bgdebug("Player::Player(name,diff,Piece<T>)", "_id=" + std::to_string(_id) + "|_name=" + _name + "|_diff" + std::to_string(_diff_level) + "|piece=" + std::to_string(piece.get()));

    _pieces.push_back(piece.copy());
  }

  /**
   * @brief Construct a new Player object
   *
   * @param name
   * @param difficulty_level
   * @param Pieces [deep move] of Piece<T>* [lifetime] [deletes after]
   */
  Player(const std::string name, size_t diff_level, Piece<T> &&piece) : _id{_next_id++}, _name{name}, _diff_level{diff_level}
  {
    _ISDBG_ bgdebug("Player::Player(name,diff,Piece<T>)", "_id=" + std::to_string(_id) + "|_name=" + _name + "|_diff" + std::to_string(diff_level) + "|piece=" + std::to_string(piece.get()));

    _pieces.push_back(piece.move());
  }

  /**
   * @brief Construct a new Player object
   *
   * @param name
   * @param difficulty_level
   * @param Pieces [deep copy] of list of Piece<T>* [lifetime] [deletes after]
   */
  Player(const std::string name, size_t diff_level, const Pieces<T> &pieces) : _id{_next_id++}, _name{name}, _diff_level{diff_level}
  {
    _ISDBG_ bgdebug("Player::Player(name,diff,Pieces<T>)", "_id=" + std::to_string(_id) + "|_name=" + _name + "|_diff" + std::to_string(diff_level) + "|pieces=" + std::to_string(pieces.size()));

    for (auto &piece : pieces)
      _pieces.push_back(piece->copy());
  }

  Player(const Player<T> &other) : _id{other._id}, _name{other._name}, _diff_level{other._diff_level}
  {
    for (const auto &p : other._pieces)
      _pieces.push_back(p->copy());
  }

  Player<T> &operator=(const Player<T> &other)
  {
    if (this != &other)
    {
      // Free the existing resource.
      _name.clear();

      for (auto &p : _pieces)
        delete p;
      _pieces.clear();

      // Copy the data source object.
      // _id = other.id;
      _name = other.name;
      _diff_level = other._diff_level;

      for (const auto &p : other._pieces)
        _pieces.push_back(p->copy());
    }
    return *this;
  }

  Player(Player<T> &&other) : _id{other._id}, _name{other._name}, _diff_level{other._diff_level}
  {
    *this = std::move(other);
  }

  Player<T> &operator=(Player<T> &&other)
  {
    if (this != &other)
    {
      // Free the existing resource.
      _name.clear();

      for (auto &p : _pieces)
        delete p;
      _pieces.clear();

      // Copy the data pointer from the source object.
      //_id = other._id;
      _name = other._name;
      _diff_level = other._diff_level;

      for (auto &p : other._pieces)
        _pieces.push_back(p->move());

      // Release the data pointer from the source object so that
      // the destructor does not free the memory multiple times.
      other._pieces.clear();
      other._name.clear();
      other._diff_level = 0;
    }
    return *this;
  }

  /**
   * @brief [virtual] Destroy the Player object
   */
  virtual ~Player()
  {
    _ISDBG_ bgdebug("Player::~Player", "_id=" + std::to_string(_id));

    _diff_level = 0;

    _name.clear();

    for (auto &it : _pieces)
      delete it;
    _pieces.clear();
  }

  //-----------------------GETTERS-------------------------

  inline auto name() const noexcept { return _name; }
  inline auto id() const noexcept { return _id; }
  inline auto diff_level() const noexcept { return _diff_level; }
  inline const auto &pieces() const { return _pieces; }

  //-----------------------SETTERS-------------------------

  inline void set_name(const std::string &name) { _name = name; }
  inline void set_diff_level(size_t diff_level) { _diff_level = diff_level; }

  /**
   * @brief inserting piece
   *
   * @param piece [deep copy] [lifetime] [deletes after]
   */
  inline void insert(const Piece<T> &piece)
  {
    _ISDBG_ bgdebug("Player::insert(Piece<T>)", "_id=" + std::to_string(_id));

    _pieces.push_back(piece.copy());
  }

  /**
 * @brief inserting piece
 *
 * @param piece [deep copy] [lifetime] [deletes after]
 */
  inline void insert(Piece<T> &&piece)
  {
    _ISDBG_ bgdebug("Player::insert(Piece<T>)", "_id=" + std::to_string(_id));

    _pieces.push_back(piece.move());
  }

  /**
   * @brief inserting list of Piece<T>*
   * @param Pieces std::vector<Pieces<T>*>, [deep copy] of list of Piece<T>* [lifetime] [deletes after]
   */
  inline void insert(const Pieces<T> &pieces)
  {
    _ISDBG_ bgdebug("Player::insert(Pieces<T>)", "_id=" + std::to_string(_id));

    for (auto &piece : pieces)
      _pieces.push_back(piece->copy());
  }

  //------------------------FUNCTIONS-----------------------------

  /**
   * @brief checking if this piece exists in player pieces.
   * @param Piece [only using, no delete]
   * @return true | false
   */
  inline bool IsPlayerPiece(const Piece<T> &piece) const
  {
    _ISDBG_ bgdebug("Player::IsPlayerPiece", "_id=" + std::to_string(_id));

    for (auto &p : _pieces)
      if (p && &piece && *p == piece)
        return true;
    return false;
  }

  /**
   * @brief checking if this piece exists in player pieces.
   * @param Piece [only using, no delete]
   * @return int -1==>no
   */
  inline auto FindPiece(const Piece<T> &piece) const
  {
    _ISDBG_ bgdebug("Player::_FinePiece", "_id=" + std::to_string(_id));

    auto it = std::find(_pieces.begin(), _pieces.end(), piece);
    if (it != _pieces.end())
      return std::distance(_pieces.begin(), it);
    return -1;
  }

  //----------------------VIRTUAL---------------------
  /**
   * @brief [pure virtual] suggest move while looking at the current game state
   *
   * @param state [only using, no delete]
   * @return Move<T>*
   */
  virtual Move<T> *SuggestMove(const Game<T> &) const = 0;
  virtual Player<T> *copy() const = 0;
  virtual Player<T> *move() = 0;

protected:
  csize_t _id{_next_id++}; //unique player id
  std::string _name;       //player name
  size_t _diff_level{0};   //difficulty level
  Pieces<T> _pieces;       //pieces of current player

private:
  inline static size_t _next_id{0}; //changes for every new object
};

BG_END

#endif //BG_PLAYER_H_