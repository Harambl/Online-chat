#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

#define OK_CODE 		quint8(111)
#define WRONG_AUTH_CODE		quint8(31)
#define OK_AUTH_CODE		quint8(17)
#define OK_LOGIN_CODE		quint8(16)
#define WRONG_LOGIN_CODE	quint8(15)

#define LOGIN_CODE 		quint16(65535)
#define AUTH_CODE 		quint16(65533)
#define MESSAGE_CODE 		quint16(65534)

QT_BEGIN_NAMESPACE
namespace Ui {

class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    bool is_connected = false;
    bool is_logined = false;

    QTcpSocket* currSocket;
    QByteArray Data;

    QString currentIp = "127.0.0.1";

    void SendToServer(QString msg);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:

    void slotReadyRead();

};
#endif // MAINWINDOW_H
