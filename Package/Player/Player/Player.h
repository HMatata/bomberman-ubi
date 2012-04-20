#pragma once

#include "IGame.h"
#include "ISimulation.h"

// to be implemented by the player (contestant)
void PlayerInit(int playerId, IGame* game);
void PlayerMove(int playerId, IGame* game, Move& move, bool& bomb);

// useful for simulating the game state (do not delete this pointer)
// HINT: this is the actual game simulator - it's the safest way to anticipate future game states
extern ISimulation* simulation;

// returns the allowed time (in milliseconds) left for computations this move
// HINT: do not let this timer reach zero, especially when doing CPU heavy operations for your AI
unsigned long GetTimeLeft();

