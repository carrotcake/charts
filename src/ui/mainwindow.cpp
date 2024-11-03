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
    chord.setRoot(Notes::C);
    chord.setExtension(Chord::triad);
    chord.addAlteration(Chord::add13);
    chord.addAlteration(Chord::add9);
    ui->label->setText(QString::fromStdString(chord.name()));
    this->setDisabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}
