#pragma once
#include "Common.h"
#include "Map.h"
#include <time.h>
#include <queue>
#include <map>
#include "JiuGongGeProject.h"
using namespace std;

class Node
{
public:
	Node();
	Node(const Node& node);
	~Node();
	Node& operator=(const Node& node);
	Map map;
	int getParentNum();
	Node* getParent();
	void setParent(Node* parent);
private:
	Node* parent;
	int m_ParentsNum;
};

class Solution
{
public:
	//传进来的参数为开始状态，结束状态，succeed 是能不能找到最终答案，
	//如果不能找到，返回false
	//由于存在最终的两种状态，ctrl为0表示强制要求最终结果最终完全符合
	//ctrl为1，那么就算不成功，返回一个左下角的两个与最终相反的路径
	//timeOrSpaceOut 是搜索失败的原因
	Solution();
	vector<MyDirection> getSolution(const Map& beginMap, const Map& finishMap, 
		bool& succeed, SearchType searchType, int ctrl, bool& timeOrSpaceOut);
	bool setMaxTime(int maxTime);
	int getMaxTime();
private:
	vector<MyDirection> widthSearchSolution(const Map& beginMap,
		const Map& finishMap, bool& succeed);

private:
	vector<MyDirection> deepSearchSolution(const Map& beginMap, 
		const Map& finishMap, bool& succeed);
	
private:
	vector<MyDirection> ASearchSolution(const Map& beginMap,
		const Map& finishMap, bool& succeed);

private:
	vector<MyDirection> NotSearchSolution(const Map& beginMap,
		const Map& finishMap, bool& succeed);

	
	static int A_g(Node* node);
	static int A_h(const Map& currentMap,
		const Map& finishMap = m_FinishMap);
	//如果index1小于index2，那么返回-1，相等返回0，大于返回1
	static int CmpIndex(int index1, int index2,int w, int h);


private:
	static Map m_FinishMap;
private:
	static bool checkHasAPath(const Map& beginMap,
		const Map& finishMap);
	static int MapNextSolution(int n, int w, int h);

	static void SwapToSucceed(Map& map);

private:
	const int M_MAXWIDTHNODE = 1500000;
	const int M_MAXDEEPNODE = 1500000;
	const int M_MAXANODE = 100000;
private:
	int m_MaxTimer;

private:
	class NodeQueueCmp
	{
	public:
		bool operator()(Node* a, Node* b);
	};
	class NodeMapCmp
	{
	public:
		bool operator()(Node* a, Node* b)const;
	};
};
