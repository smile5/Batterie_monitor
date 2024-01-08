#include "config.h"
#include "ui_config.h"

config::config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);
    //this->ui->cb_Deplacement->hide();
    this->ui->sp_c->hide();
    this->ui->sp_v->hide();
}

double config::value_c_couple() const
{
    return(this->ui->sp_c->value());
}

double config::value_c_vitesse() const
{
    return(this->ui->sp_v->value());
}

config::~config()
{
    delete ui;
}

void config::on_cb_Deplacement_currentIndexChanged(int index)
{
    emit modify_d();
}


void config::on_cb_force_currentIndexChanged(int index)
{
    emit modify_f();
}


void config::on_buttonBox_accepted()
{
    //this->ui->cb_Deplacement->hide();
    this->ui->sp_c->hide();
    this->ui->sp_v->hide();
    emit config_ok();
}

void config::on_passwd_button_clicked()
{
    if(this->ui->le_passwd->text()=="Mogwai")
    {
        this->ui->sp_c->show();
        this->ui->sp_v->show();
    }
    else
    {
        //this->ui->cb_Deplacement->hide();
        this->ui->sp_c->hide();
        this->ui->sp_v->hide();
    }
    this->ui->le_passwd->setText("");
}

