#include "mainwindow_car.h"
#include "ui_mainwindow_car.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkReply>

MainWindow_car::MainWindow_car(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_car)
{
    ui->setupUi(this);
    connect(&manager, &QNetworkAccessManager::finished, this, &MainWindow_car::onManagerFinished);

    QJsonObject jObject;
    QUrl url;
    url.setScheme("http");
    url.setHost("localhost");
    url.setPort(8080);
    url.setPath("/cars");
    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/json");
    QJsonDocument doc(jObject);
    manager.get(request);
}

MainWindow_car::~MainWindow_car()
{
    delete ui;
}

void MainWindow_car::on_pushButton_clicked()
{
    QString licenseplate = ui->lineEdit_licensePlate->text();

    if(licenseplate.isEmpty())
    {
            QMessageBox::warning(this, "Add", "The car's licenseplate is missing!");
    }else {

        QJsonObject jObject;
        jObject.insert("licensePlate", QJsonValue::fromVariant(licenseplate));

        QUrl url;
        url.setScheme("http");
        url.setHost("localhost");
        url.setPort(8080);
        url.setPath("/users/mail");
        QNetworkRequest request(url);
        request.setRawHeader("Content-Type", "application/json");
        QJsonDocument doc(jObject);
        manager.post(request, doc.toJson());
    }
}

void MainWindow_car::onManagerFinished(QNetworkReply *reply)
{
    QString data = (QString) reply->readAll();
    ui->textBrowser_cars->setPlainText(data);
}

void MainWindow_car::on_pushButton_2_clicked()
{
    hide();
    QWidget *parent = this->parentWidget();
    parent->show();
}
