#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QDialog>

namespace Ui {
class StartupWindow;
}

class StartupWindow : public QDialog {
    Q_OBJECT

public:
    explicit StartupWindow(QWidget *parent = nullptr);
    ~StartupWindow();

signals:
    void windowClosed(int result);

private slots:
    void on_StartupWindow_finished(int result);

private:
    Ui::StartupWindow *ui;
};

#endif // STARTUPWINDOW_H
