#pragma once
#include "ui_SetSize.h"
#include <qwidget.h>
class SetSizeWidget:public QWidget
{
	//Q_OBJECT
public:
	SetSizeWidget(QWidget* parent = NULL);
	Ui::SetSizeWidget ui;
protected:
	void closeEvent(QCloseEvent* Event);
};
