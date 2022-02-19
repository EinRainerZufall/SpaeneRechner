#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <xlnt/xlnt.hpp>
#include <QCoreApplication>
#include <QMessageBox>
#include <QStringList>
#include <QTranslator>
#include <cmath>
#include <QDesktopServices>
#include <QUrl>
#include <QCursor>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_MaterialAuswahlEinfach_currentIndexChanged(int index);

    void on_BtnCalcEinfach_clicked();

    void on_btnEmail_clicked();

    void on_btnGit_clicked();

    void on_btnXlnt_clicked();

    void on_btnQT_clicked();

    void on_btnCreateAll_clicked();

    void on_BtnCalcTpc_clicked();

    void on_MaterialAuswahlTpc_currentIndexChanged(int index);

    void on_FraeserdurchmesserAuswahlTpc_valueChanged(double arg1);

    void on_BeInstabilTpc_clicked();

    void on_BeNormalTpc_clicked();

    void on_BeStabilTpc_clicked();

    void on_MaterialAuswahlBohren_currentIndexChanged(int index);

    void on_BeInstabilBohren_clicked();

    void on_BeNormalBohren_clicked();

    void on_BeStabilBohren_clicked();

    void on_SchnHssBohren_clicked();

    void on_SchnVhmBohren_clicked();

    void on_BtnCalcBohren_clicked();

    void on_MaterialAuswahlPlan_currentIndexChanged(int index);

    void on_SchneidenGeometryPlan_currentIndexChanged(int index);

    void on_BeInstabilPlan_clicked();

    void on_BeNormalPlan_clicked();

    void on_BeStabilPlan_clicked();

    void on_BtnCalcPlan_clicked();

    void on_FraeserdurchmesserAuswahlPlan_valueChanged(double arg1);

    void on_MaterialAuswahlTurn_currentIndexChanged(int index);

    void on_BtnCalcTurn_clicked();

    void on_turnstyle_currentIndexChanged(int index);

    void on_BeInstabilTurn_clicked();

    void on_BeNormalTurn_clicked();

    void on_BeStabilTurn_clicked();

    void on_progressBarTpc_valueChanged(int value);

    void on_progressBarNut_valueChanged(int value);

    void on_progressBarPlan_valueChanged(int value);

    void on_progressBarBohren_valueChanged(int value);

    void on_progressBarTurn_valueChanged(int value);

    void on_btnSettingsWrite_clicked();

    void on_BtnCalcNut_clicked();

    void on_MaterialAuswahlNut_currentIndexChanged(int index);

    void on_DurchmesserAuswahlGewinde_currentIndexChanged(int index);

    void on_MaterialAuswahlGewinde_currentIndexChanged(int index);

    void on_BtnCalcGewinde_clicked();

    void on_btnOpenXLSX_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
