#include "Board.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <regex>
#include "Level_0.h"
#include "Level_1.h"

Board * output_table(User* user ){
//	User* user_level = static_cast<User*>(user);
	int level = user->get_level();
 
    switch (level)
    {
    case 0:{

        Level_0 level_0;
        Board *board = new Level_0();
     	if (board->load()){ board->print(true); }
        return board;	
    }

     case 1:{
        Level_1 level_1;
        Board *board = new Level_1();
     	if (board->load()){ board->print(true); }	
        return board;	
    }

    default:
        printf ("Что-то пошло не так\n");
        return nullptr;
    }
}


bool verifity_suboku(char* index_table, Board* pSudoku){
	//Board* board = static_cast<Board*>(pSudoku);
   
	return pSudoku->verifity(index_table[1]-'0',index_table[0]-'0');

}

bool adding_velue_suboku(char* index_table, Board* pSudoku){
	//Board* board = static_cast<Board*>(pSudoku);

    if(pSudoku->adding_velue(index_table[1]-'0',index_table[0]-'0', index_table[3]-'0'))
        pSudoku->print(true);

    return true;    
}

bool result(char* table_sudoku, Board* pSudoku, User* user ){
	//User* user_level = static_cast<User*>(user);
//	Board* board = static_cast<Board*>(pSudoku);
    if (pSudoku->verifity_table(table_sudoku)){
        pSudoku->print(false);
        user->checking_level();
        return true;
    }
    return false;
}

void free_(User* puser, Board* psudoku){
//	User* user_level = static_cast<User*>(puser);
//	Board* board = static_cast<Board*>(psudoku);
    if (puser !=NULL && psudoku != NULL){
        delete   psudoku;
        delete puser;
    }
}