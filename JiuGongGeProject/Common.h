# ifndef COMMON_H
# define COMMON_H
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

	//未开始
	NOTSTART,
	//刚刚搜索完成
	SEARCHOVER,
	//正在手动恢复
	ALLOWMANUAL,
	//正在自动生成
	ALLOWAUTO,
	//自动状态下的停止状态
	STOPAUTO,
	//手动状态下的停止状态
	STOPMANUAL
};

# endif
