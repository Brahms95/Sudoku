#include "Level_1.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <regex>

Level_2::Level_2()
{
	_tiles.resize(81);
	board=this;

}

Level_2::~Level_2()
{
	_tiles.clear();
}

bool Level_2::load()
{	
	const std::string &path = "../table_sudoku/level_2";
	std::ifstream stream(path);
	std::string buffer;

	if (!stream)
		return false;

	stream.seekg(0, std::ios::end);
	buffer.resize(stream.tellg());
	stream.seekg(0);
	stream.read(&buffer[0], buffer.size());
	stream.close();

	std::regex nonNumeric("[^0-9_]");

	buffer = std::regex_replace(buffer, nonNumeric, "");

	// if (buffer.size() != 81)
	// 	return false;

	std::vector<Tile> tiles;
	bool flag = false;


	for (auto &c : buffer)
	{	const char *b = &c;

	
	 std::string s(1, c);
		if ("_" == s ){
			flag = true;
			continue;
		}
		
		auto t = Tile{};
		t.value = (TileValue)(c - '0');

		if (flag)
			t.status = TileStatus::Empty;
		else
			t.status = TileStatus::Solved;
		flag  = false;

		tiles.push_back(t);
	}

	_tiles = tiles;
	return true;
}

bool Level_2::veifity(int a, int d) const{

	auto tile = _tiles[translate(a, d, Level_2::SIZE)];
			
	if( tile.status != TileStatus::Empty){
		std::cout <<"Данное значение уже введено " << std::endl;
		return false ;
		}
	else {
		std::cout <<"Значение: " << static_cast<char>((int)tile.value + 48)  << std::endl;
		return true;
	}			
}

Level_2* Level_2::print(bool flag) const
{	
	std::cout << std::endl << "    ";

	for (int index_row = 0; index_row < Level_2::SIZE; index_row++ ){
		if (index_row ==4 || index_row ==7){
			std::cout << " ";
		}

		std::cout << "  " << index_row << " ";
		
	}
	std::cout << std::endl;
	for (row r = 0; r < Level_2::SIZE; r++)
	{
		std::cout << std::endl;
		std::cout << r << "   ";

		for (column c = 0; c < Level_2::SIZE; c++)
		{
			auto tile = _tiles[translate(c, r, Level_2::SIZE)];
			
			
			auto value = (tile.status == TileStatus::Empty) && (flag)? '-' : static_cast<char>((int)tile.value + 48);

			std::cout << "  " << value << " ";

			if ((c + 1) % Level_2::SQUARE_SIZE == 0 && c != Level_2::SIZE - 1)
				std::cout << "|";
		}

		std::cout << std::endl;

		if ((r + 1) % Level_2::SQUARE_SIZE == 0 && r != Level_2::SIZE - 1)
		{
			std::cout << "    " << std::string(38, '_') << std::endl;
		}
	}
	return _get();

}

inline const unsigned int Level_2::translate(const column &c, const row &r, const unsigned int &width) const
{
	return r * width + c;
}

bool Level_2::verifity_table(char * table) const{
    int index = 0;

    for (row r = 0; r < Level_2::SIZE; r++)
	{
		for (column c = 0; c < Level_2::SIZE; c++)
		{
			auto tile = _tiles[translate(c, r, Level_2::SIZE)];


            if (tile.status != TileStatus::Empty){
                index ++;
                continue;
            }
            else{
                int qw = (int)tile.value;
                if (qw !=table[index]-'0'){
                    return false;
                }
            }
            index ++;
        }   

	}
    
}


// Level_2* Level_2::adding_velue(int a, int b, int c,Board **board_chrcking ) const{

// 	auto tile = _tiles[translate(a, b, Level_2::SIZE)];
			
// 	if( tile.value != TileValue::Empty){
// 		std::cout <<'Данное значение уже введено ' << std::endl;
// 		return nullptr ;
// 	}
// 	else {
// 		if ((int)tile.value == c){
// 			 std::vector<int> tiles1;
// 			 tiles1.push_back(0);
// 	// 				auto t = Tile{};
// 	// t.value =tile.value;
// 	// t.status =TileStatus::Solved;
// 	// tiles1.at(0)=t;


// //tiles1 =_tiles;



// 		}
// 		std::cout <<"Значение: " << static_cast<char>((int)tile.value + 48)  << std::endl;
// 	//	return true;
// 	}
			
// }