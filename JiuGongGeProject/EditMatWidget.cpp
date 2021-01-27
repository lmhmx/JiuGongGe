#include "EditMatWidget.h"
EditMatWidget::EditMatWidget(const Map& map, QWidget* parent) :QWidget(parent)
{
	int w = map.getWidth();
	int h = map.getHeight();
	this->m_map = map;
	ui.setupUi(this);
	m_Layout = new QGridLayout();
	m_LineEdit = new QLineEdit**[h];
	ui.widget_map->setLayout(m_Layout);
	for (int i = 0; i < h; i++)
	{
		m_LineEdit[i] = new QLineEdit*[w];
		for (int j = 0; j < w; j++)
		{
			m_LineEdit[i][j] = new QLineEdit();
			m_LineEdit[i][j]->setText(QString::number(m_map.ContentRead(j,i)));
			m_Layout->addWidget(m_LineEdit[i][j], i, j);
		}
	}
	
}
void EditMatWidget::closeEvent(QCloseEvent* Event)
{
	this->deleteLater();
}
