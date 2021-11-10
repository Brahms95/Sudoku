#include "Interface.h"
#include "registration/registration_user.h"
#include "sudoku/Board.h"

int  edo_registration (std::string user_name,int level){ return registration( user_name, level); }

void* edo_input (std::string user_name){ return input( user_name); }

void* edo_output(void* user){ return output_table(user); }

bool edo_verifity_suboku(char* index_table, void* pSudoku){ return verifity_suboku(index_table, pSudoku );};
void edo_adding_velue_suboku(char* index_table, void* pSudoku){ return adding_velue_suboku(index_table, pSudoku );};

bool edo_result(char* table_sudoku,  void* pSudoku, void* user) { return result( table_sudoku, pSudoku, user );}

void edo_free_(void* user, void* sudoku){return free_(user, sudoku );}

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
	