#pragma once

#include <QButtonGroup>
#include <QMainWindow>
#include <QThread>
#include "src/charts/chart.h"
#include "src/charts/midiplayer.h"
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

signals:
    void chordPreviewed(WorkingChord &chord);

public slots:
    void on_start_windowClosed(int result);
    void updateChord();
    void changeWorkingChord(const WorkingChord &chord);
private slots:
    void on_qualityButtons_buttonClicked(QAbstractButton *btn);
    void on_extensionButtons_buttonClicked(QAbstractButton *btn);
    void on_alterationButtons_buttonToggled(QAbstractButton *btn, bool checked);

    void on_customRootCBox_currentIndexChanged(int index);
    void on_bassAnyNoteCBox_currentIndexChanged(int index);

    void on_chordPreviewBtn_pressed();

    void on_addChordBtn_clicked();

    void on_playBtn_clicked();

    void on_stopBtn_clicked();

    void on_tempoBox_valueChanged(int arg1);

    void on_volumeSlider_valueChanged(int value);

    void on_rewindBtn_clicked();

private:
    Ui::MainWindow *ui;
    StartupWindow start;
    MIDIController m_midi;
    WorkingChord m_chord;
    Chart m_chart;
};
