#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindow_car.h" //Bérlő fellület includolása
#include "mainwindow_share.h" //Megosztó fellület includolása
#include "mainwindow_createuser.h" //Új felhasznló fellület includolása
#include <QNetworkAccessManager> //Adatcseréhez kell

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_credits_clicked();

    void on_pushButton_createNewUser_clicked();

    void onManagerFinished(QNetworkReply *reply); //QNerwork Reply kezelése

private:
    Ui::MainWindow *ui;
    MainWindow_car *mainWdow_car; //objektum a car windowhoz
    MainWindow_share *mainWindow_share; //objektum a share windowhoz
    MainWindow_createUser *mainWindow_createUser; // objektum a creatNewUser windowhoz
    QNetworkAccessManager manager; //QNerwork Reply kezelése
};

#endif // MAINWINDOW_H
