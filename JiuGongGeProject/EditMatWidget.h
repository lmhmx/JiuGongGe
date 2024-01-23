#pragma once
#include <qwidget.h>
#include <qgridlayout.h>
#include <qlineedit.h>
#include <qevent.h>
#include "Map.h"
#include "ui_EditMat.h"
class EditMatWidget:public QWidget
{
	//Q_OBJECT
public:
	EditMatWidget(const Map& map, QWidget* parent = NULL);
	Ui::EditMatWidget ui;
	Map m_map;
	QGridLayout* m_Layout;
	QLineEdit*** m_LineEdit;
protected:
	void closeEvent(QCloseEvent* Event);

};

