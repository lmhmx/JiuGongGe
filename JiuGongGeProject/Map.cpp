#include "Map.h"
using namespace std;
Map::Map()
{
	
}
Map::Map(const Map& map)
{
	m_Content = map.m_Content;
	m_Pos = map.m_Pos;
	m_Height = map.m_Height;
	m_Width = map.m_Width;
}
Map::~Map()
{
	m_Content.clear();
	m_Pos.clear();
}
Map::Map(int width, int height, vector<int> Content)
{
	if (width > 1 && height > 1 && Content.size() == width * height)
	{
		m_Height = height;
		m_Width = m_Width;
		m_Content = Content;
		if (checkContent(width, height, Content))
		{
			cout << "init data error" << endl;
			system("pause");
		}
		else
		{
			ConfirmPos();
		}
	}
}

Map::Map(int width, int height)
{
	m_Content.resize(width*height);
	m_Pos.resize(width*height);
	m_Width = width;
	m_Height = height;
}
void Map::ConfirmPos()
{
	m_Pos = m_Content;
	for (int i = 0; i < m_Content.size(); i++)
	{
		m_Pos[m_Content[i]] = i;
	}
}


MyDirection Map::operator-(const Map& map)
{
	int thism_0X = getIndex(0)%m_Width;
	int thism_0Y = getIndex(0)/m_Width;
	int mapm_0X = map.getIndex(0) % map.m_Width;
	int mapm_0Y = map.getIndex(0) / map.m_Width;
	if (thism_0X - mapm_0X == 1 && thism_0Y - mapm_0Y == 0)
	{
		return LEFT;
	}
	else if (thism_0X - mapm_0X == -1 && thism_0Y - mapm_0Y == 0)
	{
		return RIGHT;
	}
	else if (thism_0X - mapm_0X == 0 && thism_0Y - mapm_0Y == 1)
	{
		return UP;
	}
	else if (thism_0X - mapm_0X == 0 && thism_0Y - mapm_0Y == -1)
	{
		return DOWN;
	}
	else
	{
		return ERRORDIRECTION;
	}
}

