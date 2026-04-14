#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QNetworkAccessManager>
#include <QtConcurrent>
#include <QFutureWatcher>
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
    void on_actionCheckAll_triggered();
    void on_editSearch_textChanged(const QString &text);
    void on_actionNew_triggered();
    void on_actionDelete_triggered();
    void on_btnSave_clicked();
    void onScanFinished();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QFutureWatcher<void> watcher;
    void setupTable();
    void loadData();
};
#endif
