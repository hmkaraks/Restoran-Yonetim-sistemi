#ifndef SIPARISDIALOG_H
#define SIPARISDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>

class SiparisDialog : public QDialog {
    Q_OBJECT
public:
    explicit SiparisDialog(QWidget *parent = nullptr);
    QString getSecilenUrun() const;
    int getAdet() const;

private:
    QComboBox *urunCombo;
    QSpinBox *adetSpin;
    QPushButton *ekleButon;
    QPushButton *odemeButon; // Faz 4: Hesap Kapatma Butonu
};

#endif