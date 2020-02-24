#include "viewwidget.h"
#include "Ellipse.h"
ViewWidget::ViewWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	draw_status_ = false;
	shape_ = NULL;
	type_ = Shape::kDefault;
	setMouseTracking(true);
}

ViewWidget::~ViewWidget()
{
}

void ViewWidget::setLine()
{
	type_ = Shape::kLine;
}

void ViewWidget::setRect()
{
	type_ = Shape::kRect;
}

void ViewWidget::setEllip()
{
	type_ = Shape::kEllipse;
}
void ViewWidget::setPoly() {
	type_ = Shape::kPolyLine;
}

void ViewWidget::setFree()
{
	type_ = Shape::kFree;
}

void ViewWidget::mousePressEvent(QMouseEvent* event)
{
	if (Qt::LeftButton == event->button())
	{
		switch (type_)
		{
		case Shape::kLine:
		case Shape::kFree:
			shape_ = new Line();
			break;
		case Shape::kDefault:
			break;

		case Shape::kRect:
			shape_ = new Rect();
			break;

		case Shape::kEllipse:
			shape_ = new Ellip();
			break;

		case Shape::kPolyLine:
			if (shape_ != NULL)
			{
				shape_list_.push_back(shape_);
			}
			draw_status_ = true;
			shape_ = new Line();
			start_point_ = end_point_ = event->pos();
			shape_->set_end(end_point_);
			shape_->set_start(start_point_); 
			break;
		}
		if (shape_ != NULL&&type_!=Shape::kPolyLine)
		{
			draw_status_ = true;
			start_point_ = end_point_ = event->pos();
			shape_->set_start(start_point_);
			shape_->set_end(end_point_);
		}
	}
	if (Qt::RightButton == event->button())
	{
		if (type_ == Shape::kPolyLine&&shape_!=NULL) {
			delete shape_;
			shape_ = NULL;
			draw_status_ = false;
		}
	}
	update();
}

void ViewWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (type_ == Shape::kFree && draw_status_ && shape_ != NULL)
	{
		end_point_ = event->pos();
		shape_->set_end(end_point_);
		shape_list_.push_back(shape_);
		shape_ = new Line();
		start_point_ = event->pos();
		shape_->set_start(start_point_);
	}
	if (draw_status_ && shape_ != NULL)
	{
		end_point_ = event->pos();
		shape_->set_end(end_point_);
	}
}

void ViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if(shape_!=NULL&&type_!=Shape::kPolyLine)
	{
		draw_status_ = false;
		shape_list_.push_back(shape_);
		shape_ = NULL;
	}
}

void ViewWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	for (int i = 0; i < shape_list_.size(); i++)
	{
		shape_list_[i]->Draw(painter);
	}

	if (shape_ != NULL) {
		shape_->Draw(painter);
	}

	update();
}