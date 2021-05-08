
#include <iostream>
#include "c4human.h"
#include "c4game.h"
#include "../boardgame/bgmove.h"
#include "../boardgame/bgprint.h"
using namespace std;
using namespace bg;
using namespace c4;


int main()
{
	C4Game* State = new C4Game();

	State->insert(C4Human{ "human", 4, C4Piece{ 'H' } });
	State->insert(C4Human{ "human4", 4, C4Piece{ 'K' } });

	while(State->MakeMove())
	//print(State->board());

	return 0;
}
