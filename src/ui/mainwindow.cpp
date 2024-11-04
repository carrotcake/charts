#include "mainwindow.h"
#include <QString>
#include <QFile>
#include "ui_mainwindow.h"
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->qualityButtons->setId(ui->qualMajBtn, Chord::maj);
    ui->qualityButtons->setId(ui->qualMinBtn, Chord::min);
    ui->qualityButtons->setId(ui->qualDomBtn, Chord::dom);
    ui->qualityButtons->setId(ui->qualDimBtn, Chord::dim);
    ui->qualityButtons->setExclusive(true);

    ui->extensionButtons->setId(ui->ext5Btn, Chord::triad);
    ui->extensionButtons->setId(ui->ext7Btn, Chord::seven);
    ui->extensionButtons->setId(ui->ext9Btn, Chord::nine);
    ui->extensionButtons->setId(ui->ext11Btn, Chord::eleven);
    ui->extensionButtons->setId(ui->ext13Btn, Chord::thirteen);
    ui->extensionButtons->setExclusive(true);

    ui->alterationButtons->setId(ui->altNo3CBtn, Chord::no3);
    ui->alterationButtons->setId(ui->altNo5CBtn, Chord::no5);
    ui->alterationButtons->setId(ui->altFlat5CBtn, Chord::flat5);
    ui->alterationButtons->setId(ui->altSharp5CBtn, Chord::sharp5);
    ui->alterationButtons->setId(ui->altSus2CBtn, Chord::sus2);
    ui->alterationButtons->setId(ui->altSus4CBtn, Chord::sus4);
    ui->alterationButtons->setId(ui->altFlat9CBtn, Chord::flat9);
    ui->alterationButtons->setId(ui->altSharp9CBtn, Chord::sharp9);
    ui->alterationButtons->setId(ui->altAdd13CBtn, Chord::add13);
    ui->alterationButtons->setId(ui->altAdd9CBtn, Chord::add9);
    ui->alterationButtons->setId(ui->altSharp11CBtn, Chord::sharp11);
    ui->alterationButtons->setId(ui->altAdd11CBtn, Chord::add11);
    ui->alterationButtons->setId(ui->altFlat13CBtn, Chord::flat13);
    ui->alterationButtons->setExclusive(false);

    for (uint i = 0; i < Notes::COUNT; i++) {
        ui->customRootCBox->addItem(QString::fromStdString(Notes::str_BOTHNAMES[i]), i);
        ui->bassAnyNoteCBox->addItem(QString::fromStdString(Notes::str_BOTHNAMES[i]), i);
    }
    ui->bassAnyNoteCBox->setCurrentIndex(-1);
    settings = new_fluid_settings();
    fluid_settings_setint(settings, "synth.polyphony", 128);
    fluid_settings_setnum(settings, "synth.gain", 1);
    synth   = new_fluid_synth(settings);
    adriver = new_fluid_audio_driver(settings, synth);
    fluid_synth_sfload(synth, "GU-GS.sf2", 1);
}

void MainWindow::startUp() {
    connect(&start, &StartupWindow::windowClosed, this, &MainWindow::on_start_windowClosed);
    start.show();
    this->setDisabled(true);
}

void MainWindow::on_start_windowClosed(int) {
    ui->customRootCBox->setCurrentIndex(Notes::NOTE_Bflat);
    chord.setBass(Notes::NOTES[Notes::NOTE_Bflat]);
    ui->qualMajBtn->setChecked(true);
    ui->ext5Btn->setChecked(true);
    ui->altAdd13CBtn->setCheckState(Qt::Checked);
    updateChord();
    this->setDisabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::updateChord(){
    for(size_t i = 0; i < Chord::ALTCOUNT; ++i)
        ui->alterationButtons->button(i)->setEnabled(chord.canAddAlteration(static_cast<Chord::alteration>(i)));
    ui->chordNameTxt->setText(QString::fromStdString(chord.name()));
}

void MainWindow::on_qualityButtons_buttonClicked(QAbstractButton *btn) {
    chord.setQuality(static_cast<Chord::quality>(ui->qualityButtons->id(btn)));
    updateChord();
}

void MainWindow::on_extensionButtons_buttonClicked(QAbstractButton *btn) {
    chord.setExtension(static_cast<Chord::extension>(ui->extensionButtons->id(btn)));
    updateChord();
}

void MainWindow::on_alterationButtons_buttonToggled(QAbstractButton *btn, bool checked) {
    if (checked)
        chord.addAlteration(static_cast<Chord::alteration>(ui->alterationButtons->id(btn)));
    else
        chord.removeAlteration(static_cast<Chord::alteration>(ui->alterationButtons->id(btn)));
    updateChord();
}

void MainWindow::on_customRootCBox_currentIndexChanged(int index) {
    auto val = static_cast<Notes::value>(ui->customRootCBox->itemData(index).toUInt());
    chord.setRoot(Notes::NOTES[val]);
    ui->bassAnyNoteCBox->setCurrentIndex(-1);
    chord.setBass(Notes::NOTES[val]);
    updateChord();
}

void MainWindow::on_bassAnyNoteCBox_currentIndexChanged(int index) {
    auto val = static_cast<Notes::value>(ui->bassAnyNoteCBox->itemData(index).toUInt());
    chord.setBass(Notes::NOTES[val]);
    updateChord();
}


void MainWindow::on_chordPreviewBtn_pressed(){
    auto &notes = chord.notes();
    for (auto note : notes) {
        fluid_synth_noteon(synth, 0, note.MIDIValue(), 100);
    }
}


void MainWindow::on_chordPreviewBtn_released(){
    fluid_synth_all_notes_off(synth, 0);
}

