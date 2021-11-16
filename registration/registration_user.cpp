
#include <fstream>  	
#include <iostream>
#include <map>
#include <iostream>
#include "../Interface.h"
#include "registration_user.h"
#include <stdio.h>

static const std::string high_scores_filename = "users";
int  registration( std::string &user_name,int level){// Write new high score to the records table
	
	std::fstream out_file_first;
	out_file_first.open(high_scores_filename, std::fstream::in | std::fstream::out | std::fstream::app);
	if (!out_file_first.good()){
		std::ofstream out_file_first{high_scores_filename};
	}
	
	if (!out_file_first.is_open()) {
		std::cout << "Файл невозможно открыть :" << high_scores_filename << "!" << std::endl;
		return (int)Return::Error;
	}

	std :: string first_name = "";
	int number = 0;

	while (out_file_first.good()) {
		// Read thtable_request username first
		out_file_first >> first_name;
			
		if (first_name == user_name)
		{	
			std::cout << "Ползователь уже есть с таким именем\n";
			out_file_first.close();
			return Return::Error ;	
		}
		out_file_first >> number;
		}

		out_file_first.clear();
		out_file_first.seekg(0, std::ios::end);
		out_file_first << user_name << " ";
		out_file_first << level;
		out_file_first <<"\n";
		User *user =new User();
		
		user->get_name_user(first_name, number);
		out_file_first.close();
		
		return Return::Ok;
		
}

User* input(std::string &user_name ){

	std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Файл невозможно открыть :  " << high_scores_filename << " или необходимо зарегистрироваться " << "!" << std::endl;
		return nullptr;
	}
	
	std :: string first_name = "";
	int number = 0;

	while (true) {
		
		in_file >> first_name;
		if (first_name.empty()){
			std::cout << "Нет такого пользователя. Необходимо зарегистрироваться " << std::endl;
			return  nullptr;
		}
				
		if (first_name == user_name){	
			in_file >> number;		
			User *user =new User();
			user->get_name_user(first_name, number);		
			in_file.close();
			return  user ;	
		}
		first_name = "";
		// Read the high score next
		in_file >> number;
	}
	in_file.close();
	std::cout << "Нет такого пользовотеля" << std::endl;
	return  nullptr ;
}

int User:: checking_level( ){
	std::ifstream out_file{high_scores_filename};
	if (!out_file.is_open()) {
		std::cout << "Файл невозможно открыть :  "  << high_scores_filename << "!" << std::endl;
		return -1;
	}

	else{
	//узнаем колличества строк в файле
		char *str = new char [1024];
 		int line=0;

    	while (!out_file.eof())
    	{
        	out_file.getline(str, 1024, '\n');
		
			if (str[0] !=  '\0' ){
				line++;
			}
        
    	}

		out_file.clear();
		out_file.seekg(0, std::ios::beg);

		std::string*  username = new std::string [line];
		int* high_score= new int[line];
		for (int index=0; index<line; index++){
			out_file >> username[index];
			out_file >> high_score[index];

			out_file.ignore();
			if (out_file.fail()) {
				break;
			}
		}	
		out_file.close();
		std::ofstream ate_file{high_scores_filename};
		if (!ate_file.is_open()) {
			std::cout << "Файл невозможно открыть :  " << high_scores_filename << "!" << std::endl;
			return -1;
			}
		

		for (int index=0; index<line; index++){
		//переписываем на лучший рещультат
			if (username[index]== _get_name()) {
				set_level_(high_score[index]+1);
				high_score[index]=_get_level();	
			}	
		}

		for (int index=0; index<line; index++){
			ate_file << username[index] << ' ';
			ate_file << high_score[index];
			if (index != line-1)
				ate_file << std::endl;
			}
			
			delete []high_score;
			delete [] username;
			
		ate_file << std::endl;
		ate_file.close();
	}	
	
	return 1;
		
}

	