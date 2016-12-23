#include <QApplication>
#include "primawindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PrimaWindow *a = new PrimaWindow();
    return app.exec();
}

