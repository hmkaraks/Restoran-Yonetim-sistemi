#include <QApplication>
#include "../include/mainwindow.h"
#include "../include/logindialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LoginDialog login;
    // Giriş başarılı değilse program hiç açılmaz
    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}