#include "textFileBase.h"

template <typename T>
DataBase<T>::DataBase(string _baseName) :  baseName(_baseName)
{
	ofstream ofs (_baseName.c_str(),
		std::ios::app | std::ios::binary);
	ofs.close();
}	


template <typename T>
void DataBase<T>::writeObj(T* obj)
{
	ofstream ofs(baseName.c_str(), std::ios::app | std::ios::binary);
	ofs.write(reinterpret_cast<char*>(obj), sizeof(T));
	cout << sizeof(T) << endl;
	ofs.close();	
}

template <typename T>
bool DataBase<T>::findObj(T* obj)
{
	T _obj {};
	ifstream ifs(baseName.c_str(), std::ios::in | std::ios::binary);
	while(!ifs.eof()) {
		cout << sizeof(T) << endl;
		ifs.read(reinterpret_cast<char*>(&_obj), sizeof(T));
		if(_obj == *obj) return true;
	}		
	ifs.close();
	return false;
}

template <typename T>
vector<T> DataBase<T>::getAllObj()
{
	vector<T> Res {};
	T _obj {};
	ifstream ifs(baseName.c_str(), std::ios::in | std::ios::binary);
	while(!ifs.eof()) {
		cout << sizeof(T) << endl;
		ifs.read(reinterpret_cast<char*>(&_obj), sizeof(T));
		Res.push_back(_obj);
	}		
	ifs.close();
	cout << Res.size() << endl;
	return Res;
}
