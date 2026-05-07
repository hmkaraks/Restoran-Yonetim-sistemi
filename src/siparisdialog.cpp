#include "../include/siparisdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QAbstractItemView>

SiparisDialog::SiparisDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Masa İşlemleri");
    setMinimumWidth(350);

    // --- GÜNCEL VE GÖRÜNÜRLÜK GARANTİLİ TASARIM (QSS) ---
    this->setStyleSheet(
        "QDialog { background-color: #FAF0CA; border: 3px solid #0D3B66; }"
        "QLabel { color: #0D3B66; font-size: 14px; font-weight: bold; }"

        // ComboBox Ana Kutu Stili
        "QComboBox { "
        "   background-color: #ffffff; "
        "   border: 2px solid #0D3B66; "
        "   border-radius: 6px; "
        "   padding: 5px; "
        "   color: #0D3B66; "
        "   font-weight: bold; "
        "   min-height: 30px; "
        "}"

        // !!! YEMEKLERİN GÖRÜNMESİNİ SAĞLAYAN KRİTİK KISIM !!!
        "QComboBox QAbstractItemView { "
        "   background-color: #ffffff; "
        "   color: #0D3B66; "
        "   selection-background-color: #0D3B66; "
        "   selection-color: #FAF0CA; "
        "   border: 1px solid #0D3B66; "
        "   outline: 0px; "
        "}"

        "QSpinBox { "
        "   background-color: #ffffff; "
        "   border: 2px solid #0D3B66; "
        "   border-radius: 6px; "
        "   padding: 5px; "
        "   color: #0D3B66; "
        "   font-weight: bold; "
        "   min-height: 30px; "
        "}"

        "QPushButton#onayButon { "
        "   background-color: #10ac84; "
        "   color: white; "
        "   height: 45px; "
        "   border-radius: 12px; "
        "   font-weight: bold; "
        "   border-bottom: 4px solid #0a8e6e; "
        "}"
        "QPushButton#onayButon:pressed { border-bottom: 1px solid #0a8e6e; }"

        "QPushButton#odemeButon { "
        "   background-color: #0D3B66; "
        "   color: #FAF0CA; "
        "   height: 45px; "
        "   border-radius: 12px; "
        "   font-weight: bold; "
        "   border-bottom: 4px solid #082a4a; "
        "}"
        "QPushButton#odemeButon:pressed { border-bottom: 1px solid #082a4a; }"
    );

    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);

    // Ürün Seçimi
    layout->addWidget(new QLabel("Sipariş Verilecek Ürün:"));
    urunCombo = new QComboBox(this);
    urunCombo->addItems({"Adana Kebap", "Urfa Kebap", "Lahmacun", "İskender", "Karışık Pide", "Ayran", "Kola", "Künefe"});
    layout->addWidget(urunCombo);

    // Adet Seçimi
    layout->addWidget(new QLabel("Adet:"));
    adetSpin = new QSpinBox(this);
    adetSpin->setRange(1, 50);
    layout->addWidget(adetSpin);

    // Boşluk ekleyelim butonlardan önce
    layout->addSpacing(10);

    // Onay Butonu
    ekleButon = new QPushButton("✓ SİPARİŞİ ONAYLA", this);
    ekleButon->setObjectName("onayButon");
    layout->addWidget(ekleButon);

    // Ödeme Butonu
    odemeButon = new QPushButton("💳 HESABI KAPAT / ÖDEME AL", this);
    odemeButon->setObjectName("odemeButon");
    layout->addWidget(odemeButon);

    // Sinyaller
    connect(ekleButon, &QPushButton::clicked, this, &QDialog::accept);
    connect(odemeButon, &QPushButton::clicked, [this]() {
        done(2); // MainWindow'a 'Ödeme Al' sinyali gönderir
    });
}

QString SiparisDialog::getSecilenUrun() const {
    return urunCombo->currentText();
}

int SiparisDialog::getAdet() const {
    return adetSpin->value();
}