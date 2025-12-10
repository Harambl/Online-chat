#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

#include <QTcpSocket>
#include <QDataStream>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QColor>
#include <string.h>
#include <QTextBrowser>
#include <QGridLayout>
#include <QDateTime>
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include <iostream>
#include <vector>
#include <functional>
#include <QShortcut>
#include "msg.h"

#define OK_CODE 		quint8(111)
#define WRONG_AUTH_CODE		quint8(31)
#define OK_AUTH_CODE		quint8(17)
#define OK_LOGIN_CODE		quint8(16)
#define WRONG_LOGIN_CODE	quint8(15)

#define LOGIN_CODE 		quint16(65535)
#define AUTH_CODE 		quint16(65533)
#define MESSAGE_CODE 		quint16(65534)

using std::cout;
using std::endl;
using std::vector;

enum class ToolsState { CONNECTED, LOGINED, UNCONNECTED};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    	Q_OBJECT

	QString ip {"127.0.0.1"};
	QString port {"4242"};
	bool is_connected;
	bool is_logined;
	QTcpSocket* currSocket;
	QByteArray Data;
	quint16 dataSize;

	QString userName;
	QString _possibleUserName;

	QPushButton* authBtn;
	QPushButton* loginBtn;
	QPushButton* connectBtn;

	void SendToServer(Message msg);
	void setState(ToolsState State);
	void sendOKcode();
	bool checkName(QString name);
	bool checkPassw(QString passw);

public:
    	MainWindow(QWidget *parent = nullptr);
    	~MainWindow();

private:
    	Ui::MainWindow *ui;

public slots:

	void slot_send_btn_clicked();
	void slot_connect_btn_clicked();
	void slot_auth_btn_clicked();
	void slot_login_btn_clicked();
	void slot_ip_changed();
	void slot_port_changed();
	void slotReadyRead();

};


#endif // MAINWINDOW_H
