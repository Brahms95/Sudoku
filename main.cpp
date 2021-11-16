#include <iostream>
#include <limits>
#include <clocale>
#include "Interface.h"

#ifndef __GNUC__
	#include <windows.h>						// For Windows types definition

#endif	// __GNUC__

#undef max
#ifdef __GNUC__
	#include <dlfcn.h>							// For dlopen( ... ), dlclose( ... ) and dlsym( ... ) definitions
	typedef	void*	HMODULE;
#endif	// __GNUC__

using namespace std;
edo_FunctionList_S*	pstFlist;
HMODULE	hLibrary;


void LoadStorageLibrary() {

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
        pstFlist=edo_function();
        }
    } 

}

int main(){
    setlocale(LC_ALL,"Russian");
    LoadStorageLibrary();

    printf (" \t Добро пожаловать в Sudoko \n");
    User * user= NULL;
    Board * pSudoku = NULL;
    short _input;
    while(true){
    printf( "Выберите:\n 1 -  Регистрация \n 2 -  Войти\n");

    std::cin >> _input;
    // std::cin.clear();
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::string user_name;

    bool registration_flag = false;

    printf ("Введите login\n");
    std::cin >> user_name;
    switch (_input){
    
        case 1:{
            
            if (pstFlist->registration(user_name,0) != 1)   {
                user = pstFlist->input(user_name);
                if (user == NULL){
                    break;  
                }
                std::cout <<  "Добро пожаловать" << "  " << user_name ;  
                registration_flag =true;  
                break;  
            }
            else {
                break; 
            }
        }

        case 2:{
            user= pstFlist->input(user_name);
            if (user == NULL){
                break;  
            }
            std::cout <<  "С возвращением" << "  " << user_name ;
            registration_flag =true;  
            break;
        }

        default:
            printf("Пока! ,Приходи снова\n");
            break;
        }

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        if (registration_flag) {
            break;
        }
    }
    // работа с Sudoku
    bool flag_sudoku = false;
    pSudoku =pstFlist->output(user);
    if (pSudoku)
    {   while(true){
            std::cout <<  " 1 - Помощь" << std::endl;  
            std::cout <<  "2 - Добавить правильный ответ  " << std::endl;  
            std::cout <<  "3 - Проверить " << std::endl;
            std::cout <<  "4 - Выход " << std::endl;
            _input = 0;

            std::cin >> _input;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::string table_sudoku;

            switch (_input){
            
                case 1:{   
                    std::cout <<  "Введите номер строки и номер колонки (например: 12)" << std::endl;
                    std::cin >>table_sudoku ;  
                    pstFlist->verifity_suboku(&table_sudoku[0], pSudoku);  
                    break;   
                }

                case 2:{   
                    std::cout <<  "Введите номер строки и номер колонки (Например 12) пробел и значение " << std::endl;
                    std::cin >>table_sudoku ; 
            
                    if (table_sudoku.size() == 4 ){
                        pstFlist->adding_velue_suboku(&table_sudoku[0], pSudoku);
                    }
                    else{
                        std::cout <<  "Введите номер строки и номер колонки (Например 12) пробел и значение " << std::endl;
                    }
                
                    break;   
                }    
                    
                case 3:{
                    std::cout <<  "Чтобо проверить свое решение , надо ввести все цифры подряд (без пробелов)" << std::endl;  
                    std::cin >>table_sudoku ;
                    //2341143242133124
                    if (pstFlist->result(&table_sudoku[0], pSudoku, user)){
                        pSudoku=NULL;
                        pSudoku =pstFlist->output(user);
                        std::cout <<  "Отлично. Продолжай в том же духе!" << std::endl;  
                        break;
                    }  
                    break;
                }

                case 4:{
                    pstFlist->free_( user, pSudoku);
                    return 0;
                }

                default:
                    break;
                  
            }
        
        }
    }

    pstFlist->free_( user, pSudoku);

#ifdef __GNUC__
		dlclose( hLibrary );
#else	// __GNUC__
		::FreeLibrary( hLibrary );
#endif	// __GNUC__
    return 0;
}