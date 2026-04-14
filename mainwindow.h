#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QHeaderView>
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionDelete_triggered();
    void on_btnClear_clicked();
    void loadData();
    void syncToDatabase();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    void setupTable();
};
#endif
