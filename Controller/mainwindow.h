#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnHuman_clicked();

    void on_btnIDQuery_clicked();

    void on_btnFamilyQuery_clicked();

    void on_btnFriendsQuery_clicked();

    void on_btnFamilyQuery_3_clicked();

    void on_btnDeadQuery_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_btnData_clicked();

    void on_btnNebula_clicked();

    void on_btnEbony_clicked();

    void on_btnBlackD_clicked();

    void on_btnThanos_clicked();

    void on_btnThanosYear_clicked();

    void on_btnThanosB_clicked();

    void on_btnMidnight_clicked();

    void on_btnCorvus_clicked();

    void on_btnAntMan_clicked();

    void on_btnIronMan_clicked();

    void on_btnThor_clicked();

    void on_btnSpiderMan_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
