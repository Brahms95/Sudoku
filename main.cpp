#include <iostream>
#include <iostream>
#include <limits>

#include "Interface.h"

#ifdef __linux__
#include <dlfcn.h>
#endif
typedef int  (*f_ptr)();
using namespace std;
edo_FunctionList_S*	pstFlist;
void *hLibrary;
void linux_example() {
#ifdef __linux__ 
	
	hLibrary = dlopen("libsudokuLib.so", RTLD_LAZY);
	edo_GetFunctionList_T edo_output = (edo_GetFunctionList_T)dlsym(hLibrary, "_Z19edo_GetFunctionListv");
    pstFlist=edo_output();

#endif
}

int main(){
linux_example();

printf (" \t Добро пожаловать в Sudoko \n");
void * user= NULL;
void * pSudoku = NULL;
short _input;
while(true){
printf( "Выберите:\n 1 -  регистрация \n 2 -  войти\n");


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
            user= pstFlist->input(user_name);
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
        std::cout <<  "С возвращением " << "  " << user_name ;
        registration_flag =true;  
        break;
    }

	default:
		printf("Пока! ,Приходи снова\n");
		break;
	}

    std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
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
        _input = 0;
        std::cin >> _input;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::string table_sudoku;

        switch (_input){
        
            case 1:{   
                std::cout <<  "Введите номер строки и номер колонки ( пример 12)" << std::endl;
                std::cin >>table_sudoku ;  
                pstFlist->verifity_suboku(&table_sudoku[0], pSudoku);  
                break;   
                }

            case 2:{   
                std::cout <<  "Введите номер строки и номер колонки ( пример 12) пробел и значение " << std::endl;
                std::cout << "НЕ работает "<< std::endl;
                std::cin >>table_sudoku ;  
                pstFlist->adding_velue_suboku(&table_sudoku[0], pSudoku);  
                break;   
            }    
                
            case 3:{
                std::cout <<  "Чтобо проверить свое решение , надо ввести все цифры подряд (без проелов)" << std::endl;  
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
                
        }
       
    }
}

pstFlist->free_( user, pSudoku);
dlclose(hLibrary);
return 0;
}