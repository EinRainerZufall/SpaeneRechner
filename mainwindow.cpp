#include "mainwindow.h"
#include "ui_mainwindow.h"


//Module Laden
#include "Modules/settings.h"
#include "Modules/simple.h"
#include "Modules/dynamic.h"
#include "Modules/slot.h"
#include "Modules/plan.h"
#include "Modules/drill.h"
#include "Modules/createDatabase.h"
#include "Modules/turn.h"
#include "Modules/thread.h"


/*
 *  todo:
 *  - Extras komplett
 *  - Tabelle verbessern
 *  - Tooltips hinzufuegen
 *  - MacOS kompatibilität pruefen
 *  - Linux kompatibilität pruefen
*/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    setCursor(Qt::CursorShape::WaitCursor);

    ui->setupUi(this);
    this->setFixedSize(1000, 700);
    this->setCentralWidget(ui->mainTabWidget);

#ifdef QT_DEBUG
    //Debug things
#else
    //Release things
    //ui->mainTabWidget->setTabVisible(7, false);   //Extras
    ui->mainTabWidget->setCurrentIndex(Settings::readIndex());
#endif

    //check ob die .ini da ist
    if(!Settings::INIcheck()){
        Settings::create();
    };

    //check ob die .xlsx da ist
    if(!Settings::xlsxCheck()) {
        createDatabase::createSimple();
        createDatabase::createDynamic();
        createDatabase::createDrill();
        createDatabase::createSlot();
        createDatabase::createPlan90();
        createDatabase::createPlan45();
        createDatabase::createTurn();
        createDatabase::createThread();
    }

    //Settings::test();   // zum Testen

    //Disclaimer
    Settings::showDis();
    if(Settings::readDis()){
        ui->DisclaimerIn->setCurrentIndex(0);
    }else{
        ui->DisclaimerIn->setCurrentIndex(1);
    }

    //Einstellungen Lesen
    //max RPM
    ui->MaxDrehzahlAuswahlEinfach->setValue(Settings::maxRpmFr());
    ui->MaxDrehzahlAuswahlTpc->setValue(Settings::maxRpmFr());
    ui->MaxDrehzahlAuswahlBohren->setValue(Settings::maxRpmFr());
    ui->MaxDrehzahlAuswahlNut->setValue(Settings::maxRpmFr());
    ui->MaxDrehzahlAuswahlPlan->setValue(Settings::maxRpmFr());
    ui->MaxDrehzahlAuswahlTurn->setValue(Settings::maxRpmDr());
    ui->MaxDrehzahlAuswahlGewinde->setValue(Settings::maxRpmFr());
    ui->maxMillSpeedIn->setValue(Settings::maxRpmFr());
    ui->maxTurnSpeedIn->setValue(Settings::maxRpmDr());

    //mashine condition
    switch (Settings::condition()){
    case 2:
        ui->BeStabilTpc->setChecked(true);
        ui->BeStabilNut->setChecked(true);
        ui->BeStabilPlan->setChecked(true);
        ui->BeStabilBohren->setChecked(true);
        ui->BeStabilTurn->setChecked(true);
        ui->conditionIn->setCurrentIndex(2);
        break;
    case 1:
        ui->BeNormalTpc->setChecked(true);
        ui->BeNormalNut->setChecked(true);
        ui->BeNormalPlan->setChecked(true);
        ui->BeNormalBohren->setChecked(true);
        ui->BeNormalTurn->setChecked(true);
        ui->conditionIn->setCurrentIndex(1);
        break;
    case 0:
        ui->BeInstabilTpc->setChecked(true);
        ui->BeInstabilNut->setChecked(true);
        ui->BeInstabilPlan->setChecked(true);
        ui->BeInstabilBohren->setChecked(true);
        ui->BeInstabilTurn->setChecked(true);
        ui->conditionIn->setCurrentIndex(0);
        break;
    }
    //cuting material  
    switch (Settings::cutMat()){
    case 2:
        ui->SchnKeramikTpc->setChecked(true);
        ui->SchnKeramikNut->setChecked(true);
        ui->SchnKeramikPlan->setChecked(true);
        ui->SchnKeramikTurn->setChecked(true);
        ui->cutMatIn->setCurrentIndex(2);
        break;
    case 1:
        ui->SchnVhmTpc->setChecked(true);
        ui->SchnVhmNut->setChecked(true);
        ui->SchnVhmPlan->setChecked(true);
        ui->SchnVhmBohren->setChecked(true);
        ui->SchnVhmTurn->setChecked(true);
        ui->cutMatIn->setCurrentIndex(1);
        break;
    case 0:
        ui->SchnHssTpc->setChecked(true);
        ui->SchnHssNut->setChecked(true);
        ui->SchnHssPlan->setChecked(true);
        ui->SchnHssBohren->setChecked(true);
        ui->SchnHssTurn->setChecked(true);
        ui->cutMatIn->setCurrentIndex(0);
        break;
    }
    //drill angle
    switch (Settings::angleDrill()){
    case 2:
        ui->SpitzenWinkel140->setChecked(true);
        ui->drillAngleIn->setCurrentIndex(2);
        break;
    case 1:
        ui->SpitzenWinkel130->setChecked(true);
        ui->drillAngleIn->setCurrentIndex(1);
        break;
    case 0:
        ui->SpitzenWinkel118->setChecked(true);
        ui->drillAngleIn->setCurrentIndex(0);
        break;
    }
    //cooling solution
    switch (Settings::cooling()){
    case 2:
        ui->OilTpc->setChecked(true);
        ui->OilNut->setChecked(true);
        ui->OilPlan->setChecked(true);
        ui->OilBohren->setChecked(true);
        ui->OilTurn->setChecked(true);
        ui->coolingTypeIn->setCurrentIndex(2);
        break;
    case 1:
        ui->KssTpc->setChecked(true);
        ui->KssNut->setChecked(true);
        ui->KssPlan->setChecked(true);
        ui->KssBohren->setChecked(true);
        ui->KssTurn->setChecked(true);
        ui->coolingTypeIn->setCurrentIndex(1);
        break;
    case 0:
        ui->TrockenTpc->setChecked(true);
        ui->TrockenNut->setChecked(true);
        ui->TrockenPlan->setChecked(true);
        ui->TrockenBohren->setChecked(true);
        ui->TrockenTurn->setChecked(true);
        ui->coolingTypeIn->setCurrentIndex(0);
        break;
    }

    //simple mat
    ui->MaterialAuswahlEinfach->addItems(Simple::matList());
    ui->FraeserDurchmesserAuswahlEinfach->addItems(Simple::dList());

    //dynamic mat
    ui->MaterialAuswahlTpc->addItems(Dynamic::matList());

    //Slot mat
    ui->MaterialAuswahlNut->addItems(Slot::matList());

    //Plan90 mat
    ui->MaterialAuswahlPlan->addItems(Plan::matList(ui->SchneidenGeometryPlan->currentIndex()));

    //Drill mat
    ui->MaterialAuswahlBohren->addItems(Drill::matList());

    //Turn mat
    ui->MaterialAuswahlTurn->addItems(Turn::matList());
    ui->FraeserDurchmesserAuswahlNut->addItems(Slot::dList());

    //Thread mat
    ui->MaterialAuswahlGewinde->addItems(Thread::matList());
    ui->DurchmesserAuswahlGewinde->addItems(Thread::dList());

    //einstellungen uebernehmen
    ui->MaxMillPcIn->setValue(Settings::maxKw());
    ui->maxTurnPcIn->setValue(Settings::maxKwDr());

    //Update Check
    Settings::updateCheck();

    setCursor(Qt::CursorShape::ArrowCursor);
}

