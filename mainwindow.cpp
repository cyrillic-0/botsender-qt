#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::json_import()
{
    QString filename = QFileDialog::getOpenFileName(this, "Import from a JSON File");
    std::fstream file(filename.toStdString());
    if (!file) {
        QMessageBox::critical(this, "Error", "Unable to open a file");
        return;
    }
    this->reader.parse(file, this->root);
    ui->bot_token->setText(QString::fromStdString(this->root["token"].asString()));
    ui->chat_id->setText(QString::fromStdString(this->root["chat_id"].asString()));
    ui->log_file->setText(QString::fromStdString(this->root["verbose_data"].asString()));
}

void MainWindow::on_json_import_btn_clicked()
{
    json_import();
}

void MainWindow::on_actionImport_from_JSON_triggered()
{
    json_import();
}

void MainWindow::on_log_checkbox_stateChanged(int arg1)
{
    if (arg1) {
        bot.turnOnVerboseOutput(ui->log_file->text().toStdString());
    }
    else {
        bot.turnOffVerboseOutput();
    }
}


void MainWindow::on_send_message_btn_clicked()
{
    bot.setBotToken(ui->bot_token->text().toStdString());
    bot.setChatID(ui->chat_id->text().toInt());
    bool ok;
    QString text = QInputDialog::getText(this, "Send a message", "Enter a message:", QLineEdit::Normal, QDir::home().dirName(), &ok);
    bot.sendMessage(text.toStdString());
}




void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "BotSender v1.2.1");
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

