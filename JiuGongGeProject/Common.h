#pragma once
#include <iostream>
#include <vector>
#include <list>

enum MyDirection
{
	UP, DOWN, LEFT, RIGHT, ERRORDIRECTION
};
enum SearchType
{
	DEEPSEARCH,
	WIDTHSEARCH,
	ASEARCH,
	PROGRAMSEARCH
};
enum JIUGONGGESTATE
{

	//δ��ʼ
	NOTSTART,
	//�ո��������
	SEARCHOVER,
	//�����ֶ��ָ�
	ALLOWMANUAL,
	//�����Զ�����
	ALLOWAUTO,
	//�Զ�״̬�µ�ֹͣ״̬
	STOPAUTO,
	//�ֶ�״̬�µ�ֹͣ״̬
	STOPMANUAL
};
