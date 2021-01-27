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
	//�������Ĳ���Ϊ��ʼ״̬������״̬��succeed ���ܲ����ҵ����մ𰸣�
	//��������ҵ�������false
	//���ڴ������յ�����״̬��ctrlΪ0��ʾǿ��Ҫ�����ս��������ȫ����
	//ctrlΪ1����ô���㲻�ɹ�������һ�����½ǵ������������෴��·��
	//timeOrSpaceOut ������ʧ�ܵ�ԭ��
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
	//���index1С��index2����ô����-1����ȷ���0�����ڷ���1
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
