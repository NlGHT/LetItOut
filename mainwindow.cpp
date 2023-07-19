#include "mainwindow.h"
#include "customtitlebar.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QLineEdit>
#include <QFile>
#include <QResource>
#include <QShortcut>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
	setMouseTracking(true);
	setWindowFlag(Qt::FramelessWindowHint);
    QResource::registerResource("://resources.qrc");
    QFile qssFile(":/qss/style.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString qss = qssFile.readAll();
        setStyleSheet(qss);
    }

    // Set the application icon for the window decoration
    QIcon icon(":/resources/resources/icon.ico");
    setWindowIcon(icon);

    QShortcut *fullscreenShortcut = new QShortcut(Qt::Key_F11, this);
    connect(fullscreenShortcut, &QShortcut::activated, this, &MainWindow::toggleFullscreen);

    QShortcut *borderlessShortCut = new QShortcut(Qt::Key_F12, this);
    connect(borderlessShortCut , &QShortcut::activated, this, &MainWindow::toggleWindowDecorations);

	titleBarVisible = true;
}

void MainWindow::onItemDoubleClicked(QListWidgetItem *item)
{
	if (item) {
		QListWidget *listWidget = item->listWidget();
		listWidget->editItem(item);
	}
}
//
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
    } else  if (event->key() == Qt::Key_R || event->key() == Qt::Key_F5) {
		resetFields();
	} else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S) {
		saveAsTextFile();
	} else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_O) {
		openFile();
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
				} else if (event->modifiers() == Qt::ControlModifier) {
					listWidget->setCurrentRow(currentItemIndex + 1);
				}
			}
		} else if (event->key() == Qt::Key_Return) {
			listWidget->editItem(currentItem);
		} else if (event->key() == Qt::Key_Delete) {
			delete listWidget->currentItem();
		}
	}  else if (event->key() == Qt::Key_Tab) {
		if (!listWidget->hasFocus()) {
			listWidget->focusWidget();
		} else {
			inputField->focusWidget();
		}
	}
}

void MainWindow::setupUi()
{
	qDebug() << "SETUP UI";
	QWidget *centralWidget = new QWidget(this);
	centralWidget->setProperty("class", "main-layout");
	layout = new QVBoxLayout(centralWidget);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	titleBar = new CustomTitleBar(this);
	layout->addWidget(titleBar);

	scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);

	listWidget = new QListWidget(this);
	listWidget->setDragEnabled(true);
	listWidget->setDragDropMode(QAbstractItemView::InternalMove);
	listWidget->setProperty("class", "list-widget");
	listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setWidget(listWidget);
	layout->addWidget(scrollArea);

	inputField = new QLineEdit(this);
	inputField->setMaxLength(100);
	inputField->setProperty("class", "input-field");
	connect(inputField, &QLineEdit::returnPressed, this, &MainWindow::onInputFieldSubmit);
	layout->addWidget(inputField);

	setCentralWidget(centralWidget);

	inputField->setFocus();
}

void MainWindow::toggleFullscreen()
{
    if (isFullScreen())
        showNormal();
    else
        showFullScreen();
}

void MainWindow::resetFields()
{
	listWidget->clear();
	inputField->clear();
}

void MainWindow::toggleWindowDecorations() {
    if (titleBarVisible) {
        // Hide the title bar
        layout->removeWidget(titleBar);
        titleBar->hide();
        titleBarVisible = false;
    } else {
        // Show the title bar
        layout->insertWidget(0, titleBar);
        titleBar->show();
        titleBarVisible = true;
    }
}

void MainWindow::saveAsTextFile()
{
	if (listWidget->count() > 0) {
		// Prompt for the "Save As" window
		// Prompt for "Save As" window
		QFileDialog dialog(nullptr, "Save As");
		dialog.setDefaultSuffix("txt");
		dialog.setAcceptMode(QFileDialog::AcceptSave);
		dialog.setNameFilter("Text Files (*.txt);;All Files (*)");

		if (dialog.exec() != QDialog::Accepted) {
			// User canceled the save operation or didn't specify a file
			return;
		}

		QStringList filePaths = dialog.selectedFiles();
		QString filePath = filePaths.first();

		QFile file(filePath);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			// Failed to open the file
			QMessageBox::critical(nullptr, "Error", "Failed to open the file for writing.");
			return;
		}

		QTextStream out(&file);
		for (int i = 0; i < listWidget->count(); ++i) {
			QListWidgetItem* item = listWidget->item(i);
			out << item->text() << "\n";
		}

		file.close();
	}
}

void MainWindow::onInputFieldSubmit()
{
	QString inputText = inputField->text().trimmed();
	if (!inputText.isEmpty())
	{
		addToList(inputText);
		inputField->clear();
	}
}

void MainWindow::addToList(const QString &text)
{
	QListWidgetItem *item = new QListWidgetItem(text);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
	listWidget->addItem(item);
	listWidget->scrollToBottom();
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Text File"), QString(), tr("Text Files (*.txt)"));
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
			std::vector<QString> fileLines;
            while (!in.atEnd())
            {
                QString line = in.readLine().trimmed();
				if (line.length() > 0)
					fileLines.push_back(line);
            }

			if (fileLines.size() > 0)
			{
				// Initialise to yes because if the listWidget size is 0 then no confirmation needed
				QMessageBox::StandardButton reply = QMessageBox::Yes;
				if (listWidget->count() > 0)
				{
					// Ask for confirmation
					reply = QMessageBox::question(this, tr("Confirmation"), tr("Are you sure you want to replace everything?"), QMessageBox::Yes | QMessageBox::No);
				}

				if (reply == QMessageBox::Yes)
				{
					resetFields();

					for (const QString &line : fileLines)
					{
						addToList(line);
					}
				}
			}

            file.close();
        }
    }
}
