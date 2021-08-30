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
//    ui->tabWidget->setTabVisible(1, false);   //Dynamisch
    ui->tabWidget->setTabVisible(2, false);   //Nutfraesen
    ui->tabWidget->setTabVisible(3, false);   //Planfraesen
//    ui->tabWidget->setTabVisible(4, false);   //Bohren
    ui->tabWidget->setTabVisible(5, false);   //Laengsdrehen
    ui->tabWidget->setTabVisible(6, false);   //Plandrehen
    ui->tabWidget->setTabVisible(7, false);   //Gewinde
    ui->tabWidget->setTabVisible(8, false);   //Extras
    ui->tabWidget->setCurrentIndex(0);


    //check if the xlsx exist
    if(Settings::xlsxCheck()) {
        createDatabase::createSimple();
        createDatabase::createDynamic();
        createDatabase::createDrill();
        //createDatabase::createSlot();
        //createDatabase::createPlan90();
        //createDatabase::createPlan45();

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
        ui->SchnVhmBohren->setChecked(true);
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
    ui->MaterialAuswahlTpc->addItems(Dynamic::matList());

    //Slot calc
    //ui->MaterialAuswahlNut->addItems(Slot::matList());

    //Plan90 calc
    //ui->MaterialAuswahlPlan->addItems(Plan90::matList());

    //Drill calc
    ui->MaterialAuswahlBohren->addItems(Drill::matList());
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
    double Vc = Simple::Vc(ui->MaterialAuswahlEinfach->currentIndex());
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
    createDatabase::createDynamic();
    createDatabase::createDrill();

    createDatabase::createSettings();
}


void MainWindow::on_BtnCalcTpc_clicked()
{
    const double pi = M_PI;
    double D = ui->FraeserdurchmesserAuswahlTpc->value();
    double ap = ui->ApAuswahlTpc->value();
    int maxN = ui->MaxDrehzahlAuswahlTpc->value();
    int z = ui->SchneidenAuswahlTpc->value();
    int Kc = Dynamic::Kc(ui->MaterialAuswahlTpc->currentIndex());
    double Mc = Dynamic::Mc(ui->MaterialAuswahlTpc->currentIndex());
    int maxKw = Settings::maxKw();
    double C4 = 1.5;  //Verschleiss
    double C1;        //Kuehlung
    double C2;        //Schneidstoff
    double C3;        //Vc
    double Vc;
    double fz;
    double ae;
    double Pc;
    double def;
    int eTool;
    int N;

    if(ui->BeStabilTpc->isChecked()) {
        Vc = Dynamic::Vc(ui->MaterialAuswahlTpc->currentIndex(), 2);
        fz = Dynamic::fz(ui->MaterialAuswahlTpc->currentIndex(), 2, D);
        ae = Dynamic::ae(ui->MaterialAuswahlTpc->currentIndex(), 2, D);
    }else if (ui->BeNormalTpc->isChecked()) {
        Vc = Dynamic::Vc(ui->MaterialAuswahlTpc->currentIndex(), 1);
        fz = Dynamic::fz(ui->MaterialAuswahlTpc->currentIndex(), 1, D);
        ae = Dynamic::ae(ui->MaterialAuswahlTpc->currentIndex(), 1, D);
    }else {
        Vc = Dynamic::Vc(ui->MaterialAuswahlTpc->currentIndex(), 0);
        fz = Dynamic::fz(ui->MaterialAuswahlTpc->currentIndex(), 0, D);
        ae = Dynamic::ae(ui->MaterialAuswahlTpc->currentIndex(), 0, D);
    }

    if(ui->OilTpc->isChecked()) {
        C1 = 0.85;
    }else if (ui->KssTpc->isChecked()) {
        C1 = 0.9;
    }else {
        C1 = 1;
    }

    if(ui->SchnKeramikTpc->isChecked()) {
        C2 = 0.9;
        eTool = 300; //???
    }else if (ui->SchnVhmTpc->isChecked()) {
        C2 = 1;
        eTool = 300;
    }else {
        C2 = 1.2;
        eTool = 200;
    }

    if(Vc > 250) {
        C3 = pow((100 / Vc), 0.1);
    }else if(Vc > 80) {
        C3 = 1.03 - ((3 * Vc) / pow(10, 4));
    }else {
        C3 = 1.15;
    }

    N = (Vc * 1000) / (pi * D);
    if(N > maxN) {
        N = maxN;
    }

    //tpcPc = tpcZ * (90 + Math.Asin((tpcAe - (tpcFd / 2)) / (tpcFd / 2))) / 360 * (tpcKc / (tpcFz ^ tpcMc) * (tpcAp * tpcFz) * tpcC1 * tpcC2) * tpcVc / 60 / 85 / 1000
    Pc = z * (90 + asin((ae - (D / 2)) / (D / 2))) / 360 * (Kc / pow(fz, Mc) * (ap * fz) * C1 * C2 * C3 * C4) * Vc / 60 / 85 / 1000;

    double Fcut = Pc * ((2 * (maxKw * 1000)) / (D * N));
    def = (Fcut * pow((ap + 10), 3)) / (3 * eTool * 0.66 * (pow(D, 4) / 64));

    ui->RealVcOutTpc->setText(QString::number(round((N * pi * D) / 1000)) + " m/min");

    ui->DrehzahlOutTpc->setText(QString::number(N));
    ui->VorschubOutTpc->setText(QString::number(N * z * fz) + " mm/min");
    ui->AeOutTpc->setText(QString::number(ae) + " mm");
    ui->QOutTpc->setText(QString::number(ap * ae * (N * z * fz) / 1000) + " cm³/min");
    ui->PcOutTpc->setText(QString::number(Pc, 'g', 1) + " kW");
    ui->DeflevtionOutTpc->setText(QString::number(def, 'g', 1) + " mm");
}


