#include "DataBase.h"
#include "User.h"
#include "cmsg.h"

int main()
{
	DataBase<User> User_DB("/home/eust/MyBase.db", "Users");
	DataBase<cMessage> cMessage_DB("/home/eust/MyBase.db", "Messages");
	
	//User_DB.writeObj(User({(char*)"Bob5", (char*)"12345"}), (char*)"Users");
	//User_DB.writeObj(User({(char*)"Bob6", (char*)"12345"}), (char*)"Users");
	//User_DB.writeObj(User({(char*)"Bob7", (char*)"12345"}), (char*)"Users");
	//User_DB.writeObj(User({(char*)"Bob8", (char*)"12345"}), (char*)"Users");
	//cMessage_DB.writeObj(cMessage({"Bob", "Hello.", "11:11:12"}), "Messages");
	//cMessage_DB.writeObj(cMessage({"Bob", "How are you?", "11:13:12"}), "Messages");

	//User* u {new User({(char*)"Bob", (char*)"12345"})};
	//bool r;
	//r = User_DB.findObj(u, "Users");
	//cout << "RESULT: " << r << endl;
	//delete u;

	//vector<User> vUsers {};
	//User_DB.getAllObj(&vUsers, "Users");	

	return 0;
}
