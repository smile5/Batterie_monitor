#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define OS_LINUX
#define NB_MES 16

#include "clickablelabel.h"
#include <QMainWindow>
#include <QLabel>
#include <QSerialPortInfo>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QDateTime>

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class config;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    typedef struct{
        bool rcv_ok;
        float couple;
        float vitesse;
        unsigned char nb_char;
        unsigned char etat;
    } rcv_message;
public:
    explicit MainWindow(QWidget *parent = 0);
     QSerialPortInfo serialPortInfo;
     ClickableLabel *dev_label;
     QLabel *serial_port_label;
     ClickableLabel *etat_label;
     ~MainWindow();
     rcv_message rcv_serie;
     QTimer *timer;

private slots:
    void serial_timeout();
    void serialreceived();
    void on_dev_label_clicked();
    void on_Start_toggled(bool checked);
    void save_timeout();

private:
    QSerialPort *serial;
    Ui::MainWindow *ui;
    void connect_serial();
    QByteArray serbuf;
    QVector<rcv_message> tab_data;
    float tab_mesure[NB_MES];
    bool trame_commence;
    QFile fichiercsv;
    QTimer *timer_save;
};

#endif // MAINWINDOW_H
