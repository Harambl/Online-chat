#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QToolButton>
#include <QInputDialog>
#include <QString>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto* toolbar = addToolBar("");

    QToolButton*  regButton = new QToolButton();
    regButton->setText("Зарегистрироваться");

    QToolButton* logButton = new QToolButton();
    logButton->setText("Войти");

    QToolButton* startButton = new QToolButton();
    startButton->setText("Начать чат");

    connect(regButton, &QToolButton::clicked, this, [this]() {
        QString name = QInputDialog::getText(this, "Регистрация", "Введите ваше имя: ", QLineEdit::Normal);
        slot_connect_btn_clicked();
        QString password = QInputDialog::getText(this, "Регистрация", "Введите ваш пароль: ", QLineEdit::Normal);
        ui->user_label->setText(name);
    });

    connect(logButton, &QToolButton::clicked, this, [this]() {
        QString name = QInputDialog::getText(this, "Вход", "Введите ваше имя:", QLineEdit::Normal);
        slot_connect_btn_clicked();
        QString password = QInputDialog::getText(this, "Вход", "Введите ваш пароль: ", QLineEdit::Normal);
        ui->user_label->setText(name);
    });

    connect(startButton, &QToolButton::clicked, this, [this]() {
        QString name = QInputDialog::getText(this, "Старт", "Введите имя пользователя того с кем хотите начать общение:", QLineEdit::Normal);
        slot_connect_btn_clicked();
    });

    connect(ui->sendButton, &QPushButton::clicked, this, slot_send_btn_clicked());

    toolbar->addWidget(regButton);
    toolbar->addWidget(logButton);
    toolbar->addWidget(startButton);

}

void MainWindow::slotReadyRead()
{
    QDataStream in(currSocket);
    if(in.status() == QDataStream::Ok) {
        QString msg;
        in >> msg;
        ui->messageBrowser->append(msg);
    }
    else ui->messageBrowser->append("Ошибка");;
}

void MainWindow::slot_connect_btn_clicked()
{
    currSocket->connectToHost("127.0.0.1", 55555);
}

void MainWindow::slot_send_btn_clicked()
{
    SendToServer(ui->textEdit->text());
    ui->textEdit->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}
