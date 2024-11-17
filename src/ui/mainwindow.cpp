#include "mainwindow.h"
#include <QString>
#include <QFile>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui(new Ui::MainWindow)
    , m_midi(this)
    , m_chord(this)
    , chart(this) {
    ui->setupUi(this);

    ui->qualityButtons->setId(ui->qualMajBtn, Chords::maj);
    ui->qualityButtons->setId(ui->qualMinBtn, Chords::min);
    ui->qualityButtons->setId(ui->qualDomBtn, Chords::dom);
    ui->qualityButtons->setId(ui->qualDimBtn, Chords::dim);
    ui->qualityButtons->setId(ui->qualMinMajBtn, Chords::minMaj);
    ui->qualityButtons->setExclusive(true);

    ui->extensionButtons->setId(ui->ext5Btn, Chords::triad);
    ui->extensionButtons->setId(ui->ext7Btn, Chords::seven);
    ui->extensionButtons->setId(ui->ext9Btn, Chords::nine);
    ui->extensionButtons->setId(ui->ext11Btn, Chords::eleven);
    ui->extensionButtons->setId(ui->ext13Btn, Chords::thirteen);
    ui->extensionButtons->setExclusive(true);

    ui->alterationButtons->setId(ui->altNo3CBtn, Chords::no3);
    ui->alterationButtons->setId(ui->altNo5CBtn, Chords::no5);
    ui->alterationButtons->setId(ui->altFlat5CBtn, Chords::flat5);
    ui->alterationButtons->setId(ui->altSharp5CBtn, Chords::sharp5);
    ui->alterationButtons->setId(ui->altSus2CBtn, Chords::sus2);
    ui->alterationButtons->setId(ui->altSus4CBtn, Chords::sus4);
    ui->alterationButtons->setId(ui->altFlat9CBtn, Chords::flat9);
    ui->alterationButtons->setId(ui->altSharp9CBtn, Chords::sharp9);
    ui->alterationButtons->setId(ui->altAdd13CBtn, Chords::add13);
    ui->alterationButtons->setId(ui->altAdd9CBtn, Chords::add9);
    ui->alterationButtons->setId(ui->altSharp11CBtn, Chords::sharp11);
    ui->alterationButtons->setId(ui->altAdd11CBtn, Chords::add11);
    ui->alterationButtons->setId(ui->altFlat13CBtn, Chords::flat13);
    ui->alterationButtons->setExclusive(false);

    for (uint i = 0; i < Notes::COUNT; i++) {
        ui->customRootCBox->addItem(QString::fromStdString(Notes::str_BOTHNAMES[i]), i);
        ui->bassAnyNoteCBox->addItem(QString::fromStdString(Notes::str_BOTHNAMES[i]), i);
    }
    ui->bassAnyNoteCBox->setCurrentIndex(-1);
    ui->chartWidget->setScene(&chart.view());

    connect(&chart, &Chart::chordClicked, this, &MainWindow::changeWorkingChord);
    connect(&start, &StartupWindow::windowClosed, this, &MainWindow::on_start_windowClosed);
    connect(this, &MainWindow::chordPreviewed, &m_midi, &MIDIController::requestPreview);
    connect(&m_chord, &WorkingChord::rebuilt, this, &MainWindow::updateChord);
    connect(ui->actionExit_Charts, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::startUp() {
    start.show();
    chart.init();
    this->setDisabled(true);
}

void MainWindow::on_start_windowClosed(int) {
    m_midi.blockSignals(true);
    ui->customRootCBox->setCurrentIndex(Notes::NOTE_Bflat);
    m_chord.setBass(Notes::NOTES[Notes::NOTE_Bflat]);
    ui->qualMajBtn->setChecked(true);
    ui->ext5Btn->setChecked(true);
    ui->altAdd13CBtn->setCheckState(Qt::Checked);
    ui->chartWidget->show();
    this->setDisabled(false);
    m_midi.blockSignals(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::changeWorkingChord(const WorkingChord &chord) {
    m_chord.set(chord.chord());
}

void MainWindow::updateChord() {
    const auto qual = m_chord.qual();
    const auto ext = m_chord.extensionLevel();
    const auto rootVal = m_chord.root().val;
    const auto bassVal = m_chord.bass().val;
    const auto namestr = QString::fromStdString(m_chord.name());

    this->blockSignals(true);
    ui->alterationButtons->blockSignals(true);
    ui->qualityButtons->blockSignals(true);
    ui->customRootCBox->blockSignals(true);
    ui->bassAnyNoteCBox->blockSignals(true);
    auto chordblock = m_chord.blockSignals(true);
    auto midiblock = m_midi.blockSignals(true);

    ui->qualityButtons->button(qual)->setChecked(true);
    ui->extensionButtons->button(ext)->setChecked(true);
    ui->customRootCBox->setCurrentIndex(rootVal);
    ui->bassAnyNoteCBox->setCurrentIndex(bassVal);
    for (size_t i = 0; i < Chords::ALTCOUNT; ++i) {
        const auto alt = static_cast<Chords::alteration>(i);
        bool canAdd = m_chord.canAddAlteration(alt);
        bool hasAlt = m_chord.hasAlteration(alt) && canAdd;
        ui->alterationButtons->button(i)->setChecked(hasAlt);
        ui->alterationButtons->button(i)->setEnabled(canAdd);
    }
    ui->chordNameTxt->setText(namestr);

    ui->qualityButtons->blockSignals(false);
    ui->customRootCBox->blockSignals(false);
    ui->bassAnyNoteCBox->blockSignals(false);
    m_midi.blockSignals(midiblock);
    m_chord.blockSignals(chordblock);
    ui->alterationButtons->blockSignals(false);
    this->blockSignals(false);
    emit chordPreviewed(m_chord);
}

void MainWindow::on_qualityButtons_buttonClicked(QAbstractButton *btn) {
    auto qual = static_cast<Chords::quality>(ui->qualityButtons->id(btn));
    m_chord.setQuality(qual);
}

void MainWindow::on_extensionButtons_buttonClicked(QAbstractButton *btn) {
    auto ext = static_cast<Chords::extension>(ui->extensionButtons->id(btn));
    m_chord.setExtension(ext);
}

void MainWindow::on_alterationButtons_buttonToggled(QAbstractButton *btn, bool checked) {
    auto alt = static_cast<Chords::alteration>(ui->alterationButtons->id(btn));
    if (checked)
        m_chord.addAlteration(alt);
    else
        m_chord.removeAlteration(alt);
}

void MainWindow::on_customRootCBox_currentIndexChanged(int index) {
    auto val = static_cast<Notes::Value>(ui->customRootCBox->itemData(index).toUInt());
    auto blocked = m_chord.blockSignals(true);
    m_chord.setRoot(Notes::NOTES[val]);
    ui->bassAnyNoteCBox->setCurrentIndex(-1);
    m_chord.blockSignals(blocked);
    m_chord.setBass(Notes::NOTES[val]);
}

void MainWindow::on_bassAnyNoteCBox_currentIndexChanged(int index) {
    auto val = static_cast<Notes::Value>(ui->bassAnyNoteCBox->itemData(index).toUInt());
    m_chord.setBass(Notes::NOTES[val]);
}


void MainWindow::on_chordPreviewBtn_pressed(){
    emit chordPreviewed(m_chord);
}

void MainWindow::on_addChordBtn_clicked() {
    chart.setChord(m_chord.chord(), chart.selected());
}
