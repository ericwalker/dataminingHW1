#include "qtdemo.h"


Qtdemo::Qtdemo()
{

}



//#include <QtGui/QApplication>
//#include <QtGui/QPushButton>

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    QPushButton button("Hello world");
    button.show();
    return application.exec();
}

/* 《程式語言教學誌》的範例程式
    http://pydoing.blogspot.com/
    檔名：qtdemo.cpp
    功能：示範 C++ 程式
    作者：Qt 官網 */



