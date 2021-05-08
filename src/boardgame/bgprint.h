
#ifndef BG_PRINT_H_
#define BG_PRINT_H_

#include <iostream>
#include <iomanip>

#include "bgtypes.h"
#include "bgmove.h"
#include "bgplayers.h"
#include "bgboard.h"

using ::std::cout;
using ::std::endl;
using ::std::setw;
using namespace bg;

BG_BEGIN

//---------------------BOARD-------------------------

template <typename T>
void print(const T **bgrid, const int rows, const int cols);

template <typename T>
void print(const grid<T> bgrid);

template <typename T>
void print(const Board<T> *board);

template <typename T>
std::ostream &operator<<(std::ostream &out, const Board<T> &B)
{
  B.print();
  return out;
}

//---------------------MOVE----------------------------

//template <typename T>
//void print(const Move<T>* board);

//---------------------PLAYER-------------------------

// template <typename T>

//////////////////

template <typename T>
inline void print(const Board<T> &board)
{
  cout << endl
       << endl
       << endl;
  for (int i = 1; i < 8; i++)
  {
    if (i == 1)
      cout << setw(8) << i;
    else
      cout << setw(11) << i;
  }
  cout << endl
       << endl
       << endl;

  for (int r = 0; r < 6; r++)
  {
    for (int c = 0; c < 7; c++)
    {
      if (c == 0)
        cout << setw(2) << "|";
      /*auto PlayerC = board.at(r, c);
      char ccc = '.';
      if (PlayerC)
        ccc = PlayerC.get();
      cout << setw(6) << ccc << setw(5) << "|";*/
    }
    cout << endl;

    for (int b = 0; r < 5 && b < 2; b++)
    {
      for (int c = 0; r < 5 && c < 7; c++)
      {
        if (c == 0)
          cout << setw(2) << "|";
        cout << setw(6) << ' ' << setw(5) << "|";
      }
      cout << endl;
    }
  }
  for (int i = 0; i < 80; i++)
    cout << char(220);

  cout << endl
       << endl;
}

BG_END

#endif //BG_PRINT_H_
