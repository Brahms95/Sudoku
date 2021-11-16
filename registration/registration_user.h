#ifndef OFSTREAM_FILE_H
#define OFSTREAM_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

 enum Return{
        Ok = 0,
        Error = 1,
};

class User {
 
    public:
 
        int  checking_level( );
        void get_name_user(std::string name_user, int level){
            this->name_user = name_user;
            this->level = level;
        }
         int get_level(){
             return this->level;
        }
   
        std::string _get_name(){return name_user;};
        int _get_level(){ return level;};
        void set_level_(int level){ this->level= level;};
       
    private:
        std::string name_user;
        int level;
     
};

int registration( std::string &user_name,int level);
User* input(std::string &user_name);

#endif