MainWindow::~MainWindow(){
    delete ui;
}


// Material Auswahl
void MainWindow::on_MaterialAuswahlEinfach_currentIndexChanged(int index){
    ui->VcOutEinfach->setText(QString::number(Simple::Vc(index)) + " m/min");
}

void MainWindow::on_MaterialAuswahlTpc_currentIndexChanged(int index){
    if(ui->BeStabilTpc->isChecked()) {
        ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 2)) + " m/min");
    }else if (ui->BeNormalTpc->isChecked()) {
        ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 1)) + " m/min");
    }else {
        ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 0)) + " m/min");
    }
}

void MainWindow::on_MaterialAuswahlNut_currentIndexChanged(int index){
    ui->VcOutNut->setText(QString::number(Slot::Vc(index)) + " m/min");
}

void MainWindow::on_MaterialAuswahlPlan_currentIndexChanged(int index){
    int bed;
    int schn = ui->SchneidenGeometryPlan->currentIndex();

    if(ui->BeStabilPlan->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalPlan->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutPlan->setText(QString::number(Plan::Vc(index, bed, schn)) + " m/min");
}

void MainWindow::on_MaterialAuswahlBohren_currentIndexChanged(int index){
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

void MainWindow::on_MaterialAuswahlTurn_currentIndexChanged(int index){
    int bed;

    if(ui->BeStabilTurn->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalTurn->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutTurn->setText(QString::number(Turn::Vc(index, bed, ui->turnstyle->currentIndex())) + " m/min");
}

void MainWindow::on_MaterialAuswahlGewinde_currentIndexChanged(int index){
    ui->VcOutGewinde->setText(QString::number(Thread::Vc(index,ui->DurchmesserAuswahlGewinde->currentIndex()))+" m/min");
}


// Durchmesser Auswahl
void MainWindow::on_FraeserdurchmesserAuswahlTpc_valueChanged(double arg1){
    ui->ApAuswahlTpc->setValue(arg1 * 2);
}

void MainWindow::on_FraeserdurchmesserAuswahlPlan_valueChanged(double arg1){
    ui->AeAuswahlPlan->setMaximum(arg1);
}

void MainWindow::on_DurchmesserAuswahlGewinde_currentIndexChanged(int index){
    ui->DurchmesserGewinde->setText(QString::number(Thread::Diameter(index))+" mm");
    ui->SteigungGewinde->setText(QString::number(Thread::threadPitch(index))+" mm");
    ui->VcOutGewinde->setText(QString::number(Thread::Vc(ui->MaterialAuswahlGewinde->currentIndex(),index))+" m/min");
}


// Btn Berrechnen
void MainWindow::on_BtnCalcEinfach_clicked(){
    const double pi = M_PI;
    double D = (ui->FraeserDurchmesserAuswahlEinfach->currentText()).toDouble();
    int N;
    int maxN = ui->MaxDrehzahlAuswahlEinfach->value();
    int z = ui->SchneidenAuswahlEinfach->value();
    double Vc = Simple::Vc(ui->MaterialAuswahlEinfach->currentIndex());
    double fz = Simple::fz(ui->FraeserDurchmesserAuswahlEinfach->currentIndex(),ui->MaterialAuswahlEinfach->currentIndex());

    setCursor(Qt::CursorShape::WaitCursor);

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

    setCursor(Qt::CursorShape::ArrowCursor);
}

void MainWindow::on_BtnCalcTpc_clicked(){
    const double pi = M_PI;
    double D = ui->FraeserdurchmesserAuswahlTpc->value();
    double ap = ui->ApAuswahlTpc->value();
    int maxN = ui->MaxDrehzahlAuswahlTpc->value();
    int z = ui->SchneidenAuswahlTpc->value();
    int Kc = Dynamic::Kc(ui->MaterialAuswahlTpc->currentIndex());
    double Mc = Dynamic::Mc(ui->MaterialAuswahlTpc->currentIndex());
    double maxKw = Settings::maxKw();
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
    double Fcut;
    int N;
    bool OSX;

    setCursor(Qt::CursorShape::WaitCursor);

    if(QSysInfo::productType() == "osx") {
        OSX = true;
    }else {
        OSX = false;
    }

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

    Fcut = Pc * ((2 * (maxKw * 1000)) / (D * N));
    def = (Fcut * pow((ap + 10), 3)) / (3 * eTool * 0.66 * (pow(D, 4) / 64));

    ui->RealVcOutTpc->setText(QString::number(round((N * pi * D) / 1000)) + " m/min");

    ui->DrehzahlOutTpc->setText(QString::number(N));
    ui->VorschubOutTpc->setText(QString::number(N * z * fz) + " mm/min");
    ui->AeOutTpc->setText(QString::number(ae) + " mm");
    ui->QOutTpc->setText(QString::number(ap * ae * (N * z * fz) / 1000) + " cm³/min");
    Pc = round(Pc * 1000) / 1000;
    ui->PcOutTpc->setText(QString::number(Pc) + " kW");
    def = round(def * 1000) / 1000;
    ui->DeflevtionOutTpc->setText(QString::number(def) + " mm");

    ui->progressBarTpc->setMaximum((maxKw * 1.25) * 1000);

    if(Pc > (maxKw * 1.25)) {
        Pc = maxKw * 1.25;
    }

    if(D <= 4.5){
        QMessageBox msg;
        QString title(tr("Info"));
        QString text(tr("Die aktuelle Berechnung der Deflection ist erst \nab einem Fräserdurchmesser von > 4,5 mm gültig!"));
        if(OSX) {
            msg.setInformativeText(text);
            msg.setText(title);
        }else {
            msg.setText(text);
            msg.setWindowTitle(title);
        }
        msg.setIcon(QMessageBox::Information);
        msg.exec();
    }

    ui->progressBarTpc->setValue(Pc * 1000);

    setCursor(Qt::CursorShape::ArrowCursor);
}

void MainWindow::on_BtnCalcNut_clicked(){
    const double pi = M_PI;
    double D = (ui->FraeserDurchmesserAuswahlNut->currentText()).toDouble();
    int N;
    int maxN = ui->MaxDrehzahlAuswahlNut->value();
    int z = ui->SchneidenAuswahlNut->value();
    double Vc = Slot::Vc(ui->MaterialAuswahlNut->currentIndex());
    double fz = Slot::fz(ui->FraeserDurchmesserAuswahlNut->currentIndex(),ui->MaterialAuswahlNut->currentIndex());
    double maxKw = Settings::maxKwDr();
    double C4 = 1.3;  //Verschleiss
    double C1;        //Kuehlung
    double C2;        //Schneidstoff
    double C3;        //Vc
    double Pc;
    double Q;
    double phi;
    double K;
    double Kc = Slot::Kc(ui->MaterialAuswahlNut->currentIndex());
    double Mc = Slot::Mc(ui->MaterialAuswahlNut->currentIndex());
    double h;
    double y;

    setCursor(Qt::CursorShape::WaitCursor);

    N = (Vc * 1000) / (pi * D);
    if(N > maxN) {
        N = maxN;
    }

    if(ui->OilNut->isChecked()) {
        C1 = 0.85;
    }else if (ui->KssNut->isChecked()) {
        C1 = 0.9;
    }else {
        C1 = 1;
    }

    if(ui->SchnKeramikNut->isChecked()) {
        C2 = 0.9;
    }else if(ui->SchnVhmNut->isChecked()) {
        C2 = 1;
    }else {
        C2 = 1.2;
    }

    if(Vc > 250) {
        C3 = pow((100 / Vc), 0.1);
    }else if(Vc > 80) {
        C3 = 1.03 - ((3 * Vc) / pow(10, 4));
    }else {
        C3 = 1.15;
    }
    C3 = round(C3 * 1000) / 1000;

    if(ui->BeStabilNut->isChecked()) {
        fz = fz * 1.25;
    }else if(ui->BeNormalNut->isChecked()) {
        fz = fz * 1;
    }else {
        fz = fz * 0.75;
    }

    Q = (D * (ui->ApAuswahlNut->value()) * (fz * N * z)) / 1000;

    phi = 2 * asin(D / D);
    h = (114.7 * fz * sin(90) * (D / D)) / phi;
    y = D - (D / 2);
    K = (1 - (0.01 * y)) / ( pow(h, Mc)) * Kc * C1 * C2 * C3 * C4;
    Pc = (Q * K) / (60000 * 0.85); //Pc = C1 * C2 * C3 * C4 * 1;

    ui->RealVcOutNut->setText(QString::number(round((N * pi * D) / 1000)) + " m/min");

    ui->DrehzahlOutNut->setText(QString::number(N));
    ui->VorschubOutNut->setText(QString::number(N * z * fz) + " mm/min");
    ui->QOutNut->setText(QString::number(Q) + " cm³/min");
    Pc = round(Pc * 1000) / 1000;
    ui->PcOutNut->setText(QString::number(Pc)+" kW");

    ui->progressBarNut->setMaximum((maxKw * 1.25) * 1000);

    if(Pc > (maxKw * 1.25)) {
        Pc = maxKw * 1.25;
    }

    ui->progressBarNut->setValue(Pc * 1000);

    setCursor(Qt::CursorShape::ArrowCursor);
}

void MainWindow::on_BtnCalcPlan_clicked(){
    const double pi = M_PI;
    double D = ui->FraeserdurchmesserAuswahlPlan->value();
    int maxN = ui->MaxDrehzahlAuswahlPlan->value();
    int schnGeo = ui->SchneidenGeometryPlan->currentIndex();
    int z = ui->SchneidenAuswahlPlan->value();
    int Kc = Plan::Kc(ui->MaterialAuswahlPlan->currentIndex(), schnGeo);
    double Mc = Plan::Mc(ui->MaterialAuswahlPlan->currentIndex(), schnGeo);
    double ae = ui->AeAuswahlPlan->value();
    double ap = ui->ApAuswahlPlan->value();
    double maxKw = Settings::maxKw();
    double C4 = 1.3;  //Verschleiss
    double C1;        //Kuehlung
    double C2;        //Schneidstoff
    double C3;        //Vc
    double Vc;
    double Pc;
    double K;
    double Q;
    double h;
    double y;
    double einstellWinkel;
    double phi;
    int N;
    int bed;

    setCursor(Qt::CursorShape::WaitCursor);

    if(ui->BeStabilPlan->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalPlan->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    double fz = Plan::fz(ui->MaterialAuswahlPlan->currentIndex(), bed, schnGeo, D, ae);

    if(ui->SchnKeramikPlan->isChecked()) {
        C2 = 0.9;
    }else if(ui->SchnVhmPlan->isChecked()) {
        C2 = 1;
    }else {
        C2 = 1.2;
    }

    Vc = Plan::Vc(ui->MaterialAuswahlPlan->currentIndex(), bed, schnGeo);

    N = (Vc * 1000) / (pi * D);
    if(N > maxN) {
        N = maxN;
    }

    if(ui->OilPlan->isChecked()) {
        C1 = 0.85;
    }else if (ui->KssPlan->isChecked()) {
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

    if(ui->SchneidenGeometryPlan->currentIndex() == 1) {
        einstellWinkel = 45;
    }else {
        einstellWinkel = 90;
    }

    Q = (ae * ap * (fz * N * z)) / 1000;

    //Aussermittige Stellung des Fraesers
    phi = 90 + sin((ae - (D / 2)) / (D / 2));
    //bei mittiger Stellung
    //phi = 2 * asin(ae / D);

    h = (114.7 * fz * sin(einstellWinkel) * (ae / D)) / phi;

    y = ae - (D / 2);

    K = (1 - (0.01 * y)) / ( pow(h, Mc)) * Kc * C1 * C2 * C3 * C4;

    Pc = (Q * K) / (60000 * 0.85);

    ui->RealVcOutPlan->setText(QString::number(round((N * pi * D) / 1000)) + " m/min");

    ui->VorschubOutPlan->setText(QString::number(fz * N * z) + " mm/min");
    ui->DrehzahlOutPlan->setText(QString::number(N));
    Pc = round(Pc * 1000) / 1000;
    ui->PcOutPlan->setText(QString::number(Pc) + " kW");
    Q = round(Q * 1000) / 1000;
    ui->QOutPlan->setText(QString::number(Q) + " cm³/min");

    ui->progressBarPlan->setMaximum((maxKw * 1.25) * 1000);

    if(Pc > (maxKw * 1.25)) {
        Pc = maxKw * 1.25;
    }

    ui->progressBarPlan->setValue(Pc * 1000);

    setCursor(Qt::CursorShape::ArrowCursor);
}

void MainWindow::on_BtnCalcBohren_clicked(){
    const double pi = M_PI;
    double D = ui->FraeserdurchmesserAuswahlBohren->value();
    int maxN = ui->MaxDrehzahlAuswahlBohren->value();
    double fu = Drill::fu(ui->MaterialAuswahlBohren->currentIndex(), D);
    int Kc = Drill::Kc(ui->MaterialAuswahlBohren->currentIndex());
    double Mc = Drill::Mc(ui->MaterialAuswahlBohren->currentIndex());
    double maxKw = Settings::maxKw();
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

    setCursor(Qt::CursorShape::WaitCursor);

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
    Pc = round(Pc * 1000) / 1000;
    ui->PcOutBohren->setText(QString::number(Pc) + " kW");

    ui->progressBarBohren->setMaximum((maxKw * 1.25) * 1000);

    if(Pc > (maxKw * 1.25)) {
        Pc = maxKw * 1.25;
    }

    ui->progressBarBohren->setValue(Pc * 1000);

    setCursor(Qt::CursorShape::ArrowCursor);
}

void MainWindow::on_BtnCalcTurn_clicked(){
    const double pi = M_PI;
    double D = ui->WerkstueckDurchmesserAuswahl->value();
    int maxN = ui->MaxDrehzahlAuswahlTurn->value();
    int Kc = Turn::Kc(ui->MaterialAuswahlTurn->currentIndex());
    double Mc = Turn::Mc(ui->MaterialAuswahlTurn->currentIndex());
    double ap = ui->ApAuswahlTurn->value();
    double fu = ui->FuAuswahlTurn->value();
    double maxKw = Settings::maxKwDr();
    double C4 = 1.3;  //Verschleiss
    double C1;        //Kuehlung
    double C2;        //Schneidstoff
    double C3;        //Vc
    double Vc;
    double Pc;
    double K;
    double Q;
    double h;
    int N;
    int bed;

    setCursor(Qt::CursorShape::WaitCursor);

    if(ui->BeStabilTurn->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalTurn->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    Vc = Turn::Vc(ui->MaterialAuswahlTurn->currentIndex(), bed, ui->turnstyle->currentIndex());

    if(ui->SchnKeramikTurn->isChecked()) {
        C2 = 0.9;
    }else if(ui->SchnVhmTurn->isChecked()) {
        C2 = 1;
    }else {
        C2 = 1.2;
    }

    N = (Vc * 1000) / (pi * D);
    if(N > maxN) {
        N = maxN;
    }

    if(ui->OilTurn->isChecked()) {
        C1 = 0.85;
    }else if (ui->KssTurn->isChecked()) {
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

    Q = Vc * ap * fu * (1 - (ap / D));

    h = fu * sin(45); //Einstellwinkel

    K = (Kc / pow(h, Mc)) * C1 * C2 * C3 * C4;

    Pc = (Q * K) / (60000 * 0.85);

    ui->RealVcOutTurn->setText(QString::number(round((N * pi * D) / 1000)) + " m/min");

    ui->DrehzahlOutTurn->setText(QString::number(N));
    ui->VorschubOutTurn->setText(QString::number(N * fu) + " mm/min");    
    Q = round(Q * 1000) / 1000;
    ui->QOutTurn->setText(QString::number(Q) + " cm³/min");
    Pc = round(Pc * 1000) / 1000;
    ui->PcOutTurn->setText(QString::number(Pc) + " kW");

    ui->progressBarTurn->setMaximum((maxKw * 1.25) * 1000);

    if(Pc > (maxKw * 1.25)) {
        Pc = maxKw * 1.25;
    }

    ui->progressBarTurn->setValue(Pc * 1000);

    setCursor(Qt::CursorShape::ArrowCursor);
}

void MainWindow::on_BtnCalcGewinde_clicked(){
    const double pi = M_PI;
    double D = Thread::Diameter(ui->DurchmesserAuswahlGewinde->currentIndex());
    int N;
    int maxN = ui->MaxDrehzahlAuswahlGewinde->value();
    double Vc = Thread::Vc(ui->MaterialAuswahlGewinde->currentIndex(),ui->DurchmesserAuswahlGewinde->currentIndex());
    double P = Thread::threadPitch(ui->DurchmesserAuswahlGewinde->currentIndex());

    setCursor(Qt::CursorShape::WaitCursor);

    N = (Vc * 1000) / (pi * D);
    if(N > maxN) {
        N = maxN;
    }

    ui->RealVcOutGewinde->setText(QString::number(round((N * pi * D) / 1000)) + " m/min");

    ui->DrehzahlOutGewinde->setText(QString::number(N));
    ui->VorschubOutGewinde->setText(QString::number(round(N * P)) + " mm/min");
    ui->VorschubUOutGewinde->setText(QString::number(P) + " mm/U");


    setCursor(Qt::CursorShape::ArrowCursor);
}


void MainWindow::on_SchneidenGeometryPlan_currentIndexChanged(int index){
    int bed;
    int mat = ui->MaterialAuswahlPlan->currentIndex();

    if(ui->BeStabilPlan->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalPlan->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutPlan->setText(QString::number(Plan::Vc(mat, bed, index)) + " m/min");
}

void MainWindow::on_turnstyle_currentIndexChanged(int index){
    int bed;

    if(ui->BeStabilTurn->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalTurn->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutTurn->setText(QString::number(Turn::Vc(ui->MaterialAuswahlTurn->currentIndex(), bed, index)) + " m/min");
}


// Btn Infolinks
void MainWindow::on_btnEmail_clicked(){
    QDesktopServices::openUrl(QUrl("mailto:?to=contact@spaenerechner.de&subject=Betreff&body=Hi, \nich habe folgendes Problem...", QUrl::TolerantMode));
    //this->setStyleSheet("color: hotpink");
}

void MainWindow::on_btnGit_clicked(){
    QDesktopServices::openUrl(QUrl("https://github.com/EinRainerZufall/SpaeneRechner/issues", QUrl::TolerantMode));
}

void MainWindow::on_btnXlnt_clicked(){
    QDesktopServices::openUrl(QUrl("https://github.com/tfussell/xlnt", QUrl::TolerantMode));
}

void MainWindow::on_btnQT_clicked(){
    QDesktopServices::openUrl(QUrl("https://www.qt.io/", QUrl::TolerantMode));
}


// Bedingungen Auswahl
void MainWindow::on_BeInstabilTpc_clicked(){
    int index = ui->MaterialAuswahlTpc->currentIndex();
    ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 0)) + " m/min");
}

void MainWindow::on_BeNormalTpc_clicked(){
    int index = ui->MaterialAuswahlTpc->currentIndex();
    ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 1)) + " m/min");
}

void MainWindow::on_BeStabilTpc_clicked(){
    int index = ui->MaterialAuswahlTpc->currentIndex();
    ui->VcOutTpc->setText(QString::number(Dynamic::Vc(index, 2)) + " m/min");
}

void MainWindow::on_BeInstabilBohren_clicked(){
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

void MainWindow::on_BeNormalBohren_clicked(){
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

void MainWindow::on_BeStabilBohren_clicked(){
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

void MainWindow::on_SchnHssBohren_clicked(){
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

void MainWindow::on_SchnVhmBohren_clicked(){
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

void MainWindow::on_BeInstabilPlan_clicked(){
    int bed;
    int mat = ui->MaterialAuswahlPlan->currentIndex();
    int schn = ui->SchneidenGeometryPlan->currentIndex();

    if(ui->BeStabilPlan->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalPlan->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutPlan->setText(QString::number(Plan::Vc(mat, bed, schn)) + " m/min");
}

void MainWindow::on_BeNormalPlan_clicked(){
    int bed;
    int mat = ui->MaterialAuswahlPlan->currentIndex();
    int schn = ui->SchneidenGeometryPlan->currentIndex();

    if(ui->BeStabilPlan->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalPlan->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutPlan->setText(QString::number(Plan::Vc(mat, bed, schn)) + " m/min");
}

void MainWindow::on_BeStabilPlan_clicked(){
    int bed;
    int mat = ui->MaterialAuswahlPlan->currentIndex();
    int schn = ui->SchneidenGeometryPlan->currentIndex();

    if(ui->BeStabilPlan->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalPlan->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutPlan->setText(QString::number(Plan::Vc(mat, bed, schn)) + " m/min");
}

void MainWindow::on_BeInstabilTurn_clicked(){
    int bed;

    if(ui->BeStabilTurn->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalTurn->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutTurn->setText(QString::number(Turn::Vc(ui->MaterialAuswahlTurn->currentIndex(), bed, ui->turnstyle->currentIndex())) + " m/min");
}

void MainWindow::on_BeNormalTurn_clicked(){
    int bed;

    if(ui->BeStabilTurn->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalTurn->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutTurn->setText(QString::number(Turn::Vc(ui->MaterialAuswahlTurn->currentIndex(), bed, ui->turnstyle->currentIndex())) + " m/min");
}

void MainWindow::on_BeStabilTurn_clicked(){
    int bed;

    if(ui->BeStabilTurn->isChecked()) {
        bed = 2;
    }else if(ui->BeNormalTurn->isChecked()) {
        bed = 1;
    }else {
        bed = 0;
    }

    ui->VcOutTurn->setText(QString::number(Turn::Vc(ui->MaterialAuswahlTurn->currentIndex(), bed, ui->turnstyle->currentIndex())) + " m/min");
}


// Progressbar update
void MainWindow::on_progressBarTpc_valueChanged(int value){
    if(value >= (Settings::maxKw() * 1000)) {
        ui->progressBarTpc->setStyleSheet("QProgressBar::chunk {background-color: rgb(179, 0, 0);}");
    }else {
        ui->progressBarTpc->setStyleSheet("QProgressBar::chunk {background-color: rgb(0, 179, 0);}");
    }
}

void MainWindow::on_progressBarNut_valueChanged(int value){
    if(value >= (Settings::maxKw() * 1000)) {
        ui->progressBarNut->setStyleSheet("QProgressBar::chunk {background-color: rgb(179, 0, 0);}");
    }else {
        ui->progressBarNut->setStyleSheet("QProgressBar::chunk {background-color: rgb(0, 179, 0);}");
    }
}

void MainWindow::on_progressBarPlan_valueChanged(int value){
    if(value >= (Settings::maxKw() * 1000)) {
        ui->progressBarPlan->setStyleSheet("QProgressBar::chunk {background-color: rgb(179, 0, 0);}");
    }else {
        ui->progressBarPlan->setStyleSheet("QProgressBar::chunk {background-color: rgb(0, 179, 0);}");
    }
}

void MainWindow::on_progressBarBohren_valueChanged(int value){
    if(value >= (Settings::maxKw() * 1000)) {
        ui->progressBarBohren->setStyleSheet("QProgressBar::chunk {background-color: rgb(179, 0, 0);}");
    }else {
        ui->progressBarBohren->setStyleSheet("QProgressBar::chunk {background-color: rgb(0, 179, 0);}");
    }
}

void MainWindow::on_progressBarTurn_valueChanged(int value){
    if(value >= (Settings::maxKw() * 1000)) {
        ui->progressBarTurn->setStyleSheet("QProgressBar::chunk {background-color: rgb(179, 0, 0);}");
    }else {
        ui->progressBarTurn->setStyleSheet("QProgressBar::chunk {background-color: rgb(0, 179, 0);}");
    }
}


// btn settings
void MainWindow::on_btnCreateAll_clicked(){
    setCursor(Qt::CursorShape::WaitCursor);

    createDatabase::deleteWorkbook();

    createDatabase::createSimple();
    createDatabase::createDynamic();
    createDatabase::createDrill();
    createDatabase::createSlot();
    createDatabase::createPlan90();
    createDatabase::createPlan45();
    createDatabase::createTurn();
    createDatabase::createThread();

    setCursor(Qt::CursorShape::ArrowCursor);
}

void MainWindow::on_btnSettingsWrite_clicked(){
    setCursor(Qt::CursorShape::WaitCursor);

    int dis = ui->DisclaimerIn->currentIndex();
    int FrN = ui->maxMillSpeedIn->text().toInt();
    double FrPc = ui->MaxMillPcIn->value();
    int bed = ui->conditionIn->currentIndex();
    int cutMat = ui->cutMatIn->currentIndex();
    int BoWinkel = ui->drillAngleIn->currentIndex();
    int cooling = ui->coolingTypeIn->currentIndex();
    int TurN = ui->maxTurnSpeedIn->text().toInt();
    double TurPc = ui->maxTurnPcIn->value();
    int index = ui->mainTabWidget->currentIndex();

    Settings::write(dis, FrN, FrPc, bed, cutMat, BoWinkel, cooling, TurN, TurPc, index);

    setCursor(Qt::CursorShape::ArrowCursor);
}

void MainWindow::on_btnOpenXLSX_clicked(){
    // Hier jetzt die .xlsx Datei oeffnen
    const QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDesktopServices::openUrl(path);

}


// close event
void MainWindow::closeEvent(QCloseEvent *event){
    setCursor(Qt::CursorShape::WaitCursor);

    int dis = ui->DisclaimerIn->currentIndex();
    int FrN = ui->maxMillSpeedIn->text().toInt();
    double FrPc = ui->MaxMillPcIn->value();
    int bed = ui->conditionIn->currentIndex();
    int cutMat = ui->cutMatIn->currentIndex();
    int BoWinkel = ui->drillAngleIn->currentIndex();
    int cooling = ui->coolingTypeIn->currentIndex();
    int TurN = ui->maxTurnSpeedIn->text().toInt();
    double TurPc = ui->maxTurnPcIn->value();
    int index = ui->mainTabWidget->currentIndex();

    Settings::write(dis, FrN, FrPc, bed, cutMat, BoWinkel, cooling, TurN, TurPc, index);

    setCursor(Qt::CursorShape::ArrowCursor);

    QWidget::closeEvent(event);
}


// Positionstolleranzrechner
void MainWindow::on_SollPosX_editingFinished(){
    double sollX = ui->SollPosX->value();
    double sollY = ui->SollPosY->value();
    double istX = ui->IstPosX->value();
    double istY = ui->IstPosY->value();
    double tol = ui->GeoTolPos->value();
    double temp = 999999;

    temp = sqrt(pow((istX-sollX),2)+pow((istY-sollY),2));

    if(temp <= (tol/2)){
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_ok.svg"));
    }else{
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_no.svg"));
    }
}

void MainWindow::on_IstPosX_editingFinished(){
    double sollX = ui->SollPosX->value();
    double sollY = ui->SollPosY->value();
    double istX = ui->IstPosX->value();
    double istY = ui->IstPosY->value();
    double tol = ui->GeoTolPos->value();
    double temp = 999999;

    temp = sqrt(pow((istX-sollX),2)+pow((istY-sollY),2));

    if(temp <= (tol/2)){
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_ok.svg"));
    }else{
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_no.svg"));
    }
}

void MainWindow::on_SollPosY_editingFinished(){
    double sollX = ui->SollPosX->value();
    double sollY = ui->SollPosY->value();
    double istX = ui->IstPosX->value();
    double istY = ui->IstPosY->value();
    double tol = ui->GeoTolPos->value();
    double temp = 999999;

    temp = sqrt(pow((istX-sollX),2)+pow((istY-sollY),2));

    if(temp <= (tol/2)){
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_ok.svg"));
    }else{
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_no.svg"));
    }
}

void MainWindow::on_IstPosY_editingFinished(){
    double sollX = ui->SollPosX->value();
    double sollY = ui->SollPosY->value();
    double istX = ui->IstPosX->value();
    double istY = ui->IstPosY->value();
    double tol = ui->GeoTolPos->value();
    double temp = 999999;

    temp = sqrt(pow((istX-sollX),2)+pow((istY-sollY),2));

    if(temp <= (tol/2)){
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_ok.svg"));
    }else{
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_no.svg"));
    }
}

void MainWindow::on_GeoTolPos_editingFinished(){
    double sollX = ui->SollPosX->value();
    double sollY = ui->SollPosY->value();
    double istX = ui->IstPosX->value();
    double istY = ui->IstPosY->value();
    double tol = ui->GeoTolPos->value();
    double temp = 999999;

    temp = sqrt(pow((istX-sollX),2)+pow((istY-sollY),2));

    if(temp <= (tol/2)){
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_ok.svg"));
    }else{
        ui->PosIcon->setPixmap(QPixmap(":/img/src/symbol_no.svg"));
    }
}

