#include "mainwindow_createuser.h"
#include "ui_mainwindow_createuser.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

QString username;
QString password;
QString passwordagain;
QString email;
bool share = false;

MainWindow_createUser::MainWindow_createUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_createUser)
{
    ui->setupUi(this);
    connect(&manager, &QNetworkAccessManager::finished, this, &MainWindow_createUser::onManagerFinished);
}

MainWindow_createUser::~MainWindow_createUser()
{
    delete ui;
}

void MainWindow_createUser::on_pushButton_add_clicked()
{
    username = ui->lineEdit_userName->text();
    password = ui->lineEdit_password->text();
    passwordagain = ui->lineEdit_passwordagain->text();
    email = ui->lineEdit_email->text();

    if(username.isEmpty() || password.isEmpty() || passwordagain.isEmpty())
    {
        QMessageBox::warning(this, "Password", "Some information is missing!");

    }else if(password != passwordagain)
    {
        QMessageBox::warning(this, "Password", "The two passwords are not matching!");
    }
    else if (ui->radioButton_rent->isChecked() == false && ui->radioButton_sahre->isChecked() == false) {
        QMessageBox::warning(this, "Role", "Please choose between Rent or Share!");
    }
    else {
        QJsonObject jObject;
        jObject.insert("name", QJsonValue::fromVariant(username));
        jObject.insert("password", QJsonValue::fromVariant(password));
        jObject.insert("email", QJsonValue::fromVariant(email));
        if(ui->radioButton_rent->isChecked()){
            jObject.insert("role", QJsonValue::fromVariant("rent"));
        } else {
            jObject.insert("role", QJsonValue::fromVariant("share"));
        }
        QUrl url;
        url.setScheme("http");
        url.setHost("localhost");
        url.setPort(8080);
        url.setPath("/users");
        QNetworkRequest request(url);
        request.setRawHeader("Content-Type", "application/json");

        QJsonDocument doc(jObject);
        manager.post(request, doc.toJson());
        hide();
        QWidget *parent = this->parentWidget();
        parent->show();
    }
}

void MainWindow_createUser::on_radioButton_sahre_clicked()
{
    share = true;
}

void MainWindow_createUser::on_radioButton_rent_clicked()
{
    share = false;
}

void MainWindow_createUser::onManagerFinished(QNetworkReply *reply)
{
    qDebug()<< reply->readAll();
}
