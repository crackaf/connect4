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

#include "bgtypes.h"
#include "bgmove.h"
#include "bgstate.h"

BG_BEGIN

template <typename T>
class State;

/**
 * @brief Abstract Player class for boardgame
 * 
 * @tparam T 
 */
template <typename T>
class Player
{
public:
  //-------------------CONSTRUCTORS------------------

  /**
   * @brief Construct a new Player object
   */
  Player();

  /**
   * @brief Construct a new Player object
   * 
   * @param name 
   * @param id 
   * @param diff_level 
   */
  Player(const std::string name, const std::size_t id, const std::size_t diff_level);

  /**
   * @brief [virtual] Destroy the Player object
   */
  virtual ~Player();

  //-----------------------GETTERS-------------------------

  //get name
  inline std::string name() const;
  //get id
  inline std::size_t id() const;
  //get difficulty level
  inline std::size_t diff_level() const;
  //get history of suggested moves
  inline const std::vector<Move<T> *> &suggest_hist() const;

  //-----------------------SETTERS-------------------------

  //set name
  inline void set_name(const std::string &name);
  //set id
  inline void set_id(const std::size_t id);
  //set difficulty level
  inline void set_diff_level(const std::size_t diff_level);

  //------------------------FUNCTIONS-----------------------------

  /**
   * @brief suggest move while looking at the current game state
   * 
   * @param state 
   * @return const Move<T>*
   */
  const Move<T> *SuggestMove(const State<T> *state);

protected:
  std::string _name;                    //player name
  std::size_t _id;                      //can be a charachter
  std::size_t _diff_level;              //difficulty level
  std::vector<Move<T> *> _suggest_hist; //suggested moves history

  //-------------------------FUNCTIONS-----------------------

  /**
   * @brief adds Move<T>* to the _suggest_hist
   */
  void _AddHist(const Move<T> *);

  /**
   * @brief [pure virtual] suggest move while looking at the current game state
   * 
   * @param state 
   * @return Move<T>* 
   */
  virtual Move<T> *_SuggestMove(const State<T> *state) = 0;
};

//-------------------------------------------------------------------------------------------------------
//---------------------------------------IMPLEMENTATION--------------------------------------------------
//-------------------------------------------------------------------------------------------------------

template <typename T>
inline Player<T>::Player() {}

template <typename T>
inline Player<T>::Player(std::string name, std::size_t id, std::size_t diff_level) : _name(name), _id(id), _diff_level(diff_level) {}

template <typename T>
inline Player<T>::~Player()
{
  _name.clear();
  _name.shrink_to_fit();

  _id = _diff_level = 0;

  _suggest_hist.clear();
  _suggest_hist.shrink_to_fit();
}

template <typename T>
inline std::string Player<T>::name() const
{
  return _name;
}

template <typename T>
inline std::size_t Player<T>::id() const
{
  return _id;
}

template <typename T>
inline std::size_t Player<T>::diff_level() const
{
  return _diff_level;
}

template <typename T>
inline const std::vector<Move<T> *> &Player<T>::suggest_hist() const
{
  return _suggest_hist;
}

template <typename T>
inline void Player<T>::set_name(const std::string &name)
{
  _name = name;
}

template <typename T>
inline void Player<T>::set_id(const std::size_t id)
{
  _id = id;
}

template <typename T>
inline void Player<T>::set_diff_level(const std::size_t diff_level)
{
  _diff_level = diff_level;
}

template <typename T>
const Move<T> *Player<T>::SuggestMove(const State<T> *state)
{
  Move<T> *move = _SuggestMove(state);
  _AddHist(move);
  return move;
}

template <typename T>
void Player<T>::_AddHist(const Move<T> *mov)
{
  _suggest_hist.push_back(new Move<T>(*mov));
}

BG_END

#endif //BG_PLAYER_H_