#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "status.h"
#include "../registration/registration_user.h"


class Board
{
	public:
		Board(){};
		virtual ~Board(){};
		virtual bool load() = 0;
		virtual Board* print(bool flag) const =0;
		virtual bool verifity(int a, int d) const= 0;
		virtual  bool verifity_table(char* table) const=0;
		virtual bool adding_velue(int a, int b, int c) = 0;

};

Board * output_table(User* user);

bool adding_velue_suboku(char* index_table, Board* pSudoku);
bool verifity_suboku(char* index_table, Board* pSudoku);
bool result(char* table_sudoku, Board* pSudoku, User* user );
void free_(User* puser, Board* psudoku);