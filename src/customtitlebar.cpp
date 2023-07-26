#include "customtitlebar.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QFile>

#include <iostream>

CustomTitleBar::CustomTitleBar(QWidget* parent) : QWidget(parent),
	titleLabel(" ", this),
	minimizeButton("-", this),
	maximizeButton("+", this),
	closeButton("x", this),
	layout(this)
{
    QFile qssFile(":/qss/style.qss");
	QString qss;
    if (qssFile.open(QFile::ReadOnly)) {
        qss = qssFile.readAll();
		setStyleSheet(qss);
    }

	titleLabel.setObjectName("titleLabel");
	titleLabel.setProperty("class", "title-label");

	minimizeButton.setProperty("class", "title-button");
    connect(&minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::minimizeWindow);

	maximizeButton.setProperty("class", "title-button");
    connect(&maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::maximizeWindow);

	closeButton.setProperty("class", "title-button");
    connect(&closeButton, &QPushButton::clicked, this, &CustomTitleBar::closeWindow);

	layout.setProperty("class", "title-layout");
	layout.addWidget(&titleLabel);
	layout.addStretch(1); // Add the gap so that buttons appear on the right
    layout.addWidget(&minimizeButton);
    layout.addWidget(&maximizeButton);
    layout.addWidget(&closeButton);

    setLayout(&layout);
}

void CustomTitleBar::minimizeWindow() {
    nativeParentWidget()->showMinimized();
}

void CustomTitleBar::maximizeWindow() {
    if (nativeParentWidget()->isMaximized()) {
        nativeParentWidget()->showNormal();
    } else {
        nativeParentWidget()->showMaximized();
    }
}

void CustomTitleBar::closeWindow() {
    nativeParentWidget()->close();
}

void CustomTitleBar::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
        startPos = event->pos();
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = event->pos() - startPos;
        nativeParentWidget()->move(nativeParentWidget()->pos() + delta);
    }
}
