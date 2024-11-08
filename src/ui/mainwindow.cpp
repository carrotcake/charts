#include "mainwindow.h"
#include <QString>
#include <QFile>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_midi(this)
    , m_chord(this) {
    ui->setupUi(this);
    ui->qualityButtons->setId(ui->qualMajBtn, Chord::maj);
    ui->qualityButtons->setId(ui->qualMinBtn, Chord::min);
    ui->qualityButtons->setId(ui->qualDomBtn, Chord::dom);
    ui->qualityButtons->setId(ui->qualDimBtn, Chord::dim);
    ui->qualityButtons->setId(ui->qualMinMajBtn, Chord::minMaj);
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
    connect(&start, &StartupWindow::windowClosed, this, &MainWindow::on_start_windowClosed);
    connect(this, &MainWindow::chordPreviewed, &m_midi, &MIDIController::requestPreview);
    connect(&m_chord, &WorkingChord::rebuilt, this, &MainWindow::updateChord);
    //m_midi.blockSignals(true);
}

void MainWindow::startUp() {
    start.show();
    this->setDisabled(true);
}

void MainWindow::on_start_windowClosed(int) {
    m_midi.blockSignals(true);
    ui->customRootCBox->setCurrentIndex(Notes::NOTE_Bflat);
    m_chord.setBass(Notes::NOTES[Notes::NOTE_Bflat]);
    ui->qualMajBtn->setChecked(true);
    ui->ext5Btn->setChecked(true);
    ui->altAdd13CBtn->setCheckState(Qt::Checked);
    this->setDisabled(false);
    m_midi.blockSignals(false);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::updateChord(){
    this->blockSignals(true);
    ui->alterationButtons->blockSignals(true);
    for (size_t i = 0; i < Chord::ALTCOUNT; ++i) {
        auto alt = static_cast<Chord::alteration>(i);
        bool canAdd = m_chord.canAddAlteration(alt);
        bool hasAlt = m_chord.hasAlteration(alt) && canAdd;
        ui->alterationButtons->button(i)->setChecked(hasAlt);
        ui->alterationButtons->button(i)->setEnabled(canAdd);
    }
    ui->alterationButtons->blockSignals(false);
    this->blockSignals(false);
    ui->chordNameTxt->setText(QString::fromStdString(m_chord.name()));
    emit chordPreviewed(m_chord);
}

void MainWindow::on_qualityButtons_buttonClicked(QAbstractButton *btn) {
    auto qual = static_cast<Chord::quality>(ui->qualityButtons->id(btn));
    m_chord.setQuality(qual);
}

void MainWindow::on_extensionButtons_buttonClicked(QAbstractButton *btn) {
    auto ext = static_cast<Chord::extension>(ui->extensionButtons->id(btn));
    m_chord.setExtension(ext);
}

void MainWindow::on_alterationButtons_buttonToggled(QAbstractButton *btn, bool checked) {
    auto alt = static_cast<Chord::alteration>(ui->alterationButtons->id(btn));
    if (checked)
        m_chord.addAlteration(alt);
    else
        m_chord.removeAlteration(alt);
}

void MainWindow::on_customRootCBox_currentIndexChanged(int index) {
    auto val = static_cast<Notes::Value>(ui->customRootCBox->itemData(index).toUInt());
    m_chord.blockSignals(true);
    m_chord.setRoot(Notes::NOTES[val]);
    ui->bassAnyNoteCBox->setCurrentIndex(-1);
    m_chord.blockSignals(false);
    m_chord.setBass(Notes::NOTES[val]);
}

void MainWindow::on_bassAnyNoteCBox_currentIndexChanged(int index) {
    auto val = static_cast<Notes::Value>(ui->bassAnyNoteCBox->itemData(index).toUInt());
    m_chord.setBass(Notes::NOTES[val]);
}


void MainWindow::on_chordPreviewBtn_pressed(){
    emit chordPreviewed(m_chord);
}
