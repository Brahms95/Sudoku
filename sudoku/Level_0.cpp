#include "Level_0.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <regex>

Level_0::Level_0()
{
	_tiles.resize(36);
	board=this;

}

Level_0::~Level_0()
{
	_tiles.clear();
//	delete board;
}

bool Level_0::load()
{	
	const std::string &path = "../table_sudoku/level_0";
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

	// if (buffer.size() != 36)
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

bool Level_0::verifity(int a, int d) const{

	auto tile = _tiles[translate(a, d, Level_0::SIZE)];
			
	if( tile.status != TileStatus::Empty){
		std::cout <<"Данное значение уже введено" << std::endl;
		return false ;
	}
	else {
		std::cout <<"Значение: " << static_cast<char>((int)tile.value + 48)  << std::endl;
		return true;
	}
			
}

Level_0* Level_0::print(bool flag) const
{	
	std::cout << std::endl << "    ";

	for (int index_row = 0; index_row < Level_0::SIZE; index_row++ ){
		if (index_row ==4 || index_row ==7){
			std::cout << " ";
		}

		std::cout << "  " << index_row << " ";
		
	}
	std::cout << std::endl;
	for (row r = 0; r < Level_0::SIZE; r++)
	{
		std::cout << std::endl;
		std::cout << r << "   ";

		for (column c = 0; c < Level_0::SIZE; c++)
		{
			auto tile = _tiles[translate(c, r, Level_0::SIZE)];
			
			
			auto value = (tile.status == TileStatus::Empty) && (flag)? '-' : static_cast<char>((int)tile.value + 48);

			std::cout << "  " << value << " ";

			if ((c + 1) % Level_0::SQUARE_SIZE == 0 && c != Level_0::SIZE - 1)
				std::cout << "|";
		}

		std::cout << std::endl;

		if ((r + 1) % Level_0::SQUARE_SIZE == 0 && r != Level_0::SIZE - 1)
		{
			std::cout << "    " << std::string(15, '_') << std::endl;
		}
	}
	
	return _get();

}

inline const unsigned int Level_0::translate(const column &c, const row &r, const unsigned int &width) const
{
	return r * width + c;
}

bool Level_0::verifity_table(char* table) const{
    int index = 0;

    for (row r = 0; r < Level_0::SIZE; r++)
	{
		for (column c = 0; c < Level_0::SIZE; c++)
		{
			auto tile = _tiles[translate(c, r, Level_0::SIZE)];

            if (tile.status != TileStatus::Empty){
                index ++;
                continue;
            }
            else{
                int tile_value = (int)tile.value;
				int table_value = table[index]-'0';
                if (tile_value != table_value){
                    return false;
                }
            }
            index ++;
        } 

 	}
 	return true;
}


bool Level_0::adding_velue(int a, int b, int c ) {
	auto tile = _tiles[translate(a, b, Level_0::SIZE)];
			
	if( tile.status != TileStatus::Empty){
		std::cout << "Данное значение уже введено" << std::endl;
		return false ;
	}
	else {
		if ((int)tile.value == c){
			std::vector<Tile> tiles;
			tiles= _tiles;
			_tiles.clear();

			auto t = Tile{};
			t.value =tile.value;
			t.status =TileStatus::Solved;

 			tiles[translate(a, b, Level_0::SIZE)]= t;
			_tiles= tiles;
			return true;
		}
	}
	return false;			
}