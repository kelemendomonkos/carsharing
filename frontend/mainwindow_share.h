#ifndef MAINWINDOW_SHARE_H
#define MAINWINDOW_SHARE_H
#include <QNetworkAccessManager>
#include <QMainWindow>

namespace Ui {
class MainWindow_share;
}

class MainWindow_share : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_share(QWidget *parent = nullptr);
    ~MainWindow_share();

private slots:
    void on_pushButton_addVehicle_clicked();

    void on_pushButton_clicked();

    void onManagerFinished(QNetworkReply *reply);

private:
    Ui::MainWindow_share *ui;
    QNetworkAccessManager manager; //QNerwork Reply kezelése
};

#endif // MAINWINDOW_SHARE_H
