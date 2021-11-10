#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "status.h"
#include "../registration/registration_user.h"

typedef unsigned int row;
typedef unsigned int column;
typedef unsigned int square;
typedef unsigned int tile_index;

class Board
{
public:

	virtual bool load() = 0;
	virtual Board* print(bool flag) const =0;
 	virtual bool veifity(int a, int d) const= 0;
    virtual  bool verifity_table(char* table) const=0;
//	virtual Board* adding_velue(int a, int b, int c,Board **board_chrcking) const = 0;

};

Board * output_table(void* user);

void adding_velue_suboku(char* index_table, void* pSudoku);
bool verifity_suboku(char* index_table, void* pSudoku);
bool result(char* table_sudoku, void* pSudoku, void* user );
void free_(void* puser, void* psudoku);