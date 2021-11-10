#pragma once

struct SolveResult
{
	SolveResult(): backtracks(0), solved(false){};

	unsigned int backtracks;
	bool solved;
};
enum class TileValue
{
	Empty = 0,
	One = 1,
	Two = 2,
	Three = 3,
	Four = 4,
	Five = 5,
	Six = 6,
	Seven = 7,
	Eight = 8,
	Nine = 9
};

enum class TileStatus
{
	Empty,
	Solved,
	Processing
};

struct Tile
{
	TileValue value;
	TileStatus status;
};

