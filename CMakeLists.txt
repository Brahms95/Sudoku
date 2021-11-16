cmake_minimum_required(VERSION 3.0)

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
if(MSVC)
target_link_libraries(main
	PRIVATE
    sudokuLib
)

else()

target_link_libraries(main
	PRIVATE
    sudokuLib
    dl
)

endif()
#gTest
if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Build googletest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/gTest/googletest" 
    "googletest"
)


add_executable(
    test_registration
    test/reg_test.cpp
    registration/registration_user.cpp
    registration/registration_user.h
    
)

add_executable(
    test_level_1
    test/level1_test.cpp
    sudoku/Level_0.h
   sudoku/Level_0.cpp
    
)
add_executable(
    test_level_2
    test/level2_test.cpp
    sudoku/Level_1.h
   sudoku/Level_1.cpp
    
)

if(MSVC)
target_link_libraries(
    test_registration PRIVATE
    gtest gtest_main sudokuLib
)

target_link_libraries(
    test_level_1 PRIVATE
    gtest gtest_main sudokuLib
)

target_link_libraries(
    test_level_2 PRIVATE
    gtest gtest_main sudokuLib
)
else()

target_link_libraries(
    test_registration PRIVATE
    gtest gtest_main sudokuLib -ldl
)

target_link_libraries(
    test_level_1 PRIVATE
    gtest gtest_main sudokuLib -ldl
)

target_link_libraries(
    test_level_2 PRIVATE
    gtest gtest_main sudokuLib  -ldl
)
endif()