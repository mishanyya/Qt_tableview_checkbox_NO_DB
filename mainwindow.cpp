#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "delegate.h"

#include "QTableView"//добавлено для вывода БД в таблице
#include "QStandardItemModel"//добавлено для вывода БД в таблице
#include "QStandardItem"//добавлено для вывода БД в таблице


#include "QCheckBox"//добавлено для вывода QCheckBox в таблице
#include "QRadioButton"//добавлено для вывода QRadioButton в таблице
#include "QStyledItemDelegate"

#include "QDebug"





/*для исправления ошибки QSqlDatabasePrivate::addDatabase: duplicate connection name 'qt_sql_default_connection', old connection removed
подключать драйвер для БД (обычно доступно несколько драйверов, их список содержится в стандартном методе QSqlDatabase::drivers();)
следует в глобальной переменной static (видно везде в одном файле) или extern (видно везде во всех файлах) */
static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");// db - это статическая глобальная переменная, которую можно использовать только в этом файле

// Создаём элемент, который будет выполнять роль чекбокса,делаем его static
//static QTableWidgetItem *item = new QTableWidgetItem();

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
ui->setupUi(this);
tableviewfunction();//основная функция, выводящая таблицу в tableView
connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(forworktableview()));//получение значений всех ячеек в tableview через выбранные checkbox и radiobutton


}

MainWindow::~MainWindow()
{
delete ui;
}




void MainWindow::tableviewfunction(){//основная функция, выводящая таблицу в tableView


       QTableView *tableView = ui->tableView;
       CheckBoxDelegate *delegate = new CheckBoxDelegate();
int columndelegatenumber=0;//номер колонки для делегата

       int countrows=10;//кол-во строк
       int countcolumns=2;//кол-во колонок
       QStandardItemModel *model = new QStandardItemModel(countrows, countcolumns);
       //Заполнить таблицу данными
       for (int row =0; row < countrows; ++row) {
           for (int column = 0; column < countcolumns; ++column) {
               QModelIndex index = model->index(row, column, QModelIndex());
               if(column == columndelegatenumber)
                          {
                   model->setData(index, QVariant(0));
               //если установить значение 0 в колонку 0 - выставится НЕнажатый checkbox
               //если установить значение 1 и больше в колонку 0 - выставится нажатый checkbox
               }
                           else
                               {
                   model->setData(index, QVariant((row + 1) * (column + 1)));
               }
           }
       }

       //Устанавливаем модель в представление
       tableView->setModel(model);
              //Устанавливаем делегат в столбец
      tableView->setItemDelegateForColumn(columndelegatenumber, delegate);
       //Внешний вид представления
       tableView->resizeColumnsToContents();
       tableView->verticalHeader()->hide();
       tableView->horizontalHeader()->setStretchLastSection(true);
}


void MainWindow::forworktableview(){//получение значения ячейки в tableview через checkbox или radiobutton
int countrows=ui->tableView->model()->rowCount();
//int countcolumns=ui->tableView->model()->columnCount();

QString a[countrows];//создание массива с количеством элементов countrows

    //Получить данные
    for (int row =0; row < countrows; ++row) {
            QModelIndex index = ui->tableView->model()->index(row, 0, QModelIndex());//установка индекса - 0 колонка в каждой строке

            QVariant value=ui->tableView->model()->data(index);//поместить в переменную значение ячейки
            //так как там установлен делегат для checkbox должны быть значения
            //1 - если нажат checkbox и 0 - если не нажат checkbox
            //qDebug() << "информация = " << value;//вывод содержимого ячеек с индексом index(row, 0, QModelIndex())

            if(value==1){//если нажата галочка, внести значения в мвссив

                QModelIndex index1 = ui->tableView->model()->index(row, 1, QModelIndex());//установка индекса - 1 колонка в каждой строке
                QVariant value1=ui->tableView->model()->data(index1);//поместить в переменную значение ячейки
                qDebug() << "выбрано значение в формате QVariant = " << value1;////вывод содержимого ячеек с индексом index(row, 1, QModelIndex())

                QString x = value1.toString();//перевод из QVariant в тип  QString
                a[row]=x;//для простоты внесения в массив, используется int row, так как тоже идет по порядку
                qDebug() << "элементы массива = "<< a[row];//Вывести элементы массива
                }
            }
    }


