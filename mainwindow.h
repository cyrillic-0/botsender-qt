#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "botsender.h"

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
    void on_json_import_btn_clicked();

    void on_log_checkbox_stateChanged(int arg1);

    void on_send_message_btn_clicked();

    void on_actionImport_from_JSON_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

private:
    BotSender bot;
    Json::Reader reader;
    Json::Value root;
    void json_import();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
