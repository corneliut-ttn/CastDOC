/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonConnect;
    QLineEdit *ip;
    QLabel *label_ip;
    QLabel *label_port;
    QLineEdit *port;
    QLabel *label_connect;
    QPushButton *pushButtonChooseFile;
    QLineEdit *file_name_box;
    QLabel *label_file;
    QLineEdit *lineEditConvertingType;
    QLabel *label_ask_conversion;
    QPushButton *pushButtonSendType;
    QTextEdit *send_msg_box;
    QTextEdit *send_msg_box_2;
    QPushButton *pushButtonSEND;
    QLineEdit *send_msg_box_3;
    QTextEdit *send_msg_box_4;
    QLineEdit *label_rcv_file;
    QTextEdit *send_msg_box_rcv_file;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(697, 484);
        MainWindow->setStyleSheet(QStringLiteral("alternate-background-color: rgb(164, 192, 218);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButtonConnect = new QPushButton(centralWidget);
        pushButtonConnect->setObjectName(QStringLiteral("pushButtonConnect"));
        pushButtonConnect->setGeometry(QRect(340, 50, 85, 29));
        pushButtonConnect->setStyleSheet(QStringLiteral("color: rgb(210, 240, 15);"));
        ip = new QLineEdit(centralWidget);
        ip->setObjectName(QStringLiteral("ip"));
        ip->setGeometry(QRect(40, 50, 113, 29));
        ip->setStyleSheet(QLatin1String("color: rgb(227, 159, 20);\n"
"font: 75 12pt \"Cantarell\";"));
        label_ip = new QLabel(centralWidget);
        label_ip->setObjectName(QStringLiteral("label_ip"));
        label_ip->setGeometry(QRect(10, 50, 67, 21));
        label_port = new QLabel(centralWidget);
        label_port->setObjectName(QStringLiteral("label_port"));
        label_port->setGeometry(QRect(160, 50, 67, 21));
        port = new QLineEdit(centralWidget);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(210, 50, 113, 29));
        port->setStyleSheet(QLatin1String("color: rgb(19, 242, 221);\n"
"font: 75 12pt \"Cantarell\";"));
        label_connect = new QLabel(centralWidget);
        label_connect->setObjectName(QStringLiteral("label_connect"));
        label_connect->setGeometry(QRect(490, 50, 67, 21));
        label_connect->setStyleSheet(QStringLiteral("color: rgb(237, 5, 5);"));
        pushButtonChooseFile = new QPushButton(centralWidget);
        pushButtonChooseFile->setObjectName(QStringLiteral("pushButtonChooseFile"));
        pushButtonChooseFile->setEnabled(false);
        pushButtonChooseFile->setGeometry(QRect(30, 90, 85, 29));
        file_name_box = new QLineEdit(centralWidget);
        file_name_box->setObjectName(QStringLiteral("file_name_box"));
        file_name_box->setEnabled(false);
        file_name_box->setGeometry(QRect(200, 90, 451, 31));
        file_name_box->setStyleSheet(QLatin1String("color: rgb(206, 222, 30);\n"
"font: 25 11pt \"DejaVu Sans\";"));
        label_file = new QLabel(centralWidget);
        label_file->setObjectName(QStringLiteral("label_file"));
        label_file->setGeometry(QRect(120, 90, 67, 21));
        lineEditConvertingType = new QLineEdit(centralWidget);
        lineEditConvertingType->setObjectName(QStringLiteral("lineEditConvertingType"));
        lineEditConvertingType->setEnabled(false);
        lineEditConvertingType->setGeometry(QRect(210, 180, 61, 29));
        label_ask_conversion = new QLabel(centralWidget);
        label_ask_conversion->setObjectName(QStringLiteral("label_ask_conversion"));
        label_ask_conversion->setGeometry(QRect(30, 180, 161, 21));
        pushButtonSendType = new QPushButton(centralWidget);
        pushButtonSendType->setObjectName(QStringLiteral("pushButtonSendType"));
        pushButtonSendType->setEnabled(false);
        pushButtonSendType->setGeometry(QRect(310, 180, 201, 29));
        pushButtonSendType->setStyleSheet(QStringLiteral("color: rgb(192, 115, 84);"));
        send_msg_box = new QTextEdit(centralWidget);
        send_msg_box->setObjectName(QStringLiteral("send_msg_box"));
        send_msg_box->setEnabled(false);
        send_msg_box->setGeometry(QRect(20, 140, 621, 31));
        send_msg_box->setStyleSheet(QStringLiteral("color: rgb(52, 33, 33);"));
        send_msg_box_2 = new QTextEdit(centralWidget);
        send_msg_box_2->setObjectName(QStringLiteral("send_msg_box_2"));
        send_msg_box_2->setEnabled(false);
        send_msg_box_2->setGeometry(QRect(20, 220, 621, 31));
        send_msg_box_2->setStyleSheet(QStringLiteral("color: rgb(77, 37, 37);"));
        pushButtonSEND = new QPushButton(centralWidget);
        pushButtonSEND->setObjectName(QStringLiteral("pushButtonSEND"));
        pushButtonSEND->setEnabled(false);
        pushButtonSEND->setGeometry(QRect(470, 260, 171, 29));
        pushButtonSEND->setStyleSheet(QStringLiteral("color: rgb(238, 13, 13);"));
        send_msg_box_3 = new QLineEdit(centralWidget);
        send_msg_box_3->setObjectName(QStringLiteral("send_msg_box_3"));
        send_msg_box_3->setEnabled(true);
        send_msg_box_3->setGeometry(QRect(20, 260, 441, 29));
        send_msg_box_4 = new QTextEdit(centralWidget);
        send_msg_box_4->setObjectName(QStringLiteral("send_msg_box_4"));
        send_msg_box_4->setEnabled(false);
        send_msg_box_4->setGeometry(QRect(20, 300, 621, 31));
        send_msg_box_4->setStyleSheet(QStringLiteral("color: rgb(49, 142, 27);"));
        label_rcv_file = new QLineEdit(centralWidget);
        label_rcv_file->setObjectName(QStringLiteral("label_rcv_file"));
        label_rcv_file->setEnabled(false);
        label_rcv_file->setGeometry(QRect(20, 340, 611, 29));
        send_msg_box_rcv_file = new QTextEdit(centralWidget);
        send_msg_box_rcv_file->setObjectName(QStringLiteral("send_msg_box_rcv_file"));
        send_msg_box_rcv_file->setEnabled(false);
        send_msg_box_rcv_file->setGeometry(QRect(20, 370, 621, 31));
        send_msg_box_rcv_file->setStyleSheet(QStringLiteral("color: rgb(49, 142, 27);"));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 697, 26));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButtonConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        ip->setText(QApplication::translate("MainWindow", "127.0.0.1", 0));
        label_ip->setText(QApplication::translate("MainWindow", "IP:", 0));
        label_port->setText(QApplication::translate("MainWindow", "PORT:", 0));
        port->setText(QApplication::translate("MainWindow", "2809", 0));
        label_connect->setText(QString());
        pushButtonChooseFile->setText(QApplication::translate("MainWindow", "ChoseFile", 0));
        file_name_box->setText(QApplication::translate("MainWindow", "file not chosen", 0));
        label_file->setText(QApplication::translate("MainWindow", "File:", 0));
        label_ask_conversion->setText(QApplication::translate("MainWindow", "Insert Conversion Type", 0));
        pushButtonSendType->setText(QApplication::translate("MainWindow", "Send Conversion Type", 0));
        pushButtonSEND->setText(QApplication::translate("MainWindow", "SEND", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
