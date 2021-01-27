#include "SetSizeWidget.h"
SetSizeWidget::SetSizeWidget(QWidget* parent):QWidget(parent)
{
	ui.setupUi(this);
}
void SetSizeWidget::closeEvent(QCloseEvent* Event)
{
	this->deleteLater();
}
