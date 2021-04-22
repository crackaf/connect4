#ifndef GAMEPLAYER_H_
#define GAMEPLAYER_H_

#include <string>
#include <vector>

#include "gamemove.h"
#include "gamestate.h"

namespace boardgame
{
  template <typename T>
  class Player
  {
    /**
     * @brief Abstract class for the player
     * 
     */
  public:
    //Default Constructor
    Player();
    Player(std::string name, unsigned int id, unsigned int diff_level);

    //copy constructors
    Player(const Player &P);
    Player(Player *&P);

    //getters
    inline std::string name() const;
    inline unsigned int id() const;
    inline unsigned int diff_level() const;
    inline const std::vector<Move<T> *> suggest_hist() const;

    //setters
    inline bool set_name(std::string name);
    inline bool set_id(unsigned int id);
    inline bool set_diff_level(unsigned int diff_level);

    //suggest move while looking at the game state
    //return type is Move<T>* and Parameter is State<T>*
    virtual Move<T> *suggest_move(State<T> *state) = 0; //pure virtual to be implemented in derived class

  protected:
    std::string _name;        //player name
    unsigned int _id;         //can be a charachter
    unsigned int _diff_level; //difficulty level

    std::vector<Move<T> *> _suggest_hist; //suggested moves history
  };

  template <typename T>
  inline Player<T>::Player()
  {
  }

  template <typename T>
  inline Player<T>::Player(std::string name, unsigned int id, unsigned int diff_level) : _name(name), _id(id), _diff_level(diff_level) {}

  template <typename T>
  Player<T>::Player(const Player &P)
  {
    this->_name = P._name;
    this->_id = P._id;
    this->_diff_level = P._diff_level;

    for (auto suggest : P._suggest_hist)
      this->_suggest_hist.push_back(new Move(suggest));
  }

  template <typename T>
  Player<T>::Player(Player *&P)
  {
    this->_name = P->_name;
    this->_id = P->_id;
    this->_diff_level = P->_diff_level;

    for (auto suggest : P->_suggest_hist)
      this->_suggest_hist.push_back(new Move(suggest));
  }

  template <typename T>
  inline std::string Player<T>::name() const
  {
    return _name;
  }

  template <typename T>
  inline unsigned int Player<T>::id() const
  {
    return _id;
  }

  template <typename T>
  inline unsigned int Player<T>::diff_level() const
  {
    return _diff_level;
  }

  template <typename T>
  inline const std::vector<Move<T> *> Player<T>::suggest_hist() const
  {
    return _suggest_hist;
  }

  template <typename T>
  inline bool Player<T>::set_name(std::string name)
  {
    _name = name;
    return true;
  }

  template <typename T>
  inline bool Player<T>::set_id(unsigned int id)
  {
    _id = id;
    return true;
  }

  template <typename T>
  inline bool Player<T>::set_diff_level(unsigned int diff_level)
  {
    _diff_level = diff_level;
    return true;
  }

} // namespace boardgame

#endif //GAMEPLAYER_H_