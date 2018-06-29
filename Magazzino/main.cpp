#include <main.h>

void setup(QApplication &app);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    setup(a);

    Controller c;
    c.start();

    return a.exec();
}

//
// setup
//
void setup(QApplication &app)
{
    QCoreApplication::setApplicationName("Mathilde DB");
    app.setWindowIcon(QIcon(":/icon.png"));
    QFontDatabase::addApplicationFont(":/mathilde.ttf");
} // setup
