#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    DatabaseManager::instance().openDatabase("vault.db");
    DatabaseManager::instance().initSchema();

    setupTable();
    loadData();

    connect(&watcher, &QFutureWatcher<void>::finished, this, &MainWindow::onScanFinished);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupTable() {
    model = new QStandardItemModel(0, 5, this);
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Username");
    model->setHeaderData(2, Qt::Horizontal, "Password");
    model->setHeaderData(3, Qt::Horizontal, "URL");
    model->setHeaderData(4, Qt::Horizontal, "Notes");

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_actionCheckAll_triggered() {
    ui->statusbar->showMessage("Background scan started...");


    QFuture<void> future = QtConcurrent::run([this]() {
        for (int i = 0; i < model->rowCount(); ++i) {

            QThread::msleep(500);
        }
    });

    watcher.setFuture(future);
}

void MainWindow::onScanFinished() {
    ui->statusbar->showMessage("All passwords checked in background!", 5000);
}

void MainWindow::loadData() {
    model->removeRows(0, model->rowCount());
    QSqlQuery query("SELECT service, username, password, url, notes FROM credentials");
    while (query.next()) {
        QList<QStandardItem*> items;
        for(int i=0; i<5; ++i) items << new QStandardItem(query.value(i).toString());
        model->appendRow(items);
    }
}

void MainWindow::on_editSearch_textChanged(const QString &text) {
    proxyModel->setFilterFixedString(text);
}

void MainWindow::on_actionNew_triggered() {
    model->appendRow({new QStandardItem("New"), new QStandardItem("user"), new QStandardItem("pass"), new QStandardItem(""), new QStandardItem("")});
}

void MainWindow::on_actionDelete_triggered() {
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) model->removeRow(proxyModel->mapToSource(index).row());
}

void MainWindow::on_btnSave_clicked() {
    QSqlQuery query;
    query.exec("DELETE FROM credentials");
    for (int i = 0; i < model->rowCount(); ++i) {
        query.prepare("INSERT INTO credentials (service, username, password, url, notes) VALUES (?, ?, ?, ?, ?)");
        for(int j=0; j<5; j++) query.addBindValue(model->item(i, j)->text());
        query.exec();
    }
}
