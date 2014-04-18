#include "SliderWidget.h"


SliderWidget::SliderWidget(QString label_text,int default_value, int range, int step, int page, int tick) {
	value_ = default_value;

	vbox_ = new QVBoxLayout;
	label_text_ = new QLabel(label_text);
	label_value_ = new QLabel(QString::number(value_));

	label_layout_ = new QHBoxLayout;
	label_layout_->addWidget(label_text_);
	label_layout_->addWidget(label_value_);

	slider_ = new QSlider(Qt::Horizontal);
	slider_->setRange(0, range);
  slider_->setSingleStep(step);
  slider_->setPageStep(page);
  slider_->setTickInterval(tick);
  slider_->setTickPosition(QSlider::TicksRight);
  slider_->setSliderPosition(default_value);

  vbox_->addLayout(label_layout_);
  vbox_->addWidget(slider_);

  setLayout(vbox_);
  adjustSize();
  connect(slider_, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
}


void SliderWidget::setValue(int value) {
	value_ = value;
	label_value_->setText(QString::number(value));
	emit valueChanged(value_);
}

//int SliderWidget::valueChanged(int new_value) {}