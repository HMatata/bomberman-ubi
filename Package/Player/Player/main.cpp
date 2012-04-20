#include "Player.h"
#include <algorithm>
#include <cstring>
using namespace std;
// main.cpp is the only file you will be submitting for the contest
// HINT: before submitting this file, make sure to test compiling on Release 
//       and deactivating Debug mode from the Match Maker
// HINT: read the complete rules for submitting this file on the contest website
int turn = 0;
Move rev[moveCount];
int my[] = {0, -1, 1,  0, 0 };
int mx[] = {0,  0, 0, -1, 1 };

void PlayerInit(int playerId, IGame* game)
{
	
    //TODO: add initialization code here
    //HINT: this function is called only once (before the game starts)
    //HINT: the time taken by this function is taken out of the time allocated for your first move

	rev[moveUp] = moveDown;
	rev[moveDown] = moveUp;
	rev[moveLeft] = moveRight;
	rev[moveRight] = moveLeft;
	rev[moveNone] = moveNone;
}

//     fi
//    fxf
//     fi
int v[16][16][16];
int dfs (IGame *game, int playerId, int depth, int from)
{
	
	if (depth == 0  || !game->PlayerAlive(playerId) )
		return game->PlayerAlive(playerId);
	if (v[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)][depth] != -1)
		return v[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)][depth];
/*
	
	int c = 0;
	Move o = moveNone;
	for (Move i = moveUp; i != moveCount; ++i)
	{
		if (!simulation->CanMove(game, playerId, i))
			continue;

		if (i==rev[i])
			continue;
		
		++c;
		o = i;
	}

	if (c==1)
	{
		int dx = mx[o];
		int dy = my[o];
		int x = game->PlayerPosX(playerId);
		int y = game->PlayerPosY(playerId);
		x += dx;
		y += dy;
		for (;; x+=dx, y+=dy)
		{
			bool kill = false;
			Move i;
			bool ok = false;
			for (i = moveUp; i != moveCount; ++i)
			{
				if (i==rev[i] || i== o)
					continue;
				ok = !game->Wall(x+dx[i], y+dy[i]) < 0;

				
			}
			if (ok)
		}
	}
	*/

	int r = 0;
	for (Move i = moveFirst; i != moveCount; ++i)
	{
		
		if (simulation->CanMove(game, playerId, i))
		{
			IGame *ngame = game->Clone();
			simulation->StoreMove(playerId, i, 0);
			simulation->BeginTurn(ngame);
			simulation->EndTurn(ngame);
			int k = dfs(ngame, playerId, depth-1, i);
			r +=k;
			delete ngame;
		}
	}
	if (v[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)][depth] == -1)
		v[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)][depth] = r;
	return r;
}
void PlayerMove(int playerId, IGame* game, Move& move, bool& bomb)
{
	//simulation->BeginTurn(game);
	++turn;
	
	move = moveNone;
	int m = -1000;
	int gata = 0;
	for (int k = 1; k >= 0 && !gata; --k)
	for (Move i = moveUp; i <= moveCount; ++i)
	{
		if (k == 0 && m > 0)
		{
			gata = 1;
			break;
		}
		if (i == moveCount)
			i = moveNone;
		if (simulation->CanMove(game, playerId, i))
		{
			IGame * ngame = game->Clone();
			simulation->StoreMove(playerId, i, k);
			simulation->BeginTurn(ngame);
			simulation->EndTurn(ngame);
			memset(v, -1, sizeof(v));
			if (ngame->PlayerAlive(playerId))
			{
				int o;
				o = dfs(ngame, playerId, 7, i);
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
