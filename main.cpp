#include <Window/include/Window.hpp>
#include <QApplication>

int main(int argc, char *argv[]) {
    QCoreApplication::setApplicationName("MyCalculator");

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(QApplication::applicationDirPath() + "icon.png"));
    app.setApplicationDisplayName("MyCalculator");

    Window window;
    window.setWindowTitle(qApp->applicationName());
    window.setWindowIcon(qApp->windowIcon());
    window.show();
    return app.exec();
}
