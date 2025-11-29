/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *curr_label;
    QLabel *labelUserName;
    QPushButton *sendBtn;
    QTextBrowser *textBrowser;
    QLineEdit *inputLine;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(857, 636);
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        curr_label = new QLabel(centralwidget);
        curr_label->setObjectName(QString::fromUtf8("curr_label"));
        curr_label->setGeometry(QRect(580, 30, 131, 21));
        labelUserName = new QLabel(centralwidget);
        labelUserName->setObjectName(QString::fromUtf8("labelUserName"));
        labelUserName->setGeometry(QRect(740, 20, 151, 41));
        sendBtn = new QPushButton(centralwidget);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));
        sendBtn->setGeometry(QRect(650, 470, 71, 81));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(50, 80, 761, 371));
        inputLine = new QLineEdit(centralwidget);
        inputLine->setObjectName(QString::fromUtf8("inputLine"));
        inputLine->setGeometry(QRect(150, 470, 501, 81));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(92, 21, 171, 31));
        QFont font;
        font.setPointSize(14);
        lineEdit->setFont(font);
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(330, 20, 121, 31));
        QFont font1;
        font1.setPointSize(16);
        lineEdit_2->setFont(font1);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 61, 31));
        QFont font2;
        font2.setPointSize(11);
        label->setFont(font2);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(290, 20, 41, 31));
        label_2->setFont(font2);
        Client->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Client);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 857, 22));
        Client->setMenuBar(menubar);
        statusbar = new QStatusBar(Client);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Client->setStatusBar(statusbar);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        curr_label->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214:", nullptr));
        labelUserName->setText(QCoreApplication::translate("MainWindow", "\320\235\320\265\321\202", nullptr));
        sendBtn->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        inputLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\262\320\276\321\221 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "55555", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Ip \320\260\320\264\321\200\320\265\321\201", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
