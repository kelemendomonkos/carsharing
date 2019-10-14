#include "mainwindow_share.h"
#include "ui_mainwindow_share.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkReply>

MainWindow_share::MainWindow_share(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_share)
{
    ui->setupUi(this);
    connect(&manager, &QNetworkAccessManager::finished, this, &MainWindow_share::onManagerFinished);
}

MainWindow_share::~MainWindow_share()
{
    delete ui;
}

void MainWindow_share::on_pushButton_addVehicle_clicked()
{
    QString vehiclename = ui->lineEdit_vehicleName->text();
    QString ownername = ui->lineEdit_ownerName->text();
    QString licenseplate = ui->lineEdit_licensePalte->text();

    if(ownername.isEmpty() || vehiclename.isEmpty() || licenseplate.isEmpty())
    {
            QMessageBox::warning(this, "Add", "Some information is missing!");
    }else {
        QMessageBox::about(this, "Add", "Your vehicle is added!");

        QJsonObject jObject;
        jObject.insert("licensePlate", QJsonValue::fromVariant(licenseplate));
        jObject.insert("owner", QJsonValue::fromVariant(ownername));
        jObject.insert("name", QJsonValue::fromVariant(licenseplate));

        QUrl url;
        url.setScheme("http");
        url.setHost("localhost");
        url.setPort(8080);
        url.setPath("/cars");
        QNetworkRequest request(url);
        request.setRawHeader("Content-Type", "application/json");
        QJsonDocument doc(jObject);
        manager.post(request, doc.toJson());
}
}

void MainWindow_share::on_pushButton_clicked()
{
    hide();
    QWidget *parent = this->parentWidget();
    parent->show();
}

void MainWindow_share::onManagerFinished(QNetworkReply *reply)
{
    qDebug()<< reply->readAll();
}
