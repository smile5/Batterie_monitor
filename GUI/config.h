#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = nullptr);
    ~config();
    double value_c_vitesse() const;
    double value_c_couple() const;
signals:
    void modify_d();
    void modify_f();
    void config_ok();

private slots:
    void on_cb_Deplacement_currentIndexChanged(int index);
    void on_cb_force_currentIndexChanged(int index);
    void on_buttonBox_accepted();
    void on_passwd_button_clicked();

private:
    Ui::config *ui;
};

#endif // CONFIG_H
