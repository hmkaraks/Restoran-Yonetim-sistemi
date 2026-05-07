#include "../include/mainwindow.h"
#include "../include/siparisdialog.h"
#include "../include/siparis_isleyici.h"
#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QListWidget>
#include <QVBoxLayout>
#include <fstream>

// Grafik kütüphaneleri
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("RESYS ULTIMATE v5.0 - Yönetim Paneli");
    resize(1150, 850);

    // --- ÖZEL TASARIM (QSS) ---
    this->setStyleSheet(
        "QMainWindow { background-color: #FAF0CA; }"
        "QMenuBar { background-color: #0D3B66; color: #FAF0CA; padding: 5px; font-weight: bold; }"
        "QMenuBar::item:selected { background-color: #154c7a; }"
        "QStatusBar { background-color: #0D3B66; color: #FAF0CA; font-weight: bold; }"
        "QPushButton#mutfakButonu { "
        "   background-color: #0D3B66; "
        "   color: #FAF0CA; "
        "   border-radius: 15px; "
        "   font-size: 14px; "
        "   font-weight: bold; "
        "}"
        "QPushButton#mutfakButonu:hover { background-color: #154c7a; }"
    );

    masaCirolari.assign(16, 0.0);
    menuOlustur();
    arayuzuKur();
    verileriYukle();

    statusBar()->showMessage("Sistem Hazır | Yetkili Girişi Yapıldı.");
}

void MainWindow::menuOlustur() {
    QMenuBar *mBar = menuBar();
    QMenu *dosyaMenu = mBar->addMenu("Dosya");
    connect(dosyaMenu->addAction("Verileri Kaydet"), &QAction::triggered, this, &MainWindow::verileriKaydet);
    connect(dosyaMenu->addAction("Verileri Yükle"), &QAction::triggered, this, &MainWindow::verileriYukle);
    dosyaMenu->addSeparator();
    connect(dosyaMenu->addAction("Güvenli Çıkış"), &QAction::triggered, this, &QWidget::close);

    QMenu *raporMenu = mBar->addMenu("İstatistik");
    connect(raporMenu->addAction("Ciro Analizi"), &QAction::triggered, this, &MainWindow::grafikGoster);
}

void MainWindow::arayuzuKur() {
    auto *merkeziWidget = new QWidget(this);
    auto *layout = new QGridLayout(merkeziWidget);
    layout->setSpacing(20);

    for (int i = 0; i < 16; ++i) {
        int masaNo = i + 1;
        auto *buton = new QPushButton(QString("MASA %1\n\nBOŞ").arg(masaNo), this);
        buton->setMinimumSize(140, 140);

        // BAŞLANGIÇ STİLİ: Senin seçtiğin Lacivert (#0D3B66)
        buton->setStyleSheet(
            "background-color: #0D3B66; "
            "color: #FAF0CA; "
            "border-radius: 20px; "
            "font-weight: bold; "
            "border-bottom: 5px solid #082a4a;"
        );

        connect(buton, &QPushButton::clicked, [this, buton, masaNo]() {
            SiparisDialog dialog(this);
            int sonuc = dialog.exec();

            if (sonuc == QDialog::Accepted) {
                QString urun = dialog.getSecilenUrun();
                int adet = dialog.getAdet();
                QString siparisNotu = QString("Masa %1: %2 x %3").arg(masaNo).arg(adet).arg(urun);

                mutfakListesi.push_back(siparisNotu);
                masaCirolari[masaNo - 1] += (adet * 150.0);

                SiparisIsleyici *isleyici = new SiparisIsleyici(siparisNotu, this);
                connect(isleyici, &SiparisIsleyici::siparisHazir, this, &MainWindow::mutfaktanHaberGeldi);
                connect(isleyici, &SiparisIsleyici::finished, isleyici, &QObject::deleteLater);
                isleyici->start();

                // DURUM: HAZIRLANIYOR (Sıcak bir ton)
                buton->setText(QString("MASA %1\n\nHAZIRLANIYOR").arg(masaNo));
                buton->setStyleSheet("background-color: #F4A261; color: white; border-radius: 20px; font-weight: bold; border-bottom: 5px solid #E76F51;");
            }
            else if (sonuc == 2) {
                QMessageBox::StandardButton cevap = QMessageBox::question(this, "Ödeme",
                    QString("Masa %1 hesabı kapatılsın mı?").arg(masaNo), QMessageBox::Yes | QMessageBox::No);

                if (cevap == QMessageBox::Yes) {
                    buton->setText(QString("MASA %1\n\nBOŞ").arg(masaNo));
                    buton->setStyleSheet("background-color: #0D3B66; color: #FAF0CA; border-radius: 20px; font-weight: bold; border-bottom: 5px solid #082a4a;");
                    verileriKaydet();
                }
            }
        });
        layout->addWidget(buton, i / 4, i % 4);
    }

    auto *btnMutfak = new QPushButton("♨ MUTFAK TAKİP PANELİ", this);
    btnMutfak->setObjectName("mutfakButonu");
    btnMutfak->setFixedHeight(60);
    connect(btnMutfak, &QPushButton::clicked, this, &MainWindow::mutfakEkraniniAc);
    layout->addWidget(btnMutfak, 4, 0, 1, 4);

    setCentralWidget(merkeziWidget);
}

