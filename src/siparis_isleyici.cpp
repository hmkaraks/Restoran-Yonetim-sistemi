#include "../include/siparis_isleyici.h"

SiparisIsleyici::SiparisIsleyici(QString siparisBilgisi, QObject *parent)
    : QThread(parent), m_bilgi(siparisBilgisi) {}

void SiparisIsleyici::run() {
    // Mutfakta yemek hazırlanıyor simülasyonu
    // Ana ekranı dondurmadan arka planda bekler
    msleep(10000); // 10 saniye bekle
    emit siparisHazir(m_bilgi); // Ana pencereye "Yemek pişti!" mesajı gönder
}