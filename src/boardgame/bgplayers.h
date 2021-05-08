/**
 * @file bgboard.h
 * @author Hunzlah Malik @ghostdart
 * @brief Implementation of Players Class
 * @version 0.1
 * @date 2021-04-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef BG_PLAYERS_H_
#define BG_PLAYERS_H_

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <utility>

#include "bgtypes.h"
#include "bgplayer.h"

BG_BEGIN

template <typename T>
class Player;

/**
 * @brief General Players class for storing list of Player
 * @code .cpp
 * virtual ~Players();
 * @endcode
 * 
 * @tparam T
 */
template <typename T>
class Players
{
public:
  //-------------------CONSTRUCTORS----------------------------------------------------------

  /**
   * @brief Construct a new Players object
   */
  Players() noexcept : _min{0}, _max{0}
  {
    _ISDBG_ bgdebug("Players::Players", "_min=" + std::to_string(_min) + "|_max" + std::to_string(_max) + "|_players=" + std::to_string(_players.size()));
  }

  /**
   * @brief Construct a new Players object
   *
   * @param min minimum number of players
   * @param max maximum number of players
   */
  Players(size_t min, size_t max) noexcept : _min{min}, _max{max}
  {
    _ISDBG_ bgdebug("Players::Players(size_t,size_t)", "_min=" + std::to_string(_min) + "|_max" + std::to_string(_max) + "|_players=" + std::to_string(_players.size()));
  }

  Players(const Players<T> &other) : _min{other._min}, _max{other._max}
  {
    for (const auto &[key, val] : other._players)
      _players.insert({key, val->copy()}); //copying data from pointer
  }

  Players<T> &operator=(const Players<T> &other)
  {
    if (this != &other)
    {
      // Free the existing resource.
      for (auto &[key, value] : _players)
        delete value;
      _players.clear();

      // Copy the data pointer from the source object.
      _min = other._max;
      _min = other._max;
      for (const auto &[key, val] : other._players)
        _players.insert({key, val->copy()}); //copying data from pointer
    }
    return *this;
  }

  Players(Players<T> &&other) : _min{other._min}, _max{other._max} {  *this = std::move(other); }

  Players<T> &operator=(Players<T> &&other)
  {
    if (this != &other)
    {
      // Free the existing resource.
      for (auto &[key, value] : _players)
        delete value;
      _players.clear();

      // Copy the data pointer from the source object.
      _min = other._max;
      _min = other._max;
      for (const auto &[key, val] : other._players)
        _players.insert({key, val->move()}); //moving data from pointer

      // Release the data pointer from the source object so that
      // the destructor does not free the memory multiple times.
      other._players.clear();
      other._min = other._max = 0;
    }
    return *this;
  }

  /**
   * @brief [virtual] Destroy the Players object
   */
  virtual ~Players()
  {
    _ISDBG_ bgdebug("Players::~Players", "_min=" + std::to_string(_min) + "|_max" + std::to_string(_max) + "|_players=" + std::to_string(_players.size()));

    _min = _max = 0;

    for (auto &[key, value] : _players)
      delete value;
    _players.clear();
  }

  //-----------------------GETTERS------------------------------------------------------------

  //get maximum number of players
  inline auto max() const noexcept { return _max; }
  //get minimum number of players
  inline auto min() const noexcept { return _min; }
  //get size of Player list
  inline auto size() const noexcept { return _players.size(); }

  /**
   * @brief direct refrence to the player object
   *
   * @param playerid
   * @return const Player<T>&
   */
  const auto &at(size_t playerid) const
  {
    _ISDBG_ bgdebug("Players::at", "_min=" + std::to_string(_min) + "|_max" + std::to_string(_max) + "|_players=" + std::to_string(_players.size()));

    return _players.at(playerid);
  }
  /**
   * @brief direct refrence to the player object
   *
   * @param playerid
   * @return Player<T>&
   */
  auto &at(size_t playerid)
  {
    _ISDBG_ bgdebug("Players::at", "_min=" + std::to_string(_min) + "|_max" + std::to_string(_max) + "|_players=" + std::to_string(_players.size()));

    return _players.at(playerid);
  }

  /**
   * @brief direct pointer to the memory array used internally by the Players
   *
   * @return const std::vector<Player<T>*>&
   */
  const auto &data() const
  {
    std::vector<Player<T> *> vecplayers;
    std::transform(_players.begin(), _players.end(), std::back_inserter(vecplayers), [](auto &kv) { return kv.second; });
    return vecplayers;
  }
  /**
   * @brief direct pointer to the memory array used internally by the Players
   *
   * @return std::vector<Player<T> *> &
   */
  auto &data()
  {
    std::vector<Player<T> *> vecplayers;
    std::transform(_players.begin(), _players.end(), std::back_inserter(vecplayers), [](auto &kv) { return kv.second; });
    return vecplayers;
  }

  //-----------------------SETTERS-----------------------------------------------------------

  //set maximum current players
  inline void set_max(size_t max) { _max = max; }
  //set minimum current players
  inline void set_min(size_t min) { _min = min; }

  /**
   * @brief [deep copy] [using till lifetime]
   * @param Player Player<T>*
   * @return true | false
   */
  inline bool insert(const Player<T> &P)
  {
    _ISDBG_ bgdebug("Players::insert", "_min=" + std::to_string(_min) + "|_max" + std::to_string(_max) + "|_players=" + std::to_string(_players.size()));

    if (size() < max())
    {
      _players.insert({P.id(), P.copy()});
      return true;
    }
    return false;
  }

  /**
   * @brief [move copy] [using till lifetime]
   * @param Player Player<T>*
   * @return true | false
   */
  inline bool insert(Player<T> &&P)
  {
    _ISDBG_ bgdebug("Players::insert", "_min=" + std::to_string(_min) + "|_max" + std::to_string(_max) + "|_players=" + std::to_string(_players.size()));

    if (size() < max())
    {
      _players.insert({P.id(), P.move()});
      return true;
    }
    return false;
  }

  //remove player
  inline void erase(size_t playerid)
  {
    _ISDBG_ bgdebug("Players::insert", "playerid=" + std::to_string(playerid) + "|_min=" + std::to_string(_min) + "|_max" + std::to_string(_max) + "|_players=" + std::to_string(_players.size()));

    delete _players.at(playerid);
    _players.erase(playerid);
  }

  //-------------------OPERATORS-----------------------------------------------------------------

  /**
   * @brief direct pointer to the memory array used internally by the Players
   *
   * @param playerid
   * @return const Player<T>*
   */
  const auto &operator[](size_t playerid) const { return at(playerid); }
  /**
   * @brief direct pointer to the memory array used internally by the Players
   *
   * @param playerid
   * @return Player<T>*
   */
  auto &operator[](size_t playerid) { return at(playerid); }

  //--------------------VIRTUAL--------------------------------

  virtual Players<T> *copy() const { return new Players<T>{*this}; }
  virtual Players<T> *move() { return new Players<T>{std::forward<Players<T>>(*this)}; }

protected:
  size_t _min{0};                                   //minimum number of players in game
  size_t _max{0};                                   //maximum number of players in game
  std::unordered_map<size_t, Player<T> *> _players; //list of players [id, object]
};

BG_END

#endif //BG_PLAYERS_H_