#ifndef GAMEPLAYERS_H_
#define GAMEPLAYERS_H_

#include <vector>

#include "gameplayer.h"

namespace boardgame
{
  template <typename T>
  class Players
  {
  public:
    Players();
    Players(const unsigned int min, const unsigned int max);

    //deep copy
    Players(const Players &P);
    //deep copy
    Players(Players *&P);

    //destructor
    ~Players();

    //getters
    inline unsigned int max() const;
    inline unsigned int min() const;
    inline unsigned int size() const;
    inline unsigned int winner();
    const Player<T> *player(const unsigned int index) const;
    const std::vector<Player<T> *> players() const;
    const Player<T> *winner() const;

    //setters

    //set maximum current players
    inline bool set_max(const unsigned int max);
    //set minimum current players
    inline bool set_min(const unsigned int min);
    //player index of the winner
    inline bool set_winner(const int winner);
    //add player using deep copy
    inline bool add_player(const Player<T> &P);
    //add player using deep copy
    inline bool add_player(Player<T> *&P);
    //remove player
    inline bool del_player(const unsigned int index);

    //operator overloading
    inline const Player<T> *operator()(const unsigned int index) const;

  protected:
    unsigned int _min; //minimum number of players in game
    unsigned int _max; //maximum number of players in game
    int _winner;       //winner index

    std::vector<Player<T> *> _players; //list of players
  };

  template <typename T>
  inline Players<T>::Players() : _min(0), _max(0), _winner(-1) {}

  template <typename T>
  inline Players<T>::Players(const unsigned int min, const unsigned int max) : _min(min), _max(min), _winner(-1) {}

  template <typename T>
  Players<T>::Players(const Players &P)
  {
    this->_min = P._min;
    this->_max = P._max;
    this->_winner = P._winner;

    for (auto p : P._players)
      this->_players.push_back(new Player(p));
  }

  template <typename T>
  Players<T>::Players(Players *&P)
  {
    this->_min = P->_min;
    this->_max = P->_max;
    this->_winner = P->_winner;

    for (auto p : P->_players)
      this->_players.push_back(new Player(p));
  }

  template <typename T>
  inline Players<T>::~Players()
  {
    _min = _max = 0;
    _winner = -1

               for (auto i = 0; i < size(); ++i) delete _players.at(i);
    _players.clear();
    _players.shrink_to_fit();
  }

  template <typename T>
  inline unsigned int Players<T>::max() const
  {
    return _max;
  }

  template <typename T>
  inline unsigned int Players<T>::min() const
  {
    return _min;
  }

  template <typename T>
  inline unsigned int Players<T>::size() const
  {
    return _players.size();
  }

  template <typename T>
  inline unsigned int Players<T>::winner()
  {
    return _winner;
  }

  template <typename T>
  inline const Player<T> *Players<T>::player(const unsigned int index) const
  {
    if (index >= 0)
      return _players.at(index);
    return nullptr;
  }

  template <typename T>
  inline const std::vector<Player<T> *> Players<T>::players() const
  {
    return _players;
  }

  template <typename T>
  inline const Player<T> *Players<T>::winner() const
  {
    return player(_winner);
  }

  template <typename T>
  inline bool Players<T>::set_max(const unsigned int max)
  {
    _max = max;
    return true;
  }

  template <typename T>
  inline bool Players<T>::set_min(const unsigned int min)
  {
    _min = min;
    return true;
  }

  template <typename T>
  inline bool Players<T>::set_winner(const int winner_index)
  {
    _winner = winner_index;
    return true;
  }

  template <typename T>
  inline bool Players<T>::add_player(Player<T> *&P)
  {
    if (size() < max())
    {
      _players.push_back(new Player<T>(P));
      return true;
    }
    return false;
  }

  template <typename T>
  inline bool Players<T>::del_player(const unsigned int index)
  {
    if (index < size())
    {
      delete _player.at(index);
      _players.erase(_players.begin() + index);
    }
    return false;
  }

  template <typename T>
  inline bool Players<T>::add_player(const Player<T> &P)
  {
    if (size() < max())
    {
      _players.push_back(new Player<T>(P));
      return true;
    }
    return false;
  }

  template <typename T>
  inline const Player<T> *Players<T>::operator()(const unsigned int index) const
  {
    return player(index);
  }

} // namespace boardgame

#endif //GAMEPLAYERS_H_