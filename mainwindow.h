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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
