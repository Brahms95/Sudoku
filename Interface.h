#include "sudoku/Board.h"
#include "registration/registration_user.h"


/**
 * Регистрация пользователя 
 * @param user_name  - Имя пользователя
 * @param level  - Уровень пользователя
 * @return Результат выполнения или код ошибки: 1 - успешно, иначе ошибка
 */    
int edo_registration ( std::string user_name,int level);
typedef int ( *edo_registration_T)( std::string, int);

/**
 * Вывод информации о пользователе 
 * @param user_name  - Имя пользователя
 
 * @return Указатель на класс user
 */    
void* edo_input ( std::string user_name);
typedef void* ( *edo_input_T)( std::string);

/**
 * Вывод таблицы  для определенного пользователя 
 * @param user - Указатель на класс user

 * @return Результат выполнения указатель на класс sudoku
 */
void*  edo_output(void* user);
typedef void* ( *edo_output_T)( void* user);

/**
 * Помощь решение Sudoku
 * @param index_table - Номер строки и номер колонки
 * @param pSudoku  - Указатель на класс sudoku
 * @return Результат выполнения или код ошибки: true - успешно, иначе ошибка
 */
bool edo_verifity_suboku(char* index_table, void* pSudoku);
typedef bool ( *edo_verifity_suboku_T)( char* index_table, void* pSudoku);


/**
 * Ввод значения 
 * @param index_table - Номер строки и номер колонки и значение 
 * @param pSudoku  - Указатель на класс sudoku
 * @return Результат выполнения или код ошибки: true - успешно, иначе ошибка
 */
void edo_adding_velue_suboku(char* index_table, void* pSudoku);
typedef void ( *edo_adding_velue_suboku_T)( char* index_table, void* pSudoku);

/**
 * Проверка решенной Sudoku  и вывод решеной 
 * @param table_sudoku  - Таблица sudoku 
 * @param pSudoku [in] - Указатель на класс sudoku
 *  * @param user [in] - Указатель на класс user
* @return Результат выполнения или код ошибки: true - успешно, иначе ошибка
 */
bool edo_result(char* table_sudoku,  void* pSudoku, void* user);
typedef bool ( *edo_result_T)( char* table_sudoku,  void* pSudoku, void* user );

/**
 * Освобожнение памяти 
 * @param pSudoku  - Указатель на класс sudoku
 *  * @param user  - Указатель на класс user
* @return Результат выполнения :освобождение памяи 
 */
void edo_free_(void*, void*);
typedef void ( *edo_free_T)(void* user, void* sudoku);

/** Структура списка указателей на интерфейсные методы данной библиотеки */
struct edo_FunctionList_S
{   edo_registration_T registration;
    edo_output_T output;
    edo_verifity_suboku_T verifity_suboku;
    edo_adding_velue_suboku_T adding_velue_suboku;
    edo_result_T result;
    edo_input_T input;
    edo_free_T  free_;

};



typedef struct edo_FunctionList_S	edo_FunctionList_S;
/**
 * Получение указателя на структуру edo_FunctionList_S
 * @return Ненулевой указатель на структуру списка указателей на интерфейсные методы данной библиотеки edo_FunctionList_S
 */
 edo_FunctionList_S* edo_GetFunctionList( void );
typedef edo_FunctionList_S* ( *edo_GetFunctionList_T )( void );
