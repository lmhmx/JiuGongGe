#include "ShowImageWidget.h"
ShowImageWidget::ShowImageWidget(QWidget* parent):QWidget(parent)
{
	m_oldH = 3;
	m_oldW = 3;
	vector<int> map = { 1,2,3,4,5,6,7,8,0 };
	m_HasPicture = false;
	m_Changed = false;
	m_Map.initMap(3, 3);
	m_Map.setContent(map);
	m_Layout = NULL;
	ui.setupUi(this);
}
bool ShowImageWidget::Move(MyDirection direction)
{
	bool res = m_Map.Move(direction);
	showMap();
	return res;
}
void ShowImageWidget::clearMyPicture()
{
	m_HasPicture = false;
	showMap();
}

void ShowImageWidget::setMyPicture(const QPixmap& pic)
{
	m_Pi = pic;
	m_HasPicture = true;
	m_Changed = true;
	int w_window = this->width();
	int h_window = this->width();
	int w = m_Map.getWidth();
	int h = m_Map.getHeight();

	int labelw = w_window / w;
	int labelh = h_window / h;
	m_Pi = m_Pi.scaled(QSize(w_window, h_window));

	checkPic();
	
	showMap();
}
bool ShowImageWidget::setMap(Map map)
{
	if (m_Map.getWidth() != map.getWidth() || m_Map.getHeight() != map.getHeight())
	{
		m_oldW = m_Map.getWidth();
		m_oldH = m_Map.getHeight();
	}
	this->m_Map = map;
	this->showMap();
	return true;
}
bool ShowImageWidget::showMap()
{
	if (m_Layout == NULL)
	{
		m_Layout = new QGridLayout();
		m_Layout->setHorizontalSpacing(0);
		m_Layout->setVerticalSpacing(0);
		m_Layout;
		this->setLayout(m_Layout);
	}
	int mapW = m_Map.getWidth();
	int mapH = m_Map.getHeight();
	
	int labelW = this->width() / mapW;
	int labelH = this->height() / mapH;
	bool flag = false;

	if(mapH == m_labelMap.size())
	{
		if (mapW == m_labelMap[0].size())
		{
			flag = true;
		}
	}
	//大小改变了
	if (!flag)
	{
		//如果非空，先删除
		if (!m_labelMap.empty())
		{
			for (int i = 0; i < m_oldH; i++)
			{
				for (int j = 0; j < m_oldW; j++)
				{
					delete m_labelMap[i][j];
				}
				m_labelMap[i].clear();
			}
			m_labelMap.clear();
		}
		//开始申请空间

		m_labelMap.resize(mapH);
		for (int i = 0; i < mapH; i++)
		{
			m_labelMap[i].resize(mapW);
			for (int j = 0; j < mapW; j++)
			{
				m_labelMap[i][j] = new QLabel();
				m_labelMap[i][j]->setFrameStyle(1);
				//m_labelMap[i][j]->setFixedSize(labelW, labelH);
			}
		}
	}
	if (m_HasPicture == false)
	{
		for (int i = 0; i < mapH; i++)
		{
			for (int j = 0; j < mapW; j++)
			{
				if (m_Map.ContentRead(j, i) != 0)
				{
					m_labelMap[i][j]->setText(QString::number(m_Map.ContentRead(j, i)));
				}
				else
				{
					m_labelMap[i][j]->setText("");
				}
				QFont font;
				int fontsize = 26;
				if (mapH*mapW > 25 && mapH*mapW <= 100)
				{
					fontsize = 25 * 5 / mapW;
				}
				else if (mapH*mapW > 100)
				{
					fontsize = 18 * 5 / mapW;
				}
				font.setPointSize(fontsize);

				m_labelMap[i][j]->setFont(font);
				m_labelMap[i][j]->setAlignment(Qt::AlignCenter);
				m_Layout->addWidget(m_labelMap[i][j], i, j);
				qDebug() << m_Layout->cellRect(i, j).width() << " "
					<< m_Layout->cellRect(i, j).height();

			}
		}
	}
	else if (m_HasPicture == true)
	{
		checkPic();
		for (int i = 0; i < mapH; i++)
		{
			for (int j = 0; j < mapW; j++)
			{
				if (m_Map.ContentRead(j, i) != 0)
				{
					//m_labelMap[i][j]->setText(QString::number());
					int showNum = m_Map.ContentRead(j, i);
					m_labelMap[i][j]->setPixmap(*m_Pictures[showNum - 1]);
				}
				else
				{
					m_labelMap[i][j]->clear();
				}
				m_Layout->addWidget(m_labelMap[i][j], i, j);
				m_labelMap[i][j]->setFrameStyle(0);
				//qDebug() << m_Layout->cellRect(i, j).width() << " "
				//	<< m_Layout->cellRect(i, j).height();

			}
		}
	}
	return true;
}
void ShowImageWidget::checkPic()
{
	int mapH = m_Map.getHeight();
	int mapW = m_Map.getWidth();
	int labelW = (this->width()-20) / mapW;
	int labelH = (this->height()-20) / mapH;
	
	if (m_Pictures.size() != mapH * mapW || m_Changed == true)
	{
		qDebug() << "resize" << endl;
		for (int i = 0; i < m_Pictures.size(); i++)
		{
			delete m_Pictures[i];
		}
		m_Pictures.resize(mapH*mapW);
		for (int i = 0; i < mapW*mapH; i++)
		{
			m_Pictures[i] = new QPixmap();
			*m_Pictures[i] = m_Pi.copy(i%mapW*labelW, i / mapW * labelH,
				labelW, labelH);
		}
	}
	m_Changed = false;
}

int ShowImageWidget::getMapWidth()
{
	return this->m_Map.getWidth();
}
const Map& ShowImageWidget::getMap()
{
	return this->m_Map;
}

int ShowImageWidget::getMapHeight()
{
	return this->m_Map.getHeight();
}
void ShowImageWidget::paintEvent(QPaintEvent*)
{
	showMap();
}
