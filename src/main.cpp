#include <QApplication>
#include <QSettings>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
	QApplication app(argc, argv);

    MainWindow mainWindow;

    // Get the primary screen
    QScreen *screen = QGuiApplication::primaryScreen();

    // Get the geometry of the screen
    QRect screenGeometry = screen->geometry();

    // Load the previous window size from settings or use a default size
    QSettings settings("LetItOut", "LetItOutSettings");

    // Reset the window size settings for testing the default value
    // settings.remove("windowWidth");
    // settings.remove("windowHeight");

    int windowWidth = settings.value("windowWidth", screenGeometry.width() * 0.4).toInt();
    int windowHeight = settings.value("windowHeight", screenGeometry.height() * 0.6).toInt();

    // Set the window size
    mainWindow.resize(windowWidth, windowHeight);

    // Get the primary screen or the first available screen
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    if (!primaryScreen) {
        qFatal("No screen found!");
    }

    // Calculate the position to place the window at the center of the screen
    int xPos = (screenGeometry.width() - mainWindow.width()) / 2;
    int yPos = (screenGeometry.height() - mainWindow.height()) / 2;

    // Move the window to the calculated position
    mainWindow.move(xPos, yPos);

    // Show the window
    mainWindow.show();

    // Save the window size when the application is closed
    QObject::connect(&app, &QGuiApplication::aboutToQuit, [&]() {
        settings.setValue("windowWidth", mainWindow.width());
        settings.setValue("windowHeight", mainWindow.height());
    });

	return app.exec();
}
