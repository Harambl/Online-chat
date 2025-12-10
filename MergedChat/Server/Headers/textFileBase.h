#ifndef TEXTFILEBASE
#define TEXTFILEBASE

#if(0)

#include <fstream>
#include <iostream>
#include <QString>
#include <string>
#include <vector>
#include "User.h"
#include "msg.h"
#include "cmsg.h"

using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;

template<typename T>
class DataBase {
	string baseName;	
public:
	DataBase(string _baseName);
	void writeObj(T* obj);
	bool findObj(T* obj);
	vector<T> getAllObj();
};

template struct DataBase<cMessage>;
template struct DataBase<User>;

#endif(0)

#endif
