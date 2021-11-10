cmake_minimum_required(VERSION 3.5)

project (SudokuSolver)

set(CMAKE_CXX_STANDARD 14)

add_library(sudokuLib SHARED 

registration/registration_user.cpp
registration/registration_user.h
sudoku/Board.cpp
sudoku/Level_0.cpp
sudoku/Level_0.h
sudoku/Level_1.cpp
sudoku/Level_1.h
sudoku/Board.h
sudoku/status.h
Interface.h
Interface.cpp
)

target_compile_definitions(sudokuLib
	PRIVATE
	-DBUILD_SUM_DLL
)

#add_subdirectory(engine)

add_executable(
	main
	main.cpp
)

target_link_libraries(main
	PRIVATE
    sudokuLib
    dl
)

