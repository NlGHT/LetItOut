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
#include <cstdio>
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
    if (event->button() == Qt::LeftButton) {
        QListWidgetItem *selectedItem = listWidget->currentItem();
        if (selectedItem) {

        }
    }

    QMainWindow::mousePressEvent(event);
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
    QWidget *centralWidget = new QWidget(this);
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
    inputField->setMaxLength(100);
	inputField->setProperty("class", "input-field");
    connect(inputField, &QLineEdit::returnPressed, this, &MainWindow::onSubmitButtonClicked);
    layout->addWidget(inputField);

    setCentralWidget(centralWidget);
}

void MainWindow::addToList(const QString &text)
{
    QListWidgetItem *item = new QListWidgetItem(text);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
    listWidget->addItem(item);
}
