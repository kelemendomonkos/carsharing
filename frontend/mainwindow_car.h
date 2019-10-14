#ifndef MAINWINDOW_CAR_H
#define MAINWINDOW_CAR_H
#include <QNetworkAccessManager> //Adatcseréhez kell
#include <QMainWindow>

namespace Ui {
class MainWindow_car;
}

class MainWindow_car : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_car(QWidget *parent = nullptr);
    ~MainWindow_car();

private slots:
    void on_pushButton_clicked();

    void onManagerFinished(QNetworkReply *reply);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow_car *ui;
    QNetworkAccessManager manager;
};

#endif // MAINWINDOW_CAR_H
