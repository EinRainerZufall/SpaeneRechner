#include "mainwindow.h"
#include "ui_mainwindow.h"


//Module Laden
#include "Modules/settings.cpp"
#include "Modules/simple.cpp"
#include "Modules/dynamic.cpp"
#include "Modules/slot.cpp"
#include "Modules/plan90.cpp"
#include "Modules/plan45.cpp"
#include "Modules/drill.cpp"
#include "Modules/createDatabase.cpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1000,700);
    this->setCentralWidget(ui->tabWidget);


    //Release things
    ui->tabWidget->setTabVisible(1, false);
    ui->tabWidget->setTabVisible(2, false);
    ui->tabWidget->setTabVisible(3, false);
    ui->tabWidget->setTabVisible(4, false);
    ui->tabWidget->setTabVisible(5, false);
    ui->tabWidget->setTabVisible(6, false);
    ui->tabWidget->setTabVisible(7, false);
    ui->tabWidget->setTabVisible(8, false);
    ui->tabWidget->setCurrentIndex(0);


    //check if the xlsx exist
    if(Settings::xlsxCheck()) {
        createDatabase::createSimple();
        //createDatabase::createDynamic();
        //createDatabase::createSlot();
        //createDatabase::createPlan90();
        //createDatabase::createPlan45();
        //createDatabase::createDrill();

        createDatabase::createSettings();
    }
    //Disclaimer
    Settings::showDis();
    //Einstellungen Lesen
    //max RPM
    ui->MaxDrehzahlAuswahlEinfach->setValue(Settings::maxRpm());
    ui->MaxDrehzahlAuswahlTpc->setValue(Settings::maxRpm());
    ui->MaxDrehzahlAuswahlBohren->setValue(Settings::maxRpm());
    ui->MaxDrehzahlAuswahlNut->setValue(Settings::maxRpm());
    ui->MaxDrehzahlAuswahlPlan->setValue(Settings::maxRpm());
    //mashine condition
    switch (Settings::condition()) {
    case 2:
        ui->BeStabilTpc->setChecked(true);
        ui->BeStabilNut->setChecked(true);
        ui->BeStabilPlan->setChecked(true);
        ui->BeStabilBohren->setChecked(true);
        break;
    case 1:
        ui->BeNormalTpc->setChecked(true);
        ui->BeNormalNut->setChecked(true);
        ui->BeNormalPlan->setChecked(true);
        ui->BeNormalBohren->setChecked(true);
        break;
    case 0:
        ui->BeInstabilTpc->setChecked(true);
        ui->BeInstabilNut->setChecked(true);
        ui->BeInstabilPlan->setChecked(true);
        ui->BeInstabilBohren->setChecked(true);
        break;
    }
    //cuting material  
    switch (Settings::cutMat()) {
    case 2:
        ui->SchnKeramikTpc->setChecked(true);
        ui->SchnKeramikNut->setChecked(true);
        ui->SchnKeramikPlan->setChecked(true);
        ui->SchnKeramikBohren->setChecked(true);
        break;
    case 1:
        ui->SchnVhmTpc->setChecked(true);
        ui->SchnVhmNut->setChecked(true);
        ui->SchnVhmPlan->setChecked(true);
        ui->SchnVhmBohren->setChecked(true);
        break;
    case 0:
        ui->SchnHssTpc->setChecked(true);
        ui->SchnHssNut->setChecked(true);
        ui->SchnHssPlan->setChecked(true);
        ui->SchnHssBohren->setChecked(true);
        break;
    }
    //drill angle
    switch (Settings::angleDrill()) {
    case 2:
        ui->SpitzenWinkel140->setChecked(true);
        break;
    case 1:
        ui->SpitzenWinkel130->setChecked(true);
        break;
    case 0:
        ui->SpitzenWinkel118->setChecked(true);
        break;
    }
    //cooling solution
    switch (Settings::cooling()) {
    case 2:
        ui->OilTpc->setChecked(true);
        ui->OilNut->setChecked(true);
        ui->OilPlan->setChecked(true);
        ui->OilBohren->setChecked(true);
        break;
    case 1:
        ui->KssTpc->setChecked(true);
        ui->KssNut->setChecked(true);
        ui->KssPlan->setChecked(true);
        ui->KssBohren->setChecked(true);
        break;
    case 0:
        ui->TrockenTpc->setChecked(true);
        ui->TrockenNut->setChecked(true);
        ui->TrockenPlan->setChecked(true);
        ui->TrockenBohren->setChecked(true);
        break;
    }

    //simple calc
    ui->MaterialAuswahlEinfach->addItems(Simple::matList());
    ui->FraeserDurchmesserAuswahlEinfach->addItems(Simple::dList());

    //dynamic calc
    //ui->MaterialAuswahlTpc->addItems(Dynamic::matList());

    //Slot calc
    //ui->MaterialAuswahlNut->addItems(Slot::matList());

    //Plan90 calc
    //ui->MaterialAuswahlPlan->addItems(Plan90::matList());

    //Drill calc
    //ui->MaterialAuswahlBohren->addItems(Drill::matList());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_MaterialAuswahlEinfach_currentIndexChanged(int index)
{
    ui->VcOutEinfach->setText(QString::number(Simple::Vc(index)) + " m/min");
}


