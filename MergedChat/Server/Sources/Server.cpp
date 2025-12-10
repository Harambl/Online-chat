#include "Server.h"

Server::Server() : 
	User_DB {DataBase<User>("/home/eust/OnlineChatDataBase.db", USERS_TABLE_NAME)},
	cMessage_DB {DataBase<cMessage>("/home/eust/OnlineChatDataBase.db", MESSAGES_TABLE_NAME)},
	dataSize{0}
{
	if(this->listen(QHostAddress::Any, 4242)) {
		cout << "Server started" << endl;	
	} else {
		cout << "Error with starting server" << endl;
	}		
}

Server::~Server()
{ }

void Server::sendCode(quint8 code, TcpSocket* socket)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_2);
	out << code;
	socket->write(Data);
	QThread::sleep(0.2);
	socket->flush();
	qDebug() << "code sent" ;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	currSocket = new TcpSocket(&Sockets);
	currSocket->setSocketDescriptor(socketDescriptor);
	connect(currSocket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	connect(currSocket, SIGNAL(disconnected()), currSocket, SLOT(deleteSelf()));

	Sockets.push_back(currSocket);

	sendCode(OK_CODE, currSocket);
	cout << "Client connected" << endl;
}

void Server::sendPrevMessages(TcpSocket* socket)
{
	Message msg;
	vector<cMessage> prevMessages {};
	cMessage_DB.getAllObj(&prevMessages, MESSAGES_TABLE_NAME);

	QThread::sleep(2);
      	for(cMessage cmsg : prevMessages) {

		msg.userName = QString(cmsg.userName.c_str());
		msg.text = QString(cmsg.text.c_str());
		msg.time = QString(cmsg.time.c_str());

		SendToClient(msg, socket);
		QThread::sleep(0.1);
		socket->flush();
		qDebug() << "message sent" << msg.text;
       	}
}

void Server::SendToClient(Message msg)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_2);

	out << quint16(0) << msg.time << msg.userName << msg.text;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));

	for(TcpSocket* socket : Sockets)
		socket->write(Data);
}

void Server::SendToClient(Message msg, TcpSocket* socket)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_2);

	out << quint16(0) << msg.time << msg.userName << msg.text;
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));
	socket->write(Data);
}

void Server::slotReadyRead()
{
	currSocket = static_cast<TcpSocket*>(sender());
	Message msg;
	cMessage cmsg;
	QString name, passHash;
	QDataStream in(currSocket);
	in.setVersion(QDataStream::Qt_5_2);
	dataSize = 0;

	quint16 code {0};

	if(in.status() == QDataStream::Ok) {
		cout << "reading data..." << endl;		

		for(;;) {

			if(dataSize == 0) {
				if(currSocket->bytesAvailable() < 4) {
					cout << "dataSize reading error..." << endl;
					break;		
				}
				in >> dataSize;	
			}

			if(currSocket->bytesAvailable() < dataSize) break;

			in >> code;

			if(code == MESSAGE_CODE) {
				in >> msg.time >> msg.userName >> msg.text;
				SendToClient(msg);

				cmsg.userName = msg.userName.toUtf8().constData();
				cmsg.text = msg.text.toUtf8().constData();
				cmsg.time = msg.time.toUtf8().constData();

				cMessage_DB.writeObj(cmsg, MESSAGES_TABLE_NAME);
				qDebug() << "msg: " << msg.formated();

			} else if(code == LOGIN_CODE) {
				in >> name >> passHash;
				if(login(name, passHash) == true)
					sendCode(OK_LOGIN_CODE, currSocket);
				else
					sendCode(WRONG_LOGIN_CODE, currSocket);

			} else if(code == AUTH_CODE) {
				in >> name >> passHash;
				if(auth(name, passHash) == true) {
					sendCode(OK_AUTH_CODE, currSocket);
					QThread::sleep(0.5);
					sendPrevMessages(currSocket);
				} else
					sendCode(WRONG_AUTH_CODE, currSocket);
			}

		}

		cout << "reading finished" << endl;
	}
	else cout << "data reading error..." << endl;
}

bool Server::login(QString name, QString passHash)
{
	User findingUser;
	findingUser.name = name.toUtf8().constData();
	findingUser.passHash = passHash.toUtf8().constData();

	if(User_DB.findObj(&findingUser, USERS_TABLE_NAME)) return false;

	User_DB.writeObj(findingUser, USERS_TABLE_NAME);
	qDebug() << name + QString(" logined sucessfully");	

	return true;
}

bool Server::auth(QString name, QString passHash)
{
	qDebug() << name << passHash;
	User findingUser;

	findingUser.name = name.toUtf8().constData();
	findingUser.passHash = passHash.toUtf8().constData();

	return User_DB.findObj(&findingUser, USERS_TABLE_NAME);
}





