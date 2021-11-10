#include "Board.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <regex>
#include "Level_0.h"
#include "Level_1.h"



Board * output_table(void* user ){
	User* user_level = static_cast<User*>(user);
	int level = user_level->get_level();
 
    switch (level)
    {
    case 0:{

        Level_1 level_1;
        Board *board = new Level_1();
     	if (board->load()){ board->print(true); }
  
//   A* ap = &Level_1;
//   void * vp = dynamic_cast<void *>(ap);
//  B * vp1 = static_cast<B *>(vp);


//         Board *board =new Board();
// 	if (board->load()){
	
// 		board->print(true);
		
//	}return board;	
       return board;	
    }
     case 1:{

        Level_2 level_2;
        Board *board = new Level_2();
     	if (board->load()){ board->print(true); }	
        return board;	
    }

    default:
        printf ("Что-то пошло не так\n");
        return nullptr;
    }
}


bool verifity_suboku(char* index_table, void* pSudoku){
	Board* board = static_cast<Board*>(pSudoku);
   
	return board->veifity(index_table[1]-'0',index_table[0]-'0');

}

void adding_velue_suboku(char* index_table, void* pSudoku){
// 	Board* board = static_cast<Board*>(pSudoku);
//        Level_1 level_1;
//         Board *board_chrcking = new Level_1();
	
//  board->adding_velue(index_table[1]-'0',index_table[0]-'0', index_table[3]-'0', &board_chrcking );
//     if (board_chrcking){
//         board_chrcking->print(true);
         
//         pSudoku =&board_chrcking;
//         Board* board1 = static_cast<Board*>(pSudoku);
//         board1->print(true);
//         delete board ;
//     }
}
bool result(char* table_sudoku, void* pSudoku, void* user ){
	User* user_level = static_cast<User*>(user);
	Board* board = static_cast<Board*>(pSudoku);
    if (board->verifity_table(table_sudoku)){
        board->print(false);
        user_level->checking_level();
        return true;
    }
return false;
 }
//  void verifity_table(void* pSudoku){
// 	 Board* board = static_cast<Board*>(pSudoku);

//  }
void free_(void* puser, void* psudoku){

	User* user_level = static_cast<User*>(puser);
	Board* board = static_cast<Board*>(psudoku);
    if (user_level !=NULL && board != NULL){
        delete board;
        delete user_level;
    }
}