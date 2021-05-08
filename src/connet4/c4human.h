
#ifndef C4_HUMAN_
#define C4_HUMAN_

#include <string>
#include <iostream>

#include "c4types.h"
#include "c4game.h"

namespace c4
{
  class C4Game;

  class C4Human : public C4Player
  {
  public:
    C4Human(std::string name, std::size_t diff_level = 4) : Player(name, diff_level) {}

    C4Human(std::string name, std::size_t diff_level = 4, C4Piece p = {'H'}) : Player(name, diff_level, p) {}

    C4Move *SuggestMove(const BGame &state) const override
    {
      const C4Game *c4state = dynamic_cast<const C4Game *>(&state);
      if (!c4state)
        return nullptr;

      std::size_t col;
      std::cout << "Please enter your move (1-7)";
      std::cin >> col;
      const int row = c4state->AvailableRow(col);

      c4state=nullptr;

      C4Move *mov = new C4Move(static_cast<bg::int_t>(row), static_cast<bg::int_t>(col - 1), *(_pieces.front()));

      return mov;
    }

    C4Human *copy() const override
    {
      return new C4Human(*this);
    }
    C4Human *move() override
    {
      return new C4Human(std::forward<C4Human>(*this));
    }
  };

} // namespace c4

#endif //C4_HUMAN_
