#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void mutfakEkraniniAc();
    void grafikGoster();
    void verileriKaydet();   // Binary Kaydetme
    void verileriYukle();    // Binary Yükleme
    void mutfaktanHaberGeldi(QString bilgi); // Thread Sinyali

private:
    void arayuzuKur();
    void menuOlustur();

    std::vector<QString> mutfakListesi;
    std::vector<double> masaCirolari;
};

#endif