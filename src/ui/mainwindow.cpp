#include "mainwindow.h"
#include <QString>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

void MainWindow::startUp() {
    connect(&start, &StartupWindow::windowClosed, this, &MainWindow::on_start_windowClosed);
    start.show();
    this->setDisabled(true);
}

void MainWindow::on_start_windowClosed(int) {
    // ui->chordEntryMainBtn->setText(QString::number(result));
    start.close();
    this->setDisabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}
