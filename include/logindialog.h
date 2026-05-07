#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

class LoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("RESYS Güvenli Giriş");
        setFixedSize(300, 180);

        auto *layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Kullanıcı Adı: (admin)"));
        userEdit = new QLineEdit(this);
        layout->addWidget(userEdit);

        layout->addWidget(new QLabel("Şifre: (1234)"));
        passEdit = new QLineEdit(this);
        passEdit->setEchoMode(QLineEdit::Password);
        layout->addWidget(passEdit);

        auto *btn = new QPushButton("Sisteme Giriş", this);
        btn->setStyleSheet("background-color: #3498db; color: white; font-weight: bold;");
        layout->addWidget(btn);

        connect(btn, &QPushButton::clicked, this, &LoginDialog::checkLogin);
    }

private slots:
    void checkLogin() {
        if (userEdit->text() == "admin" && passEdit->text() == "1234") accept();
        else QMessageBox::warning(this, "Hata", "Giriş bilgileri hatalı!");
    }

private:
    QLineEdit *userEdit;
    QLineEdit *passEdit;
};

#endif