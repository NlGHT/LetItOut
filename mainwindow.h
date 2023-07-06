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
			void onSubmitButtonClicked();
		void onItemDoubleClicked(QListWidgetItem *item);
		// Event handlers
		void dragEnterEvent(QDragEnterEvent *event) override;
		void dragMoveEvent(QDragMoveEvent *event) override;
		void dropEvent(QDropEvent *event) override;
		void keyPressEvent(QKeyEvent *event) override;

	private:
		void setupUi();
        void addToList(const QString &text);
        void toggleFullscreen();

		QScrollArea *scrollArea;
		QListWidget *listWidget;
		QLineEdit *inputField;

	protected:
		void mousePressEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