void MainWindow::on_MaterialAuswahlTpc_currentIndexChanged(int index)
{
    if(ui->BeStabilTpc->isChecked()) {
        ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 2)) + " m/min");
    }else if (ui->BeNormalTpc->isChecked()) {
        ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 1)) + " m/min");
    }else {
        ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 0)) + " m/min");
    }
}

void MainWindow::on_FraeserdurchmesserAuswahlTpc_valueChanged(double arg1)
{
    ui->ApAuswahlTpc->setValue(arg1 * 2);
}


void MainWindow::on_BeInstabilTpc_clicked()
{
    int index = ui->MaterialAuswahlTpc->currentIndex();
    ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 0)) + " m/min");
}


void MainWindow::on_BeNormalTpc_clicked()
{
    int index = ui->MaterialAuswahlTpc->currentIndex();
    ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 1)) + " m/min");
}


void MainWindow::on_BeStabilTpc_clicked()
{
    int index = ui->MaterialAuswahlTpc->currentIndex();
    ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 2)) + " m/min");
}


void MainWindow::on_MaterialAuswahlBohren_currentIndexChanged(int index)
{
    int bed;
    int schn;

    if(ui->BeStabilBohren->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalBohren->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    if(ui->SchnVhmBohren->isChecked()) {
        schn = 1;
    }else {
        schn = 0;
    }

    ui->VcOutBohren->setText(QString::number(Drill::Vc(index, bed, schn)) + " m/min");
}


void MainWindow::on_BeInstabilBohren_clicked()
{
    int bed;
    int schn;

    if(ui->BeStabilBohren->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalBohren->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    if(ui->SchnVhmBohren->isChecked()) {
        schn = 1;
    }else {
        schn = 0;
    }

    ui->VcOutBohren->setText(QString::number(Drill::Vc(ui->MaterialAuswahlBohren->currentIndex(), bed, schn)) + " m/min");
}


void MainWindow::on_BeNormalBohren_clicked()
{
    int bed;
    int schn;

    if(ui->BeStabilBohren->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalBohren->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    if(ui->SchnVhmBohren->isChecked()) {
        schn = 1;
    }else {
        schn = 0;
    }

    ui->VcOutBohren->setText(QString::number(Drill::Vc(ui->MaterialAuswahlBohren->currentIndex(), bed, schn)) + " m/min");
}


void MainWindow::on_BeStabilBohren_clicked()
{
    int bed;
    int schn;

    if(ui->BeStabilBohren->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalBohren->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    if(ui->SchnVhmBohren->isChecked()) {
        schn = 1;
    }else {
        schn = 0;
    }

    ui->VcOutBohren->setText(QString::number(Drill::Vc(ui->MaterialAuswahlBohren->currentIndex(), bed, schn)) + " m/min");
}


void MainWindow::on_SchnHssBohren_clicked()
{
    int bed;
    int schn;

    if(ui->BeStabilBohren->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalBohren->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    if(ui->SchnVhmBohren->isChecked()) {
        schn = 1;
    }else {
        schn = 0;
    }

    ui->VcOutBohren->setText(QString::number(Drill::Vc(ui->MaterialAuswahlBohren->currentIndex(), bed, schn)) + " m/min");
}


void MainWindow::on_SchnVhmBohren_clicked()
{
    int bed;
    int schn;

    if(ui->BeStabilBohren->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalBohren->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    if(ui->SchnVhmBohren->isChecked()) {
        schn = 1;
    }else {
        schn = 0;
    }

    ui->VcOutBohren->setText(QString::number(Drill::Vc(ui->MaterialAuswahlBohren->currentIndex(), bed, schn)) + " m/min");
}


void MainWindow::on_BtnCalcBohren_clicked()
{
    const double pi = M_PI;
    double D = ui->FraeserdurchmesserAuswahlBohren->value();
    int maxN = ui->MaxDrehzahlAuswahlBohren->value();
    double fu = Drill::fu(ui->MaterialAuswahlBohren->currentIndex(), D);
    int Kc = Drill::Kc(ui->MaterialAuswahlBohren->currentIndex());
    double Mc = Drill::Mc(ui->MaterialAuswahlBohren->currentIndex());
    double C4 = 1.3;  //Verschleiss
    double C1;        //Kuehlung
    double C2;        //Schneidstoff
    double C3;        //Vc
    double Vc;
    double Pc;
    double h;
    int N;
    int spWi;
    int schn;
    int bed;

    if(ui->BeStabilBohren->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalBohren->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    if(ui->SchnVhmBohren->isChecked()) {
        schn = 1;
        C2 = 1;
    }else {
        schn = 0;
        C2 = 1.2;
    }

    if(ui->SpitzenWinkel140->isChecked()) {
        spWi = 140;
    }else if(ui->SpitzenWinkel130->isChecked()) {
        spWi = 130;
    }else {
        spWi = 118;
    }

    Vc = Drill::Vc(ui->MaterialAuswahlBohren->currentIndex(), bed, schn);

    N = (Vc * 1000) / (pi * D);
    if(N > maxN) {
        N = maxN;
    }

    if(ui->OilBohren->isChecked()) {
        C1 = 0.85;
    }else if (ui->KssBohren->isChecked()) {
        C1 = 0.9;
    }else {
        C1 = 1;
    }

    if(Vc > 250) {
        C3 = pow((100 / Vc), 0.1);
    }else if(Vc > 80) {
        C3 = 1.03 - ((3 * Vc) / pow(10, 4));
    }else {
        C3 = 1.15;
    }

    h = (fu / 2) * sin(spWi / 2);
    //(2 * ((Kc / (h ^ Mc)) * ((D * fu) / 2) * C1 * C2 * C3 * C4) * Vc) / 2 / 85 / 1000

    Pc = (2 * ((Kc / pow(h, Mc)) * ((D * fu) / 2) * C1 * C2 * C3 * C4) * Vc) / 2 / 85 / 1000;

    ui->RealVcOutBohren->setText(QString::number(round((N * pi * D) / 1000)) + " m/min");

    ui->VorschubOutBohren->setText(QString::number(fu * N) + " mm/min");
    ui->VorschubUOutBohren->setText(QString::number(fu) + " mm/U");
    ui->DrehzahlOutBohren->setText(QString::number(N));
    ui->PcOutBohren->setText(QString::number(Pc, 'g', 3) + " kW");
}

