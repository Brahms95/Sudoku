#include "Interface.h"
#include "registration/registration_user.h"
#include "sudoku/Board.h"

int  edo_registration (std::string user_name,int level){ return registration( user_name, level); }

User * edo_input (std::string user_name){ return input( user_name); }

Board* edo_output(User* user){ return output_table(user); }

bool edo_verifity_suboku(char* index_table, Board* pSudoku){ return verifity_suboku(index_table, pSudoku );};
bool edo_adding_velue_suboku(char* index_table, Board* pSudoku){ return adding_velue_suboku(index_table, pSudoku );};

bool edo_result(char* table_sudoku,  Board* pSudoku, User* user) { return result( table_sudoku, pSudoku, user );}

void edo_free_(User* user, Board* sudoku){return free_(user, sudoku );}

/** Глобальный объект заполненной структуры списка указателей на интерфейсные методы данной библиотеки */
edo_FunctionList_S	g_stFunctionList =
{
    //  методы библиотеки
    edo_registration,
    edo_output,	
    edo_verifity_suboku,
    edo_adding_velue_suboku,
    edo_result,
    edo_input,
    edo_free_,
};

edo_FunctionList_S* edo_GetFunctionList( void )
{
    return( &g_stFunctionList );
}
	