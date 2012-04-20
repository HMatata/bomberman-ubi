#include "Player.h"

// main.cpp is the only file you will be submitting for the contest
// HINT: before submitting this file, make sure to test compiling on Release 
//       and deactivating Debug mode from the Match Maker
// HINT: read the complete rules for submitting this file on the contest website
void check_move (int depth_available , ISimulation &sim)
{
}
void PlayerInit(int playerId, IGame* game)
{
	
    //TODO: add initialization code here
    //HINT: this function is called only once (before the game starts)
    //HINT: the time taken by this function is taken out of the time allocated for your first move
}

void PlayerMove(int playerId, IGame* game, Move& move, bool& bomb)
{
	const int dx[] = {0, 0, -1, 1};
	const int dy[] = {1, -1, 0, 0};
	for (i = 1; i <= n; ++i)
	{
	}
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
