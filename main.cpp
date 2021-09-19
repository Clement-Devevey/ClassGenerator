#include<QApplication>
#include"fenprincipal.h"
#include"fensecondaire.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    fenPrincipal maFenetre;
    maFenetre.setWindowTitle("Class generator");
    maFenetre.show();
    return app.exec();
}
