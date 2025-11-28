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
    ui->setupUi(this);

    currSocket = new QTcpSocket(this);

    auto* toolbar = addToolBar("");

    QToolButton*  regButton = new QToolButton();
    regButton->setText("Зарегистрироваться");

    QToolButton* logButton = new QToolButton();
    logButton->setText("Войти");

    QToolButton* startButton = new QToolButton();
    startButton->setText("Начать чат");

    connect(ui->textEdit, &QLineEdit::returnPressed, this, [this](){
        SendToServer(ui->textEdit->text());
        ui->textEdit->setText("");
    });

    connect(regButton, &QToolButton::clicked, this, [this]() {
        QString name = QInputDialog::getText(this, "Регистрация", "Введите ваше имя: ", QLineEdit::Normal);
        QString password = QInputDialog::getText(this, "Регистрация", "Введите ваш пароль: ", QLineEdit::Normal);
        currSocket->connectToHost("127.0.0.1", 55555);
        ui->user_label->setText(name);
    });

    connect(logButton, &QToolButton::clicked, this, [this]() {
        QString name = QInputDialog::getText(this, "Вход", "Введите ваше имя:", QLineEdit::Normal);
        QString password = QInputDialog::getText(this, "Вход", "Введите ваш пароль: ", QLineEdit::Normal);
        currSocket->connectToHost("127.0.0.1", 55555);
        ui->user_label->setText(name);
    });

    connect(startButton, &QToolButton::clicked, this, [this]() {
        QString name = QInputDialog::getText(this, "Старт", "Введите имя пользователя того с кем хотите начать общение:", QLineEdit::Normal);

    });

    connect(ui->sendButton, &QPushButton::clicked, this, [this](){
        SendToServer(ui->textEdit->text());
        ui->textEdit->setText("");
    });

    connect(currSocket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);

    toolbar->addWidget(regButton);
    toolbar->addWidget(logButton);
    toolbar->addWidget(startButton);

}

void MainWindow::slotReadyRead()
{
    QDataStream in(currSocket);
    if(in.status() == QDataStream::Ok) {
        QString msg;
        QString timeString = QDateTime::currentDateTime().toString("hh:mm:ss");
        QString messageWithTime = "[" + timeString + "] " + msg;
        in >> messageWithTime;

        ui->messageBrowser->append(messageWithTime);
    }
    else ui->messageBrowser->append("Ошибка");
}


void MainWindow::SendToServer(QString msg)
{
    if (!currSocket || !currSocket->isWritable()) {
        ui->messageBrowser->append("Не подключено к серверу!");
        return;
    }

    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString timeString = currentDateTime.toString("hh:mm:ss");

    QString messageWithTime = "[" + timeString + "] " + msg;
    out << messageWithTime;

    currSocket->write(Data);
}

MainWindow::~MainWindow()
{
    delete ui;
}