void MainWindow::mutfaktanHaberGeldi(QString bilgi) {
    QMessageBox::information(this, "Mutfak Bildirimi", bilgi + " hazır! Servis ediniz.");
}

void MainWindow::verileriKaydet() {
    std::ofstream dosya("restoran_veri.dat", std::ios::binary);
    if (!dosya) return;
    for (double ciro : masaCirolari) dosya.write(reinterpret_cast<const char*>(&ciro), sizeof(double));
    size_t size = mutfakListesi.size();
    dosya.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    for (const auto& s : mutfakListesi) {
        std::string stdS = s.toStdString();
        size_t len = stdS.size();
        dosya.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        dosya.write(stdS.c_str(), len);
    }
    dosya.close();
}

void MainWindow::verileriYukle() {
    std::ifstream dosya("restoran_veri.dat", std::ios::binary);
    if (!dosya) return;
    for (int i = 0; i < 16; ++i) dosya.read(reinterpret_cast<char*>(&masaCirolari[i]), sizeof(double));
    size_t size;
    dosya.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    mutfakListesi.clear();
    for (size_t i = 0; i < size; ++i) {
        size_t len;
        dosya.read(reinterpret_cast<char*>(&len), sizeof(size_t));
        std::string temp(len, ' ');
        dosya.read(&temp[0], len);
        mutfakListesi.push_back(QString::fromStdString(temp));
    }
}

void MainWindow::mutfakEkraniniAc() {
    QDialog *d = new QDialog(this);
    d->setWindowTitle("Mutfak Listesi");
    d->setStyleSheet("background-color: #FAF0CA;");
    auto *v = new QVBoxLayout(d);
    auto *lw = new QListWidget(d);
    lw->setStyleSheet("color: #0D3B66; font-weight: bold;");
    for(const auto& s : mutfakListesi) lw->addItem(s);
    v->addWidget(lw);
    d->exec();
}

void MainWindow::grafikGoster() {
    auto *chart = new QChart();
    auto *series = new QBarSeries();
    auto *set = new QBarSet("Masa Ciroları");
    for (double ciro : masaCirolari) *set << ciro;
    series->append(set);
    chart->addSeries(series);
    chart->setTitle("Finansal Analiz Paneli");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto *axisX = new QBarCategoryAxis();
    QStringList categories;
    for(int i=1; i<=16; ++i) categories << QString("M%1").arg(i);
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis();
    axisY->setTitleText("Tutar (TL)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QDialog *gDialog = new QDialog(this);
    gDialog->resize(800, 600);
    auto *v = new QVBoxLayout(gDialog);
    v->addWidget(chartView);
    gDialog->exec();
}