bool Map::operator<(const Map& map)
{
	if (map.m_Height == this->m_Height && map.m_Width == this->m_Width)
	{
		for (int i = 0; i < map.m_Height * map.m_Width; i++)
		{
			if (this->m_Content[i] < map.m_Content[i])
			{
				return true;
			}
			else if (this->m_Content[i] > map.m_Content[i])
			{
				return false;
			}
		}
	}
	return false;
}
bool Map::operator==(const Map& map)const
{
	if (map.m_Height == this->m_Height && map.m_Width == this->m_Width)
	{
		for (int i = 0; i < map.m_Height*map.m_Width; i++)
		{
			if (map.m_Content[i] != this->m_Content[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}


bool Map::initMap(int width, int height)
{
	if (width > 1 && height > 1)
	{
		m_Width = width;
		m_Height = height;
		m_Content.resize(width* height);
		m_Pos.resize(width*height);
	}
	else
	{
		cout << "error bool Map::initMap(int width, int height)" << endl;
		system("pause");
		return false;
	}
	return true;
}

int Map::getWidth()const
{
	return this->m_Width;
}
int Map::getHeight()const
{
	return this->m_Height;
}
int Map::getIndex(int x)const
{
	return m_Pos[x];
}

vector<int> Map::getContent()const
{
	return this->m_Content;
}
bool Map::setContent(vector<int> content)
{
	if (content.size() != this->m_Height * this->m_Width)
	{
		//cout << "error setContent(vector<int> content)" << endl;
		//system("pause");
		return false;
	}
	m_Content = content;
	if (checkContent(m_Width, m_Height, m_Content) == false)
	{
		//cout << "error setContent(vector<int> content)" << endl;
		//system("pause");
		return false;
	}
	ConfirmPos();
	return true;
}

Map& Map::operator=(const Map& map)
{
	m_Content = map.m_Content;
	m_Pos = map.m_Pos;
	m_Height = map.m_Height;
	m_Width = map.m_Width;
	return *this;
}
bool Map::checkContent(int width, int height, vector<int>& content)
{
	if (!(width > 1 && height > 1 && width * height == content.size()))
	{
		return false;
	}
	bool* check = new bool[width * height];
	for (int i = 0; i < width*height; i++)
	{
		check[i] = false;
	}
	for (int i = 0; i < height * width; i++)
	{
		if (content[i] < height*width && content[i] >= 0)
		{
			if (check[content[i]] == true)
			{
				return false;
			}
			else
			{
				check[content[i]] = true;
			}
		}
		else
		{
			return false;
		}
	}
	delete[] check;
	return true;
}
const int& Map::ContentRead(int x, int y)const
{
	return m_Content[x + y*m_Width];
}
const int& Map::ContentRead(int x, int y)
{
	return m_Content[x + y * m_Width];
}
int& Map::Content(int x, int y)
{
	return m_Content[x + y * m_Width];
}
//将图形挪向0的位置
//如果成功能够挪动，那么返回 true，否则返回 false
bool Map::Move(MyDirection direction)
{
	int tmp;
	int Tm_0X = this->getIndex(0) % m_Width;
	int Tm_0Y = this->getIndex(0) / m_Width;
	switch (direction)
	{
	case UP:
	{
		if (Tm_0Y == m_Height - 1)
		{
			printMap(*this);
			//cout << "UP" << endl;
			return false;
		}
		else
		{
			Content(Tm_0X,Tm_0Y) = Content(Tm_0X, Tm_0Y + 1);
			Content(Tm_0X, Tm_0Y + 1) = 0;
			m_Pos[0] = Tm_0X + (Tm_0Y + 1) * m_Width;
			m_Pos[Content(Tm_0X, Tm_0Y)] = Tm_0X + Tm_0Y * m_Width;
		}
		break;
	}
	case DOWN:
	{
		if (Tm_0Y == 0)
		{
			printMap(*this);
			//cout << "UP" << endl;
			return false;
		}
		else
		{
			Content(Tm_0X, Tm_0Y) = Content(Tm_0X, Tm_0Y - 1);
			Content(Tm_0X, Tm_0Y - 1) = 0;
			m_Pos[0] = Tm_0X + (Tm_0Y - 1) * m_Width;
			m_Pos[Content(Tm_0X, Tm_0Y)] = Tm_0X + Tm_0Y * m_Width;

		}
		break;
	}
	case LEFT:
	{
		if (Tm_0X == m_Width - 1)
		{
			printMap(*this);
			//cout << "UP" << endl;
			return false;
		}
		else
		{
			Content(Tm_0X, Tm_0Y) = Content(Tm_0X + 1, Tm_0Y);
			Content(Tm_0X + 1, Tm_0Y) = 0;
			m_Pos[0] = Tm_0X + 1 + Tm_0Y * m_Width;
			m_Pos[Content(Tm_0X, Tm_0Y)] = Tm_0X + Tm_0Y * m_Width;

		}
		break;
	}
	case RIGHT:
	{
		if (Tm_0X == 0)
		{
			printMap(*this);
			//cout << "UP" << endl;
			return false;
		}
		else
		{
			Content(Tm_0X, Tm_0Y) = Content(Tm_0X - 1, Tm_0Y);
			Content(Tm_0X - 1, Tm_0Y) = 0;
			m_Pos[0] = Tm_0X - 1 + Tm_0Y * m_Width;
			m_Pos[Content(Tm_0X, Tm_0Y)] = Tm_0X + Tm_0Y * m_Width;
		}
		break;
	}
	default:
		cout << "error Move(MyDirection direction)" << endl;
		system("pause");
		break;
	}

	return true;
}


void printMap(Map m)
{
	return;
	for (int i = 0; i < m.getHeight(); i++)
	{
		for (int j = 0; j < m.getWidth(); j++)
		{
			cout << setw(4) << m.ContentRead(j, i) << "  ";
		}
		cout << endl;
	}
}
