#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Створюємо модель на 5 колонок згідно з методичкою
    model = new QStandardItemModel(0, 5, this);
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Username");
    model->setHeaderData(2, Qt::Horizontal, "Password");
    model->setHeaderData(3, Qt::Horizontal, "URL");
    model->setHeaderData(4, Qt::Horizontal, "Notes");

    ui->tableView->setModel(model);

    // Налаштовуємо адаптивність колонок
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Початковий статус
    ui->statusbar->showMessage("Ready | Total: 0 Filtered: 0"); // [cite: 719, 720]
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionNew_triggered() {
    model->appendRow({
        new QStandardItem("New Service"),
        new QStandardItem("user@mail.com"),
        new QStandardItem("********"),
        new QStandardItem("https://..."),
        new QStandardItem("")
    });
    updateStatus();
}

void MainWindow::on_actionDelete_triggered() {
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        model->removeRow(index.row());
        updateStatus();
    }
}

void MainWindow::updateStatus() {
    int total = model->rowCount();
    ui->statusbar->showMessage(QString("Ready | Total: %1 Filtered: 0").arg(total));
}
