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

#include "bgtypes.h"
#include "bgplayer.h"

BG_BEGIN

/**
 * @brief General Players class for storing list of Player
 * 
 * @tparam T 
 */
template <typename T>
class Players
{
public:
  //-------------------CONSTRUCTORS------------------

  /**
   * @brief Construct a new Players object
   */
  Players();

  /**
   * @brief Construct a new Players object
   * 
   * @param min minimum number of players
   * @param max maximum number of players
   */
  Players(const std::size_t min, const std::size_t max);

  /**
   * @brief [virtual] Destroy the Players object
   */
  virtual ~Players();

  //-----------------------GETTERS-------------------------

  //get maximum number of players
  inline std::size_t max() const;
  //get minimum number of players
  inline std::size_t min() const;
  //get size of Player list
  inline std::size_t size() const;

  /**
   * @brief get winner index
   * 
   * @return int | -1 => no winner yet
   */
  inline int winner_index();

  /**
   * @brief direct pointer to the memory array used internally by the Players
   * 
   * @param index 
   * @return const Player<T>* 
   */
  const Player<T> *at(const std::size_t index) const;
  /**
   * @brief direct pointer to the memory array used internally by the Players
   * 
   * @param index 
   * @return Player<T>* 
   */
  Player<T> *at(const std::size_t index);

  /**
   * @brief direct pointer to the memory array used internally by the Players
   * 
   * @return const std::vector<Player<T> *> 
   */
  const std::vector<Player<T> *> &data() const;
  /**
   * @brief direct pointer to the memory array used internally by the Players
   * 
   * @return std::vector<Player<T> *> 
   */
  std::vector<Player<T> *> &data();

  /**
   * @brief direct pointer to the winner Player
   * 
   * @param index 
   * @return Player<T>* 
   */
  const Player<T> *winner() const;
  /**
   * @brief direct pointer to the winner Player
   * 
   * @param index 
   * @return Player<T>* 
   */
  Player<T> *winner();

  //-----------------------SETTERS-------------------------

  //set maximum current players
  inline void set_max(const std::size_t max);
  //set minimum current players
  inline void set_min(const std::size_t min);
  //player index of the winner
  inline bool set_winner(const int winner);
  //add player using deep copy
  inline bool insert(const Player<T> &);
  //remove player
  inline bool erase(const std::size_t index);

  //-------------------OPERATORS-------------------------

  /**
   * @brief direct pointer to the memory array used internally by the Players
   * 
   * @param index 
   * @return const Player<T>* 
   */
  const Player<T> *operator()(const std::size_t index) const;
  /**
   * @brief direct pointer to the memory array used internally by the Players
   * 
   * @param index 
   * @return Player<T>* 
   */
  Player<T> *operator()(const std::size_t index);

protected:
  std::size_t _min;                  //minimum number of players in game
  std::size_t _max;                  //maximum number of players in game
  int _winner;                       //winner index
  std::vector<Player<T> *> _players; //list of players

  //-------------------FUNCTIONS-------------------------

  /**
   * @brief return the direct pointer to the list value
   * 
   * @param index 
   * @return Player<T>* 
   */
  inline Player<T> *_AtIndex(const std::size_t index);
};

//-------------------------------------------------------------------------------------------------------
//---------------------------------------IMPLEMENTATION--------------------------------------------------
//-------------------------------------------------------------------------------------------------------

template <typename T>
inline Players<T>::Players() : _min(0), _max(0), _winner(-1) {}

template <typename T>
inline Players<T>::Players(const std::size_t min, const std::size_t max) : _min(min), _max(min), _winner(-1) {}

template <typename T>
inline Players<T>::~Players()
{
  _min = _max = 0;
  _winner = -1;

  for (std::size_t i = 0; i < size(); ++i)
    delete _players.at(i);

  _players.clear();
  _players.shrink_to_fit();
}

template <typename T>
inline std::size_t Players<T>::max() const
{
  return _max;
}

template <typename T>
inline std::size_t Players<T>::min() const
{
  return _min;
}

template <typename T>
inline std::size_t Players<T>::size() const
{
  return _players.size();
}

template <typename T>
inline int Players<T>::winner_index()
{
  return _winner;
}

template <typename T>
inline const Player<T> *Players<T>::at(const std::size_t index) const
{
  return _AtIndex(index);
}

template <typename T>
inline Player<T> *Players<T>::at(const std::size_t index)
{
  return _AtIndex(index);
}

template <typename T>
inline const std::vector<Player<T> *> &Players<T>::data() const
{
  return _players;
}

template <typename T>
inline std::vector<Player<T> *> &Players<T>::data()
{
  return _players;
}

template <typename T>
inline const Player<T> *Players<T>::winner() const
{
  return _AtIndex(_winner);
}

template <typename T>
inline Player<T> *Players<T>::winner()
{
  return _AtIndex(_winner);
}

template <typename T>
inline void Players<T>::set_max(const std::size_t max)
{
  if (size() > max)
    _players.resize(max);
  _max = max;
}

template <typename T>
inline void Players<T>::set_min(const std::size_t min)
{
  _min = min;
}

template <typename T>
inline bool Players<T>::set_winner(const int winner_index)
{
  if (winner_index < size())
  {
    _winner = winner_index;
    return true;
  }
  return false;
}

template <typename T>
inline bool Players<T>::insert(const Player<T> &P)
{
  if (size() < max())
  {
    this->_players.push_back(new Player<T>(P));
    return true;
  }
  return false;
}

template <typename T>
inline bool Players<T>::erase(const std::size_t index)
{
  if (index < size())
  {
    delete this->_player.at(index);
    _players.erase(_players.begin() + index);
  }
  return false;
}

template <typename T>
inline const Player<T> *Players<T>::operator()(const std::size_t index) const
{
  return _AtIndex(index);
}

template <typename T>
inline Player<T> *Players<T>::operator()(const std::size_t index)
{
  return _AtIndex(index);
}

template<typename T>
inline Player<T>* Players<T>::_AtIndex(const std::size_t index)
{
    return index >= 0 && index < size() ? _players.at(index) : nullptr;
}

BG_END

#endif //BG_PLAYERS_H_