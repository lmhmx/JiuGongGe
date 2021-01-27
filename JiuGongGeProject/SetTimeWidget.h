#pragma once
#include <qdialog.h>
#include "ui_SetTime.h"
class SetTimeWidget :
	public QDialog
{
	Q_OBJECT
public:
	SetTimeWidget(QDialog* parent = NULL);
	Ui::SetTimeWidget ui;
};

