#ifndef CMESSAGE_H
#define CMESSAGE_H

#define MAX_USERNAME_SIZE		128
#define MAX_MESSAGE_SIZE		256
#define MAX_TIME_SIZE			128

#include "abstractData.h"
#include <stdexcept>
#include <string>

using std::string;


struct cMessage {
	string userName;	
	string text;	
	string time;	

	static vector<pair<string, string>> getTableStructure()
	{
		char type1[32] {""}, type2[32] {""}, type3[32] {""};
		sprintf(type1, "VARCHAR(%d) NOT NULL", MAX_USERNAME_SIZE);
		sprintf(type2, "VARCHAR(%d) NOT NULL", MAX_MESSAGE_SIZE);
		sprintf(type3, "VARCHAR(%d) NOT NULL", MAX_TIME_SIZE);

		return {
	   	      	{"userName", type1}, {"text", type2}, {"time", type3}
		};
	}

	static cMessage initialize(int argc, char** argv)
	{
		if(argc != 3 + 1)
			throw std::runtime_error("invalid argument count");
		cMessage cmsg;
	       	cmsg.userName = argv[1];
		cmsg.text = argv[2];
		cmsg.time = argv[3];
		return cmsg;
	}

	vector<pair<string, Type>> getValues() const
	{
		return {
			 {userName, Type::STR},
			 {text, Type::STR},
			 {time, Type::STR}
		};
	}

	string formated() 
	{
		return userName + " [" + time + "] " + text;  		
	}
	
	bool operator==(const cMessage& other)
	{
		bool cond1, cond2, cond3;
		cond1 = (strcmp(userName.c_str(), other.userName.c_str()) == 0);
		cond2 = (strcmp(text.c_str(), other.text.c_str()) == 0);
		cond3 = (strcmp(time.c_str(), other.time.c_str()) == 0);
		return cond1 && cond2 && cond3;
	}
};

#endif
