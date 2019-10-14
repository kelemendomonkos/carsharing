#ifndef MAINWINDOW_CREATEUSER_H
#define MAINWINDOW_CREATEUSER_H
#include <QMainWindow>
#include <QNetworkAccessManager> //Adatcseréhez kell

namespace Ui {
class MainWindow_createUser;
}

class MainWindow_createUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_createUser(QWidget *parent = nullptr);
    ~MainWindow_createUser();

private slots:
    void on_pushButton_add_clicked();

    void on_radioButton_sahre_clicked();

    void on_radioButton_rent_clicked();

    void onManagerFinished(QNetworkReply *reply); //QNerwork Reply kezelése

private:
    Ui::MainWindow_createUser *ui;
    QNetworkAccessManager manager; //QNerwork Reply kezelése
};

#endif // MAINWINDOW_CREATEUSER_H
