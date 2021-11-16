#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "status.h"
#include "../registration/registration_user.h"
#include "Board.h"

typedef unsigned int row;
typedef unsigned int column;
typedef unsigned int square;
typedef unsigned int tile_index;

class Level_1 : public Board
{
public:
	Level_1();
	~Level_1();
	bool load();
	SolveResult solve();
	const bool isSolveable() const;
	Level_1* print(bool flag) const;
 	bool verifity(int a, int d) const;
	Level_1* _get()const {return board;};
    bool verifity_table(char* table) const;
	bool  adding_velue(int a, int b, int c) ;

	inline const unsigned int translate(const column &c, const row &r, const unsigned int &width) const;

private:
	const unsigned int SIZE = 9;
	const unsigned int SQUARE_SIZE = 3;
	std::vector<Tile> _tiles  ;
	Level_1* board;
 	SolveResult backtrack(tile_index index, SolveResult &result);

};
