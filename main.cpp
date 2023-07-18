#include <QApplication>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

    // Set the application icon for the window decoration
    QIcon icon(":/resources/resources/icon.ico");
    app.setWindowIcon(icon);

    MainWindow mainWindow;

    // Get the primary screen
    QScreen *screen = QGuiApplication::primaryScreen();

    // Get the geometry of the screen
    QRect screenGeometry = screen->geometry();

    // Load the previous window size from settings or use a default size
    QSettings settings("MyApp", "MyAppSettings");

    // Reset the window size settings for testing the default value
    // settings.remove("windowWidth");
    // settings.remove("windowHeight");

    int windowWidth = settings.value("windowWidth", screenGeometry.width() * 0.4).toInt();
    int windowHeight = settings.value("windowHeight", screenGeometry.height() * 0.6).toInt();

    // Set the window size
    mainWindow.resize(windowWidth, windowHeight);

    // Show the window
    mainWindow.show();

    // Save the window size when the application is closed
    QObject::connect(&app, &QGuiApplication::aboutToQuit, [&]() {
        settings.setValue("windowWidth", mainWindow.width());
        settings.setValue("windowHeight", mainWindow.height());
    });

	return app.exec();
}
