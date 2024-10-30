#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "startupwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startUp();

public slots:
    void on_start_windowClosed(int result);

private:
    Ui::MainWindow *ui;
    StartupWindow start;
};
#endif // MAINWINDOW_H
