#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include <qtimer.h>
#include <qdebug.h>
#include <qlabel.h>
#include <iostream>
#include <qdebug.h>
#include <qlayout.h>
#include <qgridlayout.h>
#include <qimage.h>
#include <qpixmap.h>
#include "Common.h"
#include "ui_ShowImage.h"
#include "Map.h"
class ShowImageWidget :
	public QWidget
{
	Q_OBJECT

public:
	ShowImageWidget(QWidget* parent = Q_NULLPTR);
	//bool setMySize(int height, int width);

	bool Move(MyDirection direction);

	void paintEvent(QPaintEvent*);
	
	bool showMap();

	bool setMap(Map map);
	int getMapWidth();
	int getMapHeight();

	const Map& getMap();
	void setMyPicture(const QPixmap& pic);
	void clearMyPicture();
private:
	Ui::ShowImageClass ui;

private:
	Map m_Map;

private:
	QGridLayout* m_Layout;
	vector<vector<QLabel*>> m_labelMap;
	void checkPic();

private:
	int m_oldW;
	int m_oldH;
private:
	//QImage m_Img;
	vector<QPixmap*> m_Pictures;
	QPixmap m_Pi;
	bool m_HasPicture;
	bool m_Changed;
};
