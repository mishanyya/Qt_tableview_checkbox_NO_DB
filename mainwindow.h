#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QMainWindow"
#include "QtSql"
#include "QSqlDatabase"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();

private:
Ui::MainWindow *ui;

private slots:
void tableviewfunction();//основная функция, выводящая таблицу в tableView

void forworktableview();//получение индекса ячейки в tablevidget через checkbox или radiobutton

};
#endif // MAINWINDOW_Hsss
