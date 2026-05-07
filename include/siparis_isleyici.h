#ifndef SIPARIS_ISLEYICI_H
#define SIPARIS_ISLEYICI_H

#include <QThread>
#include <QString>

class SiparisIsleyici : public QThread {
    Q_OBJECT
public:
    explicit SiparisIsleyici(QString siparisBilgisi, QObject *parent = nullptr);
    void run() override; // Thread'in yapacağı iş burada tanımlanır

    signals:
        void siparisHazir(QString bilgi); // İş bitince ana ekrana haber verir

private:
    QString m_bilgi;
};

#endif