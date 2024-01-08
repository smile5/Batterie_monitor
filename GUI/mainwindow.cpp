#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    dev_label(new ClickableLabel),
    serial_port_label(new QLabel),
    etat_label(new ClickableLabel),
    serial(new QSerialPort),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
 //   settings->show();
 //   settings->hide();
    timer_save =new QTimer();
    connect(timer_save, SIGNAL(timeout()), this,SLOT(save_timeout()));
    timer_save->stop();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this,SLOT(serial_timeout()));
    timer->stop();
    dev_label->setAlignment(Qt::AlignLeft);
    dev_label->setFixedWidth(180);
    connect(dev_label,SIGNAL(clicked()),this,SLOT(on_dev_label_clicked()));
    serial_port_label->setAlignment(Qt::AlignCenter);
    serial_port_label->setIndent(25);
    etat_label->setAlignment(Qt::AlignCenter);
    etat_label->setIndent(25);
    ui->statusBar->addWidget(dev_label);
    ui->statusBar->addWidget(serial_port_label, 1);
    ui->statusBar->addWidget(etat_label,2);
    etat_label->setText("Système Arrêté");
    dev_label->setText("Réalisé par Enise - XG & LG");
    serial_port_label->setText("Port série: "+serial->portName());
    connect_serial();
    trame_commence=false;
}

MainWindow::~MainWindow()
{
    if(serial->isOpen() && serial->error()==0)
    {
    }
    else
    {
        connect_serial();

    }
       serial->waitForBytesWritten();
       serial->close();
       delete ui;
}

void MainWindow::serial_timeout()
{
    etat_label->setText("Mesures Arrêtées");
    //chart_update->stop();
    rcv_serie.rcv_ok=false;
    rcv_serie.nb_char=0;
    timer->stop();
}

void MainWindow::serialreceived()
{
    int i;
    long tempval;
    static unsigned char tabchar[4];
    timer->start(1000);
    //chart_update->singleShot(300, this, SLOT(append_point()));
    serbuf=serial->readAll();
//    etat_label->setText("Mesure en cours");
    if (trame_commence==false)
    {
        rcv_serie.nb_char=0;
    }
    for(i=0;i<serbuf.size();i++)
    {
        if ((serbuf.at(i)=='%')&&(rcv_serie.nb_char==0)&& (trame_commence==false))
        {
            rcv_serie.nb_char=1;
            trame_commence=true;
        }

        else if((serbuf.at(i)==',')&&(trame_commence==true)&&((rcv_serie.nb_char%5)==0))
        {
            tempval=tabchar[0]+(tabchar[1]<<8)+(tabchar[2]<<16)+(tabchar[3]<<24);
            tab_mesure[(rcv_serie.nb_char/5)-1]=1.0*((float)tempval);
            rcv_serie.nb_char++;
        }
        else if((serbuf.at(i)=='#')&&(trame_commence==true)&&(rcv_serie.nb_char==81))
        {
            tempval=tabchar[0]+(tabchar[1]<<8)+(tabchar[2]<<16)+(tabchar[3]<<24);
            tab_mesure[(rcv_serie.nb_char/5)-1]=1.0*((float)tempval);
            rcv_serie.nb_char=0;
            rcv_serie.rcv_ok=true;
            trame_commence=false;
             ui->label_C0->setText(QString::number(tab_mesure[0], 'g', 4));
            ui->label_C1->setText(QString::number(tab_mesure[1], 'g', 4));
            ui->label_C2->setText(QString::number(tab_mesure[2], 'g', 4));
            ui->label_C3->setText(QString::number(tab_mesure[3], 'g', 4));
            ui->label_C4->setText(QString::number(tab_mesure[4], 'g', 4));
            ui->label_C5->setText(QString::number(tab_mesure[5], 'g', 4));
            ui->label_C6->setText(QString::number(tab_mesure[6], 'g', 4));
            ui->label_C7->setText(QString::number(tab_mesure[7], 'g', 4));
            ui->label_C8->setText(QString::number(tab_mesure[8], 'g', 4));
            ui->label_C9->setText(QString::number(tab_mesure[9], 'g', 4));
            ui->label_C10->setText(QString::number(tab_mesure[10], 'g', 4));
            ui->label_C11->setText(QString::number(tab_mesure[11], 'g', 4));
            ui->label_C12->setText(QString::number(tab_mesure[12], 'g', 4));
            ui->label_C13->setText(QString::number(tab_mesure[13], 'g', 4));
            ui->label_C14->setText(QString::number(tab_mesure[14], 'g', 4));
            ui->label_C15->setText(QString::number(tab_mesure[15], 'g', 4));
            ui->label_S0->setText(QString::number(tab_mesure[0], 'g', 4));
            ui->label_S1->setText(QString::number(tab_mesure[1]-tab_mesure[0], 'g', 4));
            ui->label_S2->setText(QString::number(tab_mesure[2]-tab_mesure[1], 'g', 4));
            ui->label_S3->setText(QString::number(tab_mesure[3]-tab_mesure[2], 'g', 4));
            ui->label_S4->setText(QString::number(tab_mesure[4]-tab_mesure[3], 'g', 4));
            ui->label_S5->setText(QString::number(tab_mesure[5]-tab_mesure[4], 'g', 4));
            ui->label_S6->setText(QString::number(tab_mesure[6]-tab_mesure[5], 'g', 4));
            ui->label_S7->setText(QString::number(tab_mesure[7]-tab_mesure[6], 'g', 4));
            ui->label_S8->setText(QString::number(tab_mesure[8]-tab_mesure[7], 'g', 4));
            ui->label_S9->setText(QString::number(tab_mesure[9]-tab_mesure[8], 'g', 4));
            ui->label_S10->setText(QString::number(tab_mesure[10]-tab_mesure[9], 'g', 4));
            ui->label_S11->setText(QString::number(tab_mesure[11]-tab_mesure[10], 'g', 4));
            ui->label_S12->setText(QString::number(tab_mesure[12]-tab_mesure[11], 'g', 4));
            ui->label_S13->setText(QString::number(tab_mesure[13]-tab_mesure[12], 'g', 4));
            ui->label_S14->setText(QString::number(tab_mesure[14]-tab_mesure[13], 'g', 4));
            ui->label_S15->setText(QString::number(tab_mesure[15]-tab_mesure[14], 'g', 4));
        }
        else if((rcv_serie.nb_char<81)&&(trame_commence==true) && (serbuf.at(i)!=','))
        {
            tabchar[(rcv_serie.nb_char%5)-1]=serbuf.at(i);
            rcv_serie.nb_char++;
        }
    }
}

