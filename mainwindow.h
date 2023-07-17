#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QMouseEvent>

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

		QScrollArea *scrollArea;
		QListWidget *listWidget;
		QLineEdit *inputField;

	protected:
};

#endif // MAINWINDOW_H
