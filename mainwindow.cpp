#include "mainwindow.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QLineEdit>
#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QFile>
#include <QDebug>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
	QFile File("style.qss");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());
	setStyleSheet(StyleSheet);
}

void MainWindow::onSubmitButtonClicked()
{
    QString inputText = inputField->text().trimmed();
    if (!inputText.isEmpty())
    {
        addToList(inputText);
        inputField->clear();
    }
}

void MainWindow::onItemDoubleClicked(QListWidgetItem *item)
{
	if (item) {
		QListWidget *listWidget = item->listWidget();
		listWidget->editItem(item);
	}
}
//
// Handle mouse press event

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	// Doesn't seem to work
    if (event->button() == Qt::LeftButton) {
        QListWidgetItem *selectedItem = listWidget->currentItem();
        if (selectedItem) {

        }
    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		if (listWidget->hasFocus()) {
			// Handle the escape key press event here
			listWidget->clearSelection();
			listWidget->clearFocus();
			inputField->setFocus();
		} else if (inputField->hasFocus()) {
			inputField->clearFocus();
			listWidget->focusWidget();
		}
	} else if (listWidget->hasFocus()) {
		auto currentItem = listWidget->currentItem();
		int currentItemIndex = listWidget->row(currentItem);
		if (event->key() == Qt::Key_K) {
			if (currentItemIndex > 0) {
				if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier)) {
					// Shift up pressed
					listWidget->takeItem(currentItemIndex);
					listWidget->insertItem(currentItemIndex - 1, currentItem);
					listWidget->setCurrentItem(currentItem);
				} else if (event->modifiers() == Qt::ControlModifier) {
					listWidget->setCurrentRow(currentItemIndex - 1);
				}
			}
		} else if (event->key() == Qt::Key_J) {
			if (currentItemIndex < listWidget->count() - 1) {
				// Shift down pressed
				if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier)) {
					listWidget->takeItem(currentItemIndex);
					listWidget->insertItem(currentItemIndex + 1, currentItem);
					listWidget->setCurrentItem(currentItem);
					std::cout << "CTRL SHIFT J" << std::endl;
				} else if (event->modifiers() == Qt::ControlModifier) {
					listWidget->setCurrentRow(currentItemIndex + 1);
				}
			}
		} else if (event->key() == Qt::Key_Return) {
			listWidget->editItem(currentItem);
		}
	} else if (event->key() == Qt::Key_Delete) {
		delete listWidget->currentItem();
	} else if (event->key() == Qt::Key_Tab) {
		if (!listWidget->hasFocus()) {
			listWidget->focusWidget();
		} else {
			inputField->focusWidget();
		}
	}
}



void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
}

void MainWindow::dropEvent(QDropEvent *event)
{

}

void MainWindow::setupUi()
{
	qDebug() << "SETUP UI";
    QWidget *centralWidget = new QWidget(this);
	centralWidget->setProperty("class", "main-layout");
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    listWidget = new QListWidget(this);
	listWidget->setDragEnabled(true);
	listWidget->setDragDropMode(QAbstractItemView::InternalMove);
	listWidget->setProperty("class", "list-widget");
    scrollArea->setWidget(listWidget);
    layout->addWidget(scrollArea);

    inputField = new QLineEdit(this);
    inputField->setMaxLength(80);
	inputField->setProperty("class", "input-field");
    connect(inputField, &QLineEdit::returnPressed, this, &MainWindow::onSubmitButtonClicked);
    layout->addWidget(inputField);

    setCentralWidget(centralWidget);

	inputField->setFocus();
}

void MainWindow::addToList(const QString &text)
{
    QListWidgetItem *item = new QListWidgetItem(text);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
    listWidget->addItem(item);
}
