#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    if (DatabaseManager::instance().openDatabase("vault.db")) {
        DatabaseManager::instance().initSchema();
    }

    setupTable();
    loadData();

    connect(ui->editSearch, &QLineEdit::textChanged, this, &MainWindow::on_editSearch_textChanged);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::on_btnClear_clicked);
}

MainWindow::~MainWindow() {
    syncToDatabase();
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
    proxyModel->setFilterKeyColumn(-1);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

void MainWindow::on_btnClear_clicked() {
    ui->editSearch->clear();
}

void MainWindow::on_actionNew_triggered() {
    model->appendRow({
        new QStandardItem("New Service"),
        new QStandardItem("user@mail.com"),
        new QStandardItem("password"),
        new QStandardItem("https://"),
        new QStandardItem("")
    });
}

void MainWindow::on_actionDelete_triggered() {
    QModelIndex proxyIndex = ui->tableView->currentIndex();
    if (proxyIndex.isValid()) {
        QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);
        model->removeRow(sourceIndex.row());
    }
}

void MainWindow::syncToDatabase() {
    QSqlQuery query;
    query.exec("DELETE FROM credentials");
    for (int i = 0; i < model->rowCount(); ++i) {
        query.prepare("INSERT INTO credentials (service, username, password, url, notes) VALUES (?, ?, ?, ?, ?)");
        for(int j=0; j<5; j++) query.addBindValue(model->item(i, j)->text());
        query.exec();
    }
}
