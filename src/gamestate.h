#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "gameplayers.h"
#include "gameboard.h"

namespace boardgame
{
  template <typename T>
  class State
  {
  public:
    State();
    State(const State &);

    //getters

    //returns index of the turning player
    inline unsigned int turning_player() const;
    //returns index of the next turning player
    inline unsigned int next_player() const;
    //returns index of the winning player
    inline int winner() const;
    //return the player at index
    inline const Player<T> *player(unsigned int index);

    //setters

    //operator overloading

  protected:
    Players<T> _players;
    Board<T> _board;
    unsigned int _turning_player; //index of player making a move
  };

} // namespace boardgame

#endif //GAMESTATE_H_