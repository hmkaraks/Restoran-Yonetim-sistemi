#ifndef DEPO_H
#define DEPO_H

#include <map>
#include <vector>
#include <optional>
#include <functional>

// Görev 1.2: Depo Şablon Sınıfı
template <typename K, typename T>
class Depo {
private:
    std::map<K, T> veriler;

public:
    void ekle(const K& anahtar, const T& deger) {
        veriler[anahtar] = deger;
    }

    std::optional<T> bul(const K& anahtar) const {
        if (auto it = veriler.find(anahtar); it != veriler.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    bool sil(const K& anahtar) {
        return veriler.erase(anahtar) > 0;
    }

    const std::map<K, T>& tumunu_al() const {
        return veriler;
    }

    // Lambda ile filtreleme
    std::vector<T> filtrele(std::function<bool(const T&)> kosul) const {
        std::vector<T> sonuclar;
        for (const auto& [anahtar, deger] : veriler) {
            if (kosul(deger)) {
                sonuclar.push_back(deger);
            }
        }
        return sonuclar;
    }
};

#endif