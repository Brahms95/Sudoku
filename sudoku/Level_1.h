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

class Level_2:public Board
{
public:
	Level_2();
	~Level_2();

	bool load();
	SolveResult solve();
	const bool isSolveable() const;
	Level_2* print(bool flag) const;
 	bool veifity(int a, int d) const;
	Level_2* _get()const {return board;};
    bool verifity_table(char* table) const;
	//Level_2*  adding_velue(int a, int b, int c,Board **board_chrcking) const;

	 inline const unsigned int translate(const column &c, const row &r, const unsigned int &width) const;

private:
	const unsigned int SIZE = 9;
	const unsigned int SQUARE_SIZE = 3;
	 std::vector<Tile> _tiles  ;
	Level_2* board;
 	SolveResult backtrack(tile_index index, SolveResult &result);

};
