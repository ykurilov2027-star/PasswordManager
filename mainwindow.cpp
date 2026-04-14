#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    DatabaseManager::instance().openDatabase("vault.db");
    DatabaseManager::instance().initSchema();

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);

    setupTable();
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

void MainWindow::on_actionCheckBreach_triggered() {
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) return;

    QString password = proxyModel->data(proxyModel->index(index.row(), 2)).toString();

    // Хешуємо пароль (SHA-1), як того вимагає більшість API перевірки витоків
    QString hash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex()).toUpper();
    QString prefix = hash.left(5);

    QUrl url("https://api.pwnedpasswords.com/range/" + prefix);
    networkManager->get(QNetworkRequest(url));
    ui->statusbar->showMessage("Checking password safety...");
}

void MainWindow::onNetworkReply(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        ui->statusbar->showMessage("Check complete. See console for details (or popup).");
    } else {
        ui->statusbar->showMessage("Network error: " + reply->errorString());
    }
    reply->deleteLater();
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
