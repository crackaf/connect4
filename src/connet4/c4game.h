#ifndef C4_STATE_
#define C4_STATE_

#include <vector>

#include "c4types.h"

namespace c4
{

  class C4Game : public BGame
  {
  public:
    inline static const C4Piece kEmpty{'.'};
    static const int kRows = 6;
    static const int kCols = 7;
    int available_row[kCols];

    C4Game() noexcept : BGame{0, C4Players{0, 2}, C4Board{kRows, kCols}} {}

    size_t NextPlayer(size_t playerid) const override
    {
      return (playerid + 1) % players()->size();
    }

    const std::vector<C4Move *> GetPossibleMoves(size_t playerid) const override
    {
      std::vector<C4Move *> moves;
      for (auto c = 0; c < kCols; ++c)
        if (*(at(kRows - 1, c)) == kEmpty)
          moves.push_back(new C4Move(available_row[c], c, *(players()->at(playerid)->pieces().at(0))));

      return moves;
    }
    bool IsWinningState(size_t playerid) const override { return false; }
    bool IsValid(const C4Move &mov, size_t playerid) const override
    {
      return available_row[mov.col()] >= 0 ? true : false;
    }
    bool IsNoMoreMoves() const override { return false; }
    bool Apply(const C4Move &mov) override
    {
      board()->insert(size_t(mov.row()), size_t(mov.col()), *(mov.piece()));
      available_row[mov.col()]++;
      return true;
    }
    C4Game *copy() const override { return new C4Game{*this}; }
    C4Game *move() override { return new C4Game{std::forward<C4Game>(*this)}; }
    bool IsWinning(const C4Move &mov, size_t playerid) const override
    {
      const C4Player *cp = at(playerid);
      bool isWin = false;

      int r = mov.row();
      int c = mov.col();
      if (!(cp->IsPlayerPiece(*(mov.piece()))))
        return false;

      //check vertically, only need to check down
      if (!isWin)
      {
        int down = 0;
        for (int row = r + 1; row < 6 && cp->IsPlayerPiece(*(board()->at(row, c))); ++row) //moving down
          ++down;
        isWin = down >= 3 ? true : false;
      }

      //check horizontaly
      if (!isWin)
      {
        int right = 0, left = 0;
        for (int col = c - 1; col >= 0 && cp->IsPlayerPiece(*(board()->at(r, col))); --col) //moving left
          ++left;
        for (int col = c + 1; col < 7 && cp->IsPlayerPiece(*(board()->at(r, col))); ++col) //moving right
          ++right;
        isWin = (left + right) >= 3 ? true : false;
      }

      //check forward diagnal e.g //
      if (!isWin)
      {
        int upright = 0, downleft = 0;
        for (int col = c - 1, row = r + 1; col >= 0 && row < 6 && cp->IsPlayerPiece(*(board()->at(row, col))); --col, ++row) //moving downleft
          ++downleft;
        for (int col = c + 1, row = r - 1; col < 7 && row >= 0 && cp->IsPlayerPiece(*(board()->at(row, col))); ++col, --row) //moving upright
          ++upright;
        isWin = (downleft + upright) >= 3 ? true : false;
      }

      /*check backward diagnal e.g \\*/

      if (!isWin)
      {
        int upleft = 0, downright = 0;
        for (int col = c + 1, row = r + 1; col < 7 && row < 6 && cp->IsPlayerPiece(*(board()->at(row, col))); ++col, ++row) //moving downright
          ++downright;
        for (int col = c - 1, row = r - 1; col >= 0 && row >= 0 && cp->IsPlayerPiece(*(board()->at(row, col))); --col, --row) //moving upleft
          ++upleft;
        isWin = (downright + upleft) >= 3 ? true : false;
      }

      return isWin;
    }
    int AvailableRow(const std::size_t col) const
    {
      return available_row[col];
    }
  };
} // namespace c4

#endif //C4_STATE_
