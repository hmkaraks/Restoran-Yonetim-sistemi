#ifndef VARLIKLAR_H
#define VARLIKLAR_H

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <iomanip>

// Görev 1.1: Enum Class Tanımı
enum class SiparisDurum { Hazirlaniyor, Hazir, TeslimEdildi, Iptal };

inline std::string durumToString(SiparisDurum d) {
    switch(d) {
        case SiparisDurum::Hazirlaniyor: return "Hazirlaniyor";
        case SiparisDurum::Hazir: return "Hazir";
        case SiparisDurum::TeslimEdildi: return "Teslim Edildi";
        case SiparisDurum::Iptal: return "Iptal";
        default: return "Bilinmiyor";
    }
}

// Görev 1.1: Varlık Struct'ları
struct MenuItem {
    int urun_id{};
    std::string urun_adi;
    std::string kategori;
    double fiyat{};

    // Akış çıkış operatörü
    friend std::ostream& operator<<(std::ostream& os, const MenuItem& m) {
        return os << "[" << m.urun_id << "] " << std::left << std::setw(18)
                  << m.urun_adi << " | " << std::setw(10) << m.kategori << " | " << m.fiyat << " TL";
    }
};

struct SiparisKalemi {
    int urun_id{};
    int adet{};
    std::optional<std::string> notlar; // std::optional kullanımı
};

struct Siparis {
    int siparis_id{};
    int masa_no{};
    std::string tarih_saat;
    std::vector<SiparisKalemi> kalemler;
    SiparisDurum durum{SiparisDurum::Hazirlaniyor};

    friend std::ostream& operator<<(std::ostream& os, const Siparis& s) {
        os << "Siparis ID: " << s.siparis_id << " | Masa: " << s.masa_no
           << " | Durum: " << durumToString(s.durum) << " | Kalem Sayisi: " << s.kalemler.size();
        return os;
    }
};

struct StokMalzeme {
    int malzeme_id{};
    std::string malzeme_adi;
    double miktar{};
    std::string birim;
    double minimum_stok{};

    friend std::ostream& operator<<(std::ostream& os, const StokMalzeme& s) {
        return os << std::left << std::setw(15) << s.malzeme_adi << ": "
                  << s.miktar << " " << s.birim << " (Min: " << s.minimum_stok << ")";
    }
};

#endif