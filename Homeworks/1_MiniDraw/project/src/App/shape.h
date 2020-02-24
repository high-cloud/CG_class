#pragma once

#include <QtGui>

class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual void Draw(QPainter &paint)=0;

public:
	enum Type
	{
		kDefault = 0,
		kLine=1,
		kRect=2,
		kEllipse=3,
		kPolyLine=4,
		kFree=5,
	};
	
protected:
	QPoint start;
	QPoint end;
};
