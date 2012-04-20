#pragma once

// forward declaration of stream classes
class IReadStream;
class IWriteStream;

// Stores information about a game state.
// You can freely modify the data (which is returned by references) to simulate various scenarios.
class IGame
{
public:
    // virtual destructor
	virtual			~IGame()	{}

    // create a duplicate of this game state; delete it after use to free memory
    virtual IGame*  Clone() = 0;

#pragma region "Level information"
    // number of lines (read only)
	virtual int		SizeX() const = 0; 
    // number of columns (read only)
	virtual int		SizeY() const = 0; 
    // wall info (read/write): negative = indestructible, 0 = empty, positive = life of the wall
	virtual int&	Wall(int x, int y) const = 0;
    // bomb info (read/write): zero = none, positive = countdown timer, negative = explosion counter
	virtual int&	Bomb(int x, int y) const = 0;
#pragma endregion

#pragma region "Player information"
    // total number of players (read only)
	virtual int		PlayerCount() const = 0; 
    // true if player is alive (read/write)
	virtual bool&	PlayerAlive(int n) const = 0;
    // x coordinate of a player (read/write)
	virtual int&	PlayerPosX(int n) const = 0;
    // y Coordinate of a player (read/write)
	virtual int&	PlayerPosY(int n) const = 0;
#pragma endregion

#pragma region "Game serialization - for advanced use only (ex. to dump/load game state)"
    // Load the initial state of a game from a stream
    virtual bool	Load(IReadStream* stream) = 0;
    // Save the initial state of a game to a stream
    virtual bool	Save(IWriteStream* stream) = 0;
    // Read current state of a game from a stream
    virtual bool	Read(IReadStream* stream) = 0;
    // Write current state of a game to a stream
    virtual bool	Write(IWriteStream* stream) = 0;
#pragma endregion
};

