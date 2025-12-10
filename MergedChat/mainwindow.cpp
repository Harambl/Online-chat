#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QToolButton>
#include <QInputDialog>
#include <QString>
#include <QToolBar>
#include <QShortcut>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
	dataSize = 0;
	userName = "";

    	ui->setupUi(this);

    	auto* toolbar = addToolBar("");

	loginBtn = new QPushButton("Зарегестрироваться", this);
	authBtn = new QPushButton("Войти", this);
	connectBtn = new QPushButton("Начать чат", this);

    	toolbar->addWidget(authBtn);
    	toolbar->addWidget(loginBtn);
    	toolbar->addWidget(connectBtn);

	setState(ToolsState::UNCONNECTED);
	is_logined = false;

	currSocket = new QTcpSocket(this);

	connect(connectBtn, SIGNAL(clicked()), this, SLOT(slot_connect_btn_clicked()));
	connect(ui->sendBtn, SIGNAL(clicked()), this, SLOT(slot_send_btn_clicked()));
	connect(currSocket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	connect(currSocket, SIGNAL(disconnected()), currSocket, SLOT(deleteLater()));
	connect(authBtn, SIGNAL(clicked()), this, SLOT(slot_auth_btn_clicked()));
	connect(loginBtn, SIGNAL(clicked()), this, SLOT(slot_login_btn_clicked()));
	connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(slot_ip_changed()));
	connect(ui->lineEdit_2, SIGNAL(editingFinished()), this, SLOT(slot_port_changed()));

	new QShortcut(QKeySequence(Qt::Key_Return), const_cast<MainWindow*>(this), SLOT(slot_send_btn_clicked()));
}

void MainWindow::slotReadyRead()
{
	QDataStream in(currSocket);

	if(currSocket->bytesAvailable() == 1) {
		// server sent a code
		quint8 code; in >> code;
		if(code == OK_CODE) {
			setState(ToolsState::CONNECTED);
		} else if(code == OK_AUTH_CODE) {
			userName = _possibleUserName;
			ui->labelUserName->setText("User:\t" + userName);
			setState(ToolsState::LOGINED);
			is_logined = true;
			QMessageBox::information(this, "Notification",
				QString("signed in successfully"));
		} else if(code == WRONG_AUTH_CODE) {
			QMessageBox::warning(this, "Error",
				QString("Invalid username or password. Try again"));
		} else if(code == OK_LOGIN_CODE) {
			QMessageBox::information(this, "Notification",
				QString("logined in successfully"));
		} else if(code == WRONG_LOGIN_CODE) {
			QMessageBox::warning(this, "Error",
				QString("The same user also exists"));
		}
		return;
	}

	if(in.status() == QDataStream::Ok) {
		cout << "reading data..." << endl;		

		for(;;) {
			if(dataSize == 0) {
				if(currSocket->bytesAvailable() < 2) break;
				in >> dataSize;	
			}
			if(currSocket->bytesAvailable() < dataSize) break;
			Message msg;
			in >> msg.time >> msg.userName >> msg.text;
			dataSize = 0;
			ui->textBrowser->append(msg.formated());
		}
		
		cout << "data reading finished" << endl;
	}
	else cout << "data reading error..." << endl;
}


void MainWindow::SendToServer(Message msg)
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_2);
	out << quint16(0) << MESSAGE_CODE << msg.time << msg.userName << msg.text;

	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));

	currSocket->write(Data);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::sendOKcode()
{
	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_2);
	out << OK_CODE;
	currSocket->write(Data);
}

void MainWindow::setState(ToolsState State)
{
	QString sheet;
	switch(State) {
		case ToolsState::UNCONNECTED:
			sheet = QString("background-color: #ff0000");
			authBtn->setEnabled(false);
			loginBtn->setEnabled(false);
			ui->sendBtn->setEnabled(false);
			break;
		case ToolsState::CONNECTED:
			sheet = QString("background-color: #00ff00");
			authBtn->setEnabled(true);
			loginBtn->setEnabled(true);
			ui->sendBtn->setEnabled(false);
			break;
		case ToolsState::LOGINED:
			sheet = QString("background-color: #00ff00");
			authBtn->setEnabled(true);
			loginBtn->setEnabled(true);
			ui->sendBtn->setEnabled(true);
			break;
	};
	is_connected = (State == ToolsState::UNCONNECTED) ? false : true;
}

void MainWindow::slot_ip_changed()
{
	ip = ui->lineEdit->text();	
}

void MainWindow::slot_port_changed()
{
	port = ui->lineEdit_2->text();	
}

void MainWindow::slot_connect_btn_clicked()
{
	if(is_connected) return;
	currSocket->connectToHost(ip, port.toInt());
}

void MainWindow::slot_send_btn_clicked()
{
	if(!is_connected) return;

	Message msg;
	QDateTime currDt = QDateTime::currentDateTime();

	msg.time = currDt.time().toString();
	msg.userName = userName;
	msg.text = ui->inputLine->text();

	msg.text = msg.text.trimmed();
	if(msg.text == "") return; 
	SendToServer(msg);		
	ui->inputLine->setText("");
}

void MainWindow::slot_login_btn_clicked()
{
	if(is_logined) return;

	QString name = QInputDialog::getText(this, "Input", "Name: ");

	if(!checkName(name)) {
		QMessageBox::warning(this, "Error", QString("Invalid username. Try again"));
		return;
	}

	QString passw = QInputDialog::getText(this, "Input", "New password: ");
	std::string _passw = passw.toUtf8().constData();
	size_t hsh = std::hash<std::string>{}(_passw);
	char chsh[128]; sprintf(chsh, "%lld", (long long)hsh);
	QString shsh(chsh);

	if(!checkPassw(passw)) {
		QMessageBox::warning(this, "Error", QString("Invalid password. Try again"));
		return;
	}

	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_2);
	out << quint16(0) << LOGIN_CODE << name << QString(shsh);
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));

	currSocket->write(Data);
}

void MainWindow::slot_auth_btn_clicked()
{
	if(is_logined) return;

	QString name = QInputDialog::getText(this, "Input", "Name: ");

	if(!checkName(name)) {
		QMessageBox::warning(this, "Error", QString("Invalid username. Try again"));
		return;
	}

	QString passw = QInputDialog::getText(this, "Input", "Password: ");
	std::string _passw = passw.toUtf8().constData();
	size_t hsh = std::hash<std::string>{}(_passw);
	char chsh[128]; sprintf(chsh, "%lld", (long long)hsh);
	QString shsh(chsh);

	if(!checkPassw(passw)) {
		QMessageBox::warning(this, "Error", QString("Invalid password. Try again"));
		return;
	}

	Data.clear();
	QDataStream out(&Data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_2);
	out << quint16(0) << AUTH_CODE << name << QString(shsh);
	out.device()->seek(0);
	out << quint16(Data.size() - sizeof(quint16));

	currSocket->write(Data);

	_possibleUserName = name;
	cout << "ok" << endl;
}

bool MainWindow::checkName(QString name)
{ return name != QString(""); }

bool MainWindow::checkPassw(QString passw)
{ return true; }

