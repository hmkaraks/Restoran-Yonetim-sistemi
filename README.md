# 🍽️ RESYS - Profesyonel Restoran Yönetim Sistemi

**RESYS**, C++ ve Qt6 framework kullanılarak geliştirilmiş, yüksek performanslı ve modern bir restoran yönetim panelidir. Bu proje, üniversite teknik çalışmaları kapsamında hem yazılım mimarisi hem de kullanıcı deneyimi (UX) odaklı hazırlanmıştır.

## 🚀 Öne Çıkan Özellikler

*   **Asenkron Mutfak Yönetimi:** `QThread` kullanılarak hazırlanan mutfak simülasyonu sayesinde, siparişler arka planda hazırlanırken sistem akıcı bir şekilde çalışmaya devam eder.
*   **Modern Tasarım:** #0D3B66 (Lacivert) ve #FAF0CA (Krem) renk paleti ile göz yormayan, kurumsal ve şık bir arayüz.
*   **Finansal Analiz:** QtCharts entegrasyonu ile masaların ciro dağılımını gösteren dinamik grafikler.
*   **Güvenli Veri Saklama:** Veriler binary formatta (`.dat`) diskte saklanır, böylece uygulama kapatılsa bile siparişler ve cirolar kaybolmaz.
*   **Hata Yönetimi:** Giriş kontrolü, dosya okuma/yazma güvenliği ve dinamik bellek yönetimi.

## 🛠️ Teknik Detaylar

*   **Dil:** C++ 17
*   **Framework:** Qt 6.x
*   **Derleme Sistemi:** CMake
*   **Veri Yapıları:** `std::vector`, `std::string`, Binary File I/O

## 📦 Kurulum ve Çalıştırma

1.  Bilgisayarınızda **Qt 6** ve **CMake** kurulu olduğundan emin olun.
2.  Depoyu klonlayın:
    ```bash
    git clone [https://github.com/hmkaraks/Restoran-Yonetim-sistemi.git](https://github.com/hmkaraks/Restoran-Yonetim-sistemi.git)
    ```
3.  Proje klasörüne gidin ve CMake ile derleyin:
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```

## 📸 Ekran Görüntüleri

> *İpucu: Buraya projenin ekran görüntülerini ekleyebilirsin!*
> ![Uygulama Ekranı](ana-ekran.png)