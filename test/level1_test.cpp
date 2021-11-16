#include <iostream>

#include <iostream>
#include <limits>

#include "../Interface.h"
#ifndef __GNUC__
	#include <windows.h>						// For Windows types definition
#endif	// __GNUC__

#undef max
#ifdef __GNUC__
	#include <dlfcn.h>							// For dlopen( ... ), dlclose( ... ) and dlsym( ... ) definitions
	typedef	void*	HMODULE;
#endif	// __GNUC__


#include "../sudoku/Level_0.h"
#include <gtest/gtest.h>

using namespace std;
edo_FunctionList_S*	pstFlist;
HMODULE	hLibrary;

//--------------------------------------------------------------------------------------------------------------------
struct Sudoku_level_1 : public testing::Test {
   public:

    static bool storageLoaded  ;
    static HMODULE	hLibrary;
    static  User* user;
    static Board* board;
    static void  SetUpTestSuite() {

         #ifdef __GNUC__
        hLibrary = dlopen("libsudokuLib.so", RTLD_LAZY);
    #else	// __GNUC__
        hLibrary = ::LoadLibrary("sudokuLib.dll");
    #endif	// __GNUC__
        if (hLibrary != NULL) {
    #ifdef __GNUC__
        edo_GetFunctionList_T edo_function = (edo_GetFunctionList_T)dlsym(hLibrary, "_Z19edo_GetFunctionListv");
        pstFlist=edo_function();
    #else	// __GNUC__
        edo_GetFunctionList_T edo_function = (edo_GetFunctionList_T)::GetProcAddress(hLibrary, "_Z19edo_GetFunctionListv");
    #endif	// __GNUC__
        if (pstFlist != NULL) {	
       Level_0 level_0;
            board = new Level_0();
            storageLoaded = true;
        }
    } 
    }

    // Per-test-suite tear-down.
    static void TearDownTestSuite() {
        if(remove("users")) {
            printf("Error removing file");
        }
#ifdef __GNUC__
		dlclose( hLibrary );
#else	// __GNUC__
		::FreeLibrary( hLibrary );
#endif	// __GNUC__
    }
};

bool Sudoku_level_1::storageLoaded = false;
HMODULE Sudoku_level_1::hLibrary= NULL;
User* Sudoku_level_1::user= NULL;
Board* Sudoku_level_1::board = NULL;


TEST_F(Sudoku_level_1, output_sudoku) {
   
    if (storageLoaded)
        ASSERT_TRUE(board->load());
  
}

TEST_F(Sudoku_level_1, verifity_sudoku_statusT) {
   std::map<int,int> map_value ={{0,1},{0,1}, {2,0} };
 
    if (storageLoaded){
        for(auto& item : map_value){
            ASSERT_TRUE(board->verifity(item.first, item.second));
        }
    }  
}


TEST_F(Sudoku_level_1, verifity_sudoku_statusF) {
    std::map<int,int> map_value ={{2,1},{0,0}, {1,3} };
   
    if (storageLoaded){
         for(auto& item : map_value){
             ASSERT_FALSE(board->verifity(2,1));
        }
    }
}

TEST_F(Sudoku_level_1, adding_velue_sudoku) {
   
    if (storageLoaded)
        ASSERT_TRUE(board->adding_velue(0,1,1));
  
}

TEST_F(Sudoku_level_1, verifity_table_sudoku) {
    std::string table_values = "2341143242133124";

    if (storageLoaded)
        ASSERT_TRUE(board->verifity_table(&*table_values.begin()));

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
   
    return RUN_ALL_TESTS();
}