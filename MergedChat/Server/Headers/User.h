#ifndef USER_H
#define USER_H

#define MAX_LEN			128
#define MAX_HASH_LEN		128

#include "abstractData.h"
#include <stdexcept>
#include <string>

using std::string;


struct User {

	string name;
	string passHash;	

	static vector<pair<string, string>> getTableStructure()
	{
		char type1[32] {""}, type2[32] {""};
		sprintf(type1, "VARCHAR(%d) UNIQUE NOT NULL", MAX_LEN);
		sprintf(type2, "VARCHAR(%d) NOT NULL", MAX_HASH_LEN);

		return {
	   	      	{"name", type1}, {"passHash", type2}
		};
	}

	static User initialize(int argc, char** argv)
	{
		if(argc != 2 + 1)
			throw std::runtime_error("invalid argument count");
		User u;
		u.name = argv[1];
		u.passHash = argv[2];
		return u;	
	}

	vector<pair<string, Type>> getValues() const
	{
		return { {name, Type::STR}, {passHash, Type::INT} };
	}

	string formated()
	{
		return "name: " + name + "  |  password hash: " + passHash;	
	}

	bool operator==(const User& other)
	{
		bool cond1 = (strcmp(name.c_str(), other.name.c_str()) == 0);
	       	bool cond2 = (strcmp(passHash.c_str(), other.passHash.c_str()) == 0);	
		return cond1 && cond2;
	}
};


#endif
