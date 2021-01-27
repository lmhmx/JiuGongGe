#pragma once
#include <iostream>
#include "Common.h"
#include <iomanip>

using namespace std;
class Map
{
public:
	Map();
	Map(const Map& map);
	Map(int width, int height);
	Map(int width, int height, vector<int> m_Content);
	~Map();
	Map& operator=(const Map& map);

	bool operator==(const Map& map)const;
	bool operator<(const Map& map);
	bool initMap(int width = 3, int height = 3);

	int getWidth()const;
	int getHeight()const;
	vector<int> getContent()const;
	bool setContent(vector<int> content);

	//将图形挪向0的位置
	//如果成功能够挪动，那么返回 true，否则返回 false
	bool Move(MyDirection diretion);
	MyDirection operator-(const Map& map);
	int getIndex(int x)const;


public:
	static bool checkContent(int width, int height, vector<int>& content);

public:
	const int& ContentRead(int x, int y)const;
	const int& ContentRead(int x, int y);
private:
	int& Content(int x, int y);

	void ConfirmPos();
private:
	
	int m_Width;
	int m_Height;
	vector<int> m_Content;
	vector<int> m_Pos;
};

void printMap(Map m);