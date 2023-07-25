#ifndef CUSTOMTITLEBAR_H
#define CUSTOMTITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class CustomTitleBar : public QWidget
{
    Q_OBJECT

	public:
		CustomTitleBar(QWidget* parent = nullptr);

	protected:
		void mousePressEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;

	private slots:
		void minimizeWindow();
		void maximizeWindow();
		void closeWindow();

	private:
		QPoint startPos;
		QLabel titleLabel;
		QPushButton minimizeButton;
		QPushButton maximizeButton;
		QPushButton closeButton;
		QHBoxLayout layout;
};

#endif // CUSTOMTITLEBAR_H