void MainWindow::on_BtnCalcEinfach_clicked()
{
    const double pi = M_PI;
    double D = (ui->FraeserDurchmesserAuswahlEinfach->currentText()).toDouble();
    int N;
    int maxN = ui->MaxDrehzahlAuswahlEinfach->value();
    int z = ui->SchneidenAuswahlEinfach->value();
    int Vc = Simple::Vc(ui->MaterialAuswahlEinfach->currentIndex());
    double fz = Simple::fz(ui->FraeserDurchmesserAuswahlEinfach->currentIndex(),ui->MaterialAuswahlEinfach->currentIndex());

    N = (Vc * 1000) / (pi * D);
    if(N > maxN) {
        N = maxN;
    }

    ui->RealVcOutEinfach->setText(QString::number(round((N * pi * D) / 1000)) + " m/min");

    ui->DrehzahlOutEinfach->setText(QString::number(N));
    ui->VorschubOutEinfach->setText(QString::number(N * z * fz) + " mm/min");
    ui->EintauchVorschubOutEinfach->setText(QString::number(round((N * z * fz) * 0.333)) + " mm/min");

    ui->ApNutAluOutEinfach->setText(QString::number(D * 0.5) + " mm");
    ui->ApNutHolzOutEinfach->setText(QString::number(D) + " mm");
    ui->ApNutKunststoffOutEinfach->setText(QString::number(D * 2) + " mm");
    ui->ApTpcAluOutEinfach->setText(QString::number(D * 2) + " mm");
    ui->AeAluOutEinfach->setText(QString::number(D * 0.125) + " mm");
    ui->AeTpcAluOutEinfach->setText(QString::number(D * 0.2) + " mm");
}

void MainWindow::on_btnEmail_clicked()
{
    QDesktopServices::openUrl(QUrl("mailto:?to=info@spaenerechner.de&subject=Betreff&body=Hi, \nich habe folgendes Problem...", QUrl::TolerantMode));
    //this->setStyleSheet("color: hotpink");
}


void MainWindow::on_btnGit_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/EinRainerZufall/SpaeneRechner/issues", QUrl::TolerantMode));
}


void MainWindow::on_btnXlnt_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/tfussell/xlnt", QUrl::TolerantMode));
}


void MainWindow::on_btnQT_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.qt.io/", QUrl::TolerantMode));
}


void MainWindow::on_btnCreateAll_clicked()
{
    createDatabase::createSimple();
    createDatabase::createSettings();
}

