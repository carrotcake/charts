#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include "src/music/chord.h"
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

private slots:
    void on_qualityButtons_buttonClicked(QAbstractButton *btn);
    void on_extensionButtons_buttonClicked(QAbstractButton *btn);
    void on_alterationButtons_buttonToggled(QAbstractButton *btn, bool checked);

    void on_customRootCBox_currentIndexChanged(int index);
    void on_bassAnyNoteCBox_currentIndexChanged(int index);

    void on_chordPreviewBtn_clicked();

private:
    Chord chord;
    Ui::MainWindow *ui;
    StartupWindow start;
};
#endif // MAINWINDOW_H
