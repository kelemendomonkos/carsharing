#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/img/pic.png");
    ui->label_pic->setPixmap(pix.scaled(230,230));
    this->setFixedSize(QSize(650, 350));
    connect(&manager, &QNetworkAccessManager::finished, this, &MainWindow::onManagerFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    QJsonObject jObject;
    jObject.insert("name", QJsonValue::fromVariant(username));
    jObject.insert("password", QJsonValue::fromVariant(password));

    QUrl url;
    url.setScheme("http");
    url.setHost("localhost");
    url.setPort(8080);
    url.setPath("/users/login");
    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/json");
    QJsonDocument doc(jObject);
    manager.post(request, doc.toJson());
}

void MainWindow::on_pushButton_credits_clicked()
{
   QMessageBox::about(this, "About", "Alkalmazásfejlesztési Környezetek Házi Feladat\n\nGyimes Balázs - CLTWFY \nDomonkos Kelemen - UWMDDI\n\n2019.05.19");
}


void MainWindow::on_pushButton_createNewUser_clicked()
{
    hide();
    mainWindow_createUser = new MainWindow_createUser(this);
    mainWindow_createUser->show();
}

void MainWindow::onManagerFinished(QNetworkReply *reply)
{
    QString data = (QString) reply->readAll();

    //Renting
    if(data == "rent")
    {
        hide();
        mainWdow_car = new MainWindow_car(this);
        mainWdow_car->show();
    }

    //Shareing
    else if(data == "share")
    {
        hide();
        mainWindow_share = new MainWindow_share(this);
        mainWindow_share->show();
    }
    else {
        QMessageBox::warning(this, "Login", "Username or password is incorrect!");
    }
}
