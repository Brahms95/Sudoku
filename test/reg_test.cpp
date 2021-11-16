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

#include "../registration/registration_user.h"
#include <gtest/gtest.h>

using namespace std;
edo_FunctionList_S*	pstFlist;
HMODULE	hLibrary;

//--------------------------------------------------------------------------------------------------------------------
struct Sudoku : public testing::Test {
   public:

    static bool storageLoaded  ;
    static HMODULE hLibrary;
 
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

bool Sudoku::storageLoaded = false;
HMODULE Sudoku::hLibrary= NULL;


TEST_F(Sudoku, Registration_user) {
    std::string user_name = "test";
    User* user =NULL;; 
    if (storageLoaded)
        ASSERT_EQ(pstFlist->registration(user_name,0), 0);
}

TEST_F(Sudoku, Input_user) {
    std::string user_name = "test";
    User* user =NULL;
    if (storageLoaded){
       user = pstFlist->input(user_name);
        ASSERT_TRUE (user != NULL);
        delete user;
    }
}

TEST_F(Sudoku, Checking_level) {
    std::string user_name = "test";
    User* user =NULL;; 
    if (storageLoaded){
        user = pstFlist->input(user_name);
        user->checking_level();
        user= NULL;
        user = pstFlist->input(user_name);

        ASSERT_EQ(user->get_level(), 1);
        delete user;
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}