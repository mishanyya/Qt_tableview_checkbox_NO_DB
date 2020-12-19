#include "mainwindow.h"
#include "delegate.h"
#include "QApplication"
#include "QStandardItemModel"
#include "QHeaderView"
#include "QTableView"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
