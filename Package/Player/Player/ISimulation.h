#pragma once

// Number of steps before bomb explodes
#define BOMB_TIMER 6

// Number of steps for explosion to disappear
#define EXPLOSION_COOLDOWN 2

// forward declaration
class IGame;

// possible moves a player can make
enum Move
{
    // keep current position (no move)
	moveNone,
    // move one cell up
	moveUp,
    // move one cell down
	moveDown,
    // move one cell left
	moveLeft,
    // move one cell right
	moveRight,

    // first valid move (for iterating through moves)
    moveFirst = moveNone,
    // last valid move (for iterating through moves with the < operator)
    moveLast = moveRight,
    // total number of moves (for iterating trough moves with the <= operator)
    moveCount,
};

/* used to accurately simulate the game evolution (step by step).
One game step consists of (in order):
    * Store move: called for each player to store their move. This is optional (empty move is assumed).
    * Begin turn: apply the evolution of the game level. Update timers and wall destruction; place new bombs.
    * End turn: apply the player moves towards their destinations. Resets the player moves.
A single ISimulation instance may be used to simulate the evolution of multiple IGame instances.
*/
class ISimulation
{
public:
    // virtual destructor
	virtual ~ISimulation()	{}

#pragma region "Game simulation"
    // Can be used to store a potential move for one player. Should be called before BeginTurn.
	virtual void StoreMove(int player, Move move, bool bomb) = 0;
    // Simulate the evolution of one game turn. Update timers; explode bombs and kill players; place new bombs.
	virtual void BeginTurn(IGame* game) = 0;
    // Move players to their final destination according to the moves stored. Resets player moves.
	virtual void EndTurn(IGame* game) = 0;
#pragma endregion

#pragma region "Utility functions"
    // Can simulate the explosion of a bomb at a specific coordinate (recursively explodes all bombs)
	virtual void ExplodeBomb(IGame* game, int x, int y) = 0;
    // Apply the move to a coordinate (no validation is made)
	virtual void ApplyMove(Move move, int& x, int& y) const = 0;
    // True if the move is valid for player (no obstacle, no explosion, does not exit the map)
	virtual bool CanMove(IGame* game, int player, Move move) const = 0;
#pragma endregion

};

#pragma region "Move operators ++ and -- (prefix and postfix)"
// prefix operator ++
inline Move operator++(Move& move) 
{
    move = (Move)((int)move + 1);
    return move;
}

// postfix operator ++
inline Move operator++(Move& move, int) 
{
    Move res = move;
    move = (Move)((int)move + 1); 
    return res;
}

// prefix operator --
inline Move operator--(Move& move) 
{
    move = (Move)((int)move - 1);
    return move;
}

// postfix operator --
inline Move operator--(Move& move, int) 
{
    Move res = move;
    move = (Move)((int)move - 1); 
    return res;
}
#pragma endregion



