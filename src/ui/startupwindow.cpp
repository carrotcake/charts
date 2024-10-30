#include "startupwindow.h"
#include "ui_startupwindow.h"

StartupWindow::StartupWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartupWindow) {
    ui->setupUi(this);
}

void StartupWindow::on_StartupWindow_finished(int result) {
    emit windowClosed(result);
}

StartupWindow::~StartupWindow() {
    delete ui;
}