void MainWindow::on_dev_label_clicked()
{
    QMessageBox::about(this,"Laboratoire Mécatronique",
                       "<h4>Laboratoire Mécatronique 342</h4>\n\n"
                       "Mesure de couple ENISE <br>"
                       "Copyright 2022 Enise.<br>"
                       "Support: Galtier Granjon Thévenon - Centrale Lyon - ENISE <br>"
                       "<a href=\"http://www.enise.fr\">http://www.enise.fr</a>" );

}

void MainWindow::connect_serial()
{
        QString port_name;
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
      /*        qDebug() << "Name : " << info.portName();
                qDebug() << "Description : " << info.description();
                qDebug() << "Manufacturer: " << info.manufacturer();
                qDebug() << "VID " << info.vendorIdentifier();
                qDebug() << "PID" << info.productIdentifier();

       */
            if((info.vendorIdentifier()==0x04B4)&&(info.productIdentifier()==0xF232)) //Dmanufacturer()=="Essais Flambage Enise"))
            {
                port_name=info.portName();
            }
        }
//        if(serial->isOpen())
//        {
//            serial->disconnect(serial,SIGNAL(readyRead()),this,SLOT(serialreceived()));
//            serial->flush();
//            serbuf.clear();
//            serial->close();
//        }
        rcv_serie.nb_char=0;
        rcv_serie.rcv_ok=false;
#ifdef OS_LINUX
       serial->setPortName("/dev/"+port_name);
        //serial->setPortName("/dev/pts/1"); // only for debug
#elif
        serial->setPortName(portname);
#endif
        if(port_name=="")
        {
         //   ui->pb_start->setChecked(false);
            serial_port_label->setText("Port Série: Clos");
            serial->disconnect();
            serial->clearError();
            serial->close();

        }
        else
        {
            tab_data.clear();
            serbuf.clear();
            serial->setBaudRate(1000000);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->setReadBufferSize(0);
            serial->open(QIODevice::ReadWrite);
            serial->connect(serial,SIGNAL(readyRead()),this,SLOT(serialreceived()),Qt::UniqueConnection);
            serial_port_label->setText("Port série: "+serial->portName());
        }
}

void MainWindow::save_timeout()
{

        timer_save->start(5000);
        QStringList strList;
        QDateTime heure;
        heure.currentDateTime();
        if (fichiercsv.isOpen())
        {
            strList.clear();
            QTextStream stream(&fichiercsv);
            strList << heure.currentDateTime().toString("dd.MM.yyyy.hh.mm.ss") +";"+ ui->label_I->text() +";" + ui->label_S0->text() + ";" + ui->label_S1->text() + ";" + ui->label_S2->text() + ";" \
                + ui->label_S3->text() + ";" + ui->label_S4->text() + ";" + ui->label_S5->text() + ";" + ui->label_S6->text() + ";" + ui->label_S7->text() + ";" + ui->label_S8->text() + ";" \
                + ui->label_S9->text() + ";" + ui->label_S10->text() + ";" + ui->label_S11->text() + ";" + ui->label_S12->text() + ";" + ui->label_S13->text() + ";" + ui->label_S14->text() + ";" \
                + ui->label_S15->text();
            stream << strList.join(";")+"\n";
        }
}

void MainWindow::on_Start_toggled(bool checked)
{
        if(checked == true)
        {
            ui->led->setPixmap(QPixmap(":/red_led.png"));
            QString filename;
            filename=QFileDialog::getSaveFileName();// fd->directory().path()+"/fichiercsv.csv");
            fichiercsv.setFileName(filename);

            if (fichiercsv.open(QFile::WriteOnly|QFile::Truncate))
            {
                QTextStream stream(&fichiercsv);
                QStringList strList;
                //Entete fichier
                strList.clear();
                strList << "Heure;Courant (A);cellule 1(V);cellule 2(V);cellule 3(V);cellule 4(V);cellule 5(V);cellule 6(V);cellule 7(V);cellule 8(V);cellule 9(V);cellule 10(V);cellule 11(V);cellule 12(V);"  \
                            << "cellule 13(V);cellule 14(V);cellule 15(V);cellule 16(V)";
                stream << strList.join(";")+"\n";
                // for( int r = 0; r < ui->tableWidget_1->rowCount(); ++r )
                // {
                //     strList.clear();
                //     strList << (ui->tableWidget_1->item( r,0)->text()+";"+ui->tableWidget_2->item( r,0)->text()+";"+ui->tableWidget_3->item( r,0)->text()+";"+ui->tableWidget_4->item( r,0)->text());
                //     stream << strList.join(";")+"\n";
                // }
               // fichiercsv.close();
            }
            timer_save->start(5000);

        }
        else
        {
            ui->led->setPixmap(QPixmap(":/green_led.png"));
            timer_save->stop();
            if (fichiercsv.isOpen())
            {
                fichiercsv.close();
            }
        }

}

