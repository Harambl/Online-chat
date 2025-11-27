#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {

class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTcpSocket* currSocket;
    QByteArray Data;

    void SendToServer(QString msg);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void slot_send_btn_clicked();
    void slot_connect_btn_clicked();
    void slotReadyRead();

};
#endif // MAINWINDOW_H
