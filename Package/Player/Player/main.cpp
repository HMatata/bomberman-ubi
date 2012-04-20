#include "Player.h"
#include <algorithm>
using namespace std;
// main.cpp is the only file you will be submitting for the contest
// HINT: before submitting this file, make sure to test compiling on Release 
//       and deactivating Debug mode from the Match Maker
// HINT: read the complete rules for submitting this file on the contest website
int turn = 0;

void PlayerInit(int playerId, IGame* game)
{
	
    //TODO: add initialization code here
    //HINT: this function is called only once (before the game starts)
    //HINT: the time taken by this function is taken out of the time allocated for your first move
}
int dfs (IGame *game, int playerId, int depth)
{
	
	
	if (depth == 0  || !game->PlayerAlive(playerId)|| GetTimeLeft() <= 5)
		return game->PlayerAlive(playerId);
	
	int r = -100;
	for (Move i = moveFirst; i != moveCount; ++i)
	{
		
		if (simulation->CanMove(game, playerId, i))
		{
			IGame *ngame = game->Clone();
			simulation->StoreMove(playerId, i, 0);
			simulation->BeginTurn(ngame);
			simulation->EndTurn(ngame);
			int k;
			if(k = dfs(ngame, playerId, depth-1))
				r = max(k, r);
			delete ngame;
		}
	}
	return r;
}
void PlayerMove(int playerId, IGame* game, Move& move, bool& bomb)
{
	//simulation->BeginTurn(game);
	++turn;
	move = moveNone;
	int m = -1000;
	for (int k = 1; k >= 0; --k)
	for (Move i = moveUp; i <= moveCount; ++i)
	{
		if (i == moveCount)
			i = moveNone;
		if (simulation->CanMove(game, playerId, i))
		{
			IGame * ngame = game->Clone();
			simulation->StoreMove(playerId, i, k);
			simulation->BeginTurn(ngame);
			simulation->EndTurn(ngame);
			if (ngame->PlayerAlive(playerId))
			{
				int o;
				o = dfs(ngame, playerId, 7);
				if (o > m)
				{
					m = o;
					move = i;
					bomb = k;
				}
			}
			delete ngame;
			//delete ngame;
		}
		if (i == moveNone)
			break;


	}
	if (m == -1000)
	printf("I can't survive\n");
    //TODO: add AI code here
    //TODO: assign values to move and bomb (which represent your move for this step)
    //HINT: this function is called once for every game step
    //HINT: you can use the simulation pointer to simulate game states
    //HINT: you can modify the contents of the game pointer
    //HINT: you can clone the game state to evolve different scenarios
    //HINT: this function must return before GetTimeLeft() returns 0
    //HINT: the game will evolve 1 step before your character starts moving, so it's useful to
    //      call simulation->BeginTurn(game) to get the state of the game at the time your player 
    //      will begin to move or place the bomb.
    
}
