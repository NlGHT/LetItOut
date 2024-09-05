#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QMouseEvent>
#include "customtitlebar.h"
#include <QSizeGrip>
#include <QShortcut>
#include <QSettings>

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow(QWidget *parent = nullptr);

	private slots:
		void onItemDoubleClicked(QListWidgetItem *item);
		void keyPressEvent(QKeyEvent *event) override;

	private:
		void setupUi();
        void toggleFullscreen();
		void resetFields();
		void toggleWindowDecorations();
		void saveAsTextFile();
		void onInputFieldSubmit();
        void addToList(const QString &text);
		void openFile();

		QWidget centralWidget;
		QVBoxLayout layout;
		QScrollArea scrollArea;
        QListWidget listWidget;
		QLineEdit inputField;
        CustomTitleBar* titleBar;
        bool titleBarVisible;
        QString defaultSaveDir;
        QSettings settings;


		QShortcut fullscreenShortcut;
		QShortcut borderlessShortcut;
};

#endif // MAINWINDOW_H
