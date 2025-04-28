#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("IMPP - Image Format Converter");
    app.setOrganizationName("Augment Projects");
    
    MainWindow mainWindow;
    mainWindow.setWindowTitle("IMPP - Image Format Converter");
    mainWindow.resize(800, 600);
    mainWindow.show();
    
    return app.exec();
}
