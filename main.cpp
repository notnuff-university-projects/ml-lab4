#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.setWindowTitle("Керування обігрівачем (Нечітка логіка)");
    window.resize(600, 200);
    window.show();
    
    return app.exec();
} 