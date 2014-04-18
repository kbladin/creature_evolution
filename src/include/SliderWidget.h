#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QString>


class SliderWidget : public QWidget {
	Q_OBJECT

public:
	SliderWidget(QString label_text, int default_value, int range, int step, int page, int tick);
	~SliderWidget(){};

signals:
	void valueChanged(int new_value);

private slots:
	void setValue(int value);

private:
	QSlider* slider_;
	QLabel* label_text_;
	QLabel* label_value_;

	QVBoxLayout* vbox_;
	QHBoxLayout* label_layout_;

	int value_;
};


#endif // SLIDERWIDGET_H 