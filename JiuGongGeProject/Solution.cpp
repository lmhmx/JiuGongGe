#include "Solution.h"
Map Solution::m_FinishMap;
Solution::Solution()
{
	this->m_MaxTimer = 10000;
}
vector<MyDirection> Solution::getSolution(const Map& beginMap, const Map& finishMap, 
	bool& succeed, SearchType searchType, int ctrl, bool& timeOrSpaceOut)
{
	vector<MyDirection> res;
	Map a = beginMap;
	succeed = checkHasAPath(a, finishMap);
	timeOrSpaceOut = true;
	if (!succeed)
	{
		if (ctrl == 0)
		{
			timeOrSpaceOut = false;
			return res;
		}
		else
		{
			SwapToSucceed(a);
		}
	}
	
	succeed = checkHasAPath(a, finishMap);
	m_FinishMap = finishMap;
	if (!succeed)
	{
		cout << "error not suc" << endl;
		system("pause");
	}
	int clk0 = clock();
	cout << "will search " << endl;
	if (searchType == ASEARCH)
	{
		res = ASearchSolution(a, finishMap, succeed);
	}
	else if (searchType == DEEPSEARCH)
	{
		res = deepSearchSolution(a, finishMap, succeed);
	}
	else if (searchType == WIDTHSEARCH)
	{
		res = widthSearchSolution(a, finishMap, succeed);
	}
	else if (searchType == PROGRAMSEARCH)
	{
		res = NotSearchSolution(a, finishMap, succeed);
	}
	cout << clock() - clk0 << endl;
	timeOrSpaceOut = true;
	return  res;
}
bool Solution::setMaxTime(int maxTime)
{
	if (maxTime >= 10 && maxTime <= 1000 * 300)
	{
		this->m_MaxTimer = maxTime;
		return true;
	}
	else
	{
		return false;
	}
}
int Solution::getMaxTime()
{
	return this->m_MaxTimer;
}

//A 算法
vector<MyDirection> Solution::ASearchSolution(const Map& beginMap,
	const Map& finishMap, bool& succeed)
{
	vector<MyDirection> res;
	vector<Node*> close;
	priority_queue<Node*, vector<Node*>, NodeQueueCmp> open;

	map<Node*, int, NodeMapCmp> opendNode;
	int mapOpendNodeNum = 0;

	Node* allNode = new Node[M_MAXANODE];
	Node* allNode_CurrentNode = allNode;

	succeed = checkHasAPath(beginMap, finishMap);
	if (!succeed)
	{
		return res;
	}
	succeed = true;

	Node* currentNode = allNode_CurrentNode;
	allNode_CurrentNode++;

	currentNode->map = beginMap;
	currentNode->setParent(NULL);
	open.push(currentNode);

	opendNode.insert(pair<Node*, int>(currentNode, mapOpendNodeNum));
	mapOpendNodeNum++;

	int nodeNum = 1;
	int deleteNum = 0;
	int timerbegin = clock();
	while (1)
	{
		if ((nodeNum - deleteNum) % 5000 == 1)
		{
			cout << "已申请节点 " << nodeNum - deleteNum << endl;
		}
		if (open.empty() || succeed == false)
		{
			succeed = false;
			break;
		}
		if (clock() - timerbegin > m_MaxTimer)
		{
			succeed = false;
			break;
		}

		close.push_back(open.top());
		currentNode = open.top();
		open.pop();

		if (currentNode->map == finishMap)
		{
			succeed = true;
			break;
		}
		if (allNode_CurrentNode - allNode >= M_MAXANODE)
		{
			succeed = false;
			break;
		}
		Node* willKuoZhan = allNode_CurrentNode;
		allNode_CurrentNode++;

		nodeNum++;

		*willKuoZhan = *currentNode;
		for (int i = 0; i < 4; i++)
		{
			if (succeed == false)
			{
				break;
			}
			MyDirection direction;
			switch (i)
			{
			case 0:
			{
				direction = UP;
				break;
			}
			case 1:
			{
				direction = DOWN;
				break;
			}
			case 2:
			{
				direction = LEFT;
				break;
			}
			case 3:
			{
				direction = RIGHT;
				break;
			}
			default:
			{
				break;
			}
			}
			if (willKuoZhan->map.Move(direction))
			{
				bool flag = true;
				if (opendNode.find(willKuoZhan) != opendNode.end())
				{
					flag = false;
				}
				if (flag == true)
				{
					willKuoZhan->setParent(currentNode);
					open.push(willKuoZhan);

					opendNode.insert(pair<Node*, int>(willKuoZhan, mapOpendNodeNum));

					mapOpendNodeNum++;

					if (allNode_CurrentNode - allNode >= M_MAXANODE)
					{
						succeed = false;
						break;
					}

					willKuoZhan = allNode_CurrentNode;
					allNode_CurrentNode++;
					nodeNum++;
					*willKuoZhan = *currentNode;
				}
				//不能进行扩展
				else
				{
					*willKuoZhan = *currentNode;
				}
			}
		}
		allNode_CurrentNode--;
		deleteNum++;
	}
	cout << "searchtime "<<clock() - timerbegin << endl;
	if (succeed)
	{
		while (currentNode->getParent() != NULL)
		{
			res.push_back(currentNode->map - currentNode->getParent()->map);
			currentNode = currentNode->getParent();
		}
		reverse(res.begin(), res.end());
	}
	delete[] allNode;
	cout << "delete time" << clock() - timerbegin << endl;
	return res;
}


//深度优先搜索
vector<MyDirection> Solution::deepSearchSolution(const Map& beginMap,
	const Map& finishMap, bool& succeed)
{
	vector<MyDirection> res;
	vector<Node*> close;
	list<Node*> open;

	map<Node*, int, NodeMapCmp> opendNode;
	int mapOpendNodeNum = 0;

	Node* allNode = new Node[M_MAXDEEPNODE];
	Node* allNode_CurrentNode = allNode;

	succeed = checkHasAPath(beginMap, finishMap);
	if (!succeed)
	{
		return res;
	}
	succeed = true;

	Node* currentNode = allNode_CurrentNode;
	allNode_CurrentNode++;

	currentNode->map = beginMap;
	currentNode->setParent(NULL);
	open.push_back(currentNode);

	opendNode.insert(pair<Node*, int>(currentNode, mapOpendNodeNum));
	mapOpendNodeNum++;

	int nodeNum = 1;
	int deleteNum = 0;
	int timerbegin = clock();
	while (1)
	{
		if ((nodeNum - deleteNum) % 5000 == 1)
		{
			cout << "已申请节点 " << (nodeNum - deleteNum) << endl;
		}
		if (open.empty() || succeed == false)
		{
			succeed = false;
			break;
		}
		if (clock() - timerbegin > m_MaxTimer)
		{
			succeed = false;
			break;
		}

		close.push_back(open.back());
		currentNode = open.back();
		open.pop_back();

		if (currentNode->map == finishMap)
		{
			succeed = true;
			break;
		}
		if (allNode_CurrentNode - allNode >= M_MAXDEEPNODE)
		{
			succeed = false;
			break;
		}
		Node* willKuoZhan = allNode_CurrentNode;
		allNode_CurrentNode++;

		nodeNum++;

		*willKuoZhan = *currentNode;
		for (int i = 0; i < 4; i++)
		{
			if (succeed == false)
			{
				break;
			}
			MyDirection direction;
			switch (i)
			{
			case 0:
			{
				direction = UP;
				break;
			}
			case 1:
			{
				direction = DOWN;
				break;
			}
			case 2:
			{
				direction = LEFT;
				break;
			}
			case 3:
			{
				direction = RIGHT;
				break;
			}
			default:
			{
				break;
			}
			}
			if (willKuoZhan->map.Move(direction))
			{
				bool flag = true;
				if (opendNode.find(willKuoZhan) != opendNode.end())
				{
					flag = false;
				}
				if (flag == true)
				{
					willKuoZhan->setParent(currentNode);
					open.push_back(willKuoZhan);

					opendNode.insert(pair<Node*, int>(willKuoZhan, mapOpendNodeNum));

					mapOpendNodeNum++;

					if (allNode_CurrentNode - allNode >= M_MAXDEEPNODE)
					{
						succeed = false;
						break;
					}

					willKuoZhan = allNode_CurrentNode;
					allNode_CurrentNode++;
					nodeNum++;
					*willKuoZhan = *currentNode;
				}
				//不能进行扩展
				else
				{
					*willKuoZhan = *currentNode;
				}
			}
		}
		allNode_CurrentNode--;
		deleteNum++;
	}
	cout << clock() - timerbegin << endl;
	if (succeed)
	{
		while (currentNode->getParent() != NULL)
		{
			res.push_back(currentNode->map - currentNode->getParent()->map);
			currentNode = currentNode->getParent();
		}
		reverse(res.begin(), res.end());
	}
	delete[] allNode;
	cout << clock() - timerbegin << endl;
	return res;
}

//宽度优先搜索
vector<MyDirection> Solution::widthSearchSolution(const Map& beginMap,
	const Map& finishMap, bool& succeed)
{
	vector<MyDirection> res;
	vector<Node*> close;
	list<Node*> open;

	map<Node*, int, NodeMapCmp> opendNode;
	int mapOpendNodeNum = 0;

	Node* allNode = new Node[M_MAXWIDTHNODE];
	Node* allNode_CurrentNode = allNode;

	succeed = checkHasAPath(beginMap, finishMap);
	if (!succeed)
	{
		return res;
	}
	succeed = true;

	Node* currentNode = allNode_CurrentNode;
	allNode_CurrentNode++;

	currentNode->map = beginMap;
	currentNode->setParent(NULL);
	open.push_back(currentNode);

	opendNode.insert(pair<Node*, int>(currentNode, mapOpendNodeNum));
	mapOpendNodeNum++;

	int nodeNum = 1;
	int deleteNum = 0;
	int timerbegin = clock();
	while (1)
	{
		if ((nodeNum - deleteNum) % 5000 == 1)
		{
			cout << "已申请节点 " << (nodeNum - deleteNum) << endl;
		}
		if (open.empty() || succeed == false)
		{
			succeed = false;
			break;
		}
		if (clock() - timerbegin > m_MaxTimer)
		{
			succeed = false;
			break;
		}

		close.push_back(open.front());
		currentNode = open.front();
		open.pop_front();

		if (currentNode->map == finishMap)
		{
			succeed = true;
			break;
		}
		if (allNode_CurrentNode - allNode >= M_MAXWIDTHNODE)
		{
			succeed = false;
			break;
		}
		Node* willKuoZhan = allNode_CurrentNode;
		allNode_CurrentNode++;

		nodeNum++;

		*willKuoZhan = *currentNode;
		for (int i = 0; i < 4; i++)
		{
			if (succeed == false)
			{
				break;
			}
			MyDirection direction;
			switch (i)
			{
			case 0:
			{
				direction = UP;
				break;
			}
			case 1:
			{
				direction = DOWN;
				break;
			}
			case 2:
			{
				direction = LEFT;
				break;
			}
			case 3:
			{
				direction = RIGHT;
				break;
			}
			default:
			{
				break;
			}
			}
			if (willKuoZhan->map.Move(direction))
			{
				bool flag = true;
				if (opendNode.find(willKuoZhan) != opendNode.end())
				{
					flag = false;
				}
				if (flag == true)
				{
					willKuoZhan->setParent(currentNode);
					open.push_back(willKuoZhan);

					opendNode.insert(pair<Node*, int>(willKuoZhan, mapOpendNodeNum));

					mapOpendNodeNum++;

					if (allNode_CurrentNode - allNode >= M_MAXWIDTHNODE)
					{
						succeed = false;
						break;
					}

					willKuoZhan = allNode_CurrentNode;
					allNode_CurrentNode++;
					nodeNum++;
					*willKuoZhan = *currentNode;
				}
				//不能进行扩展
				else
				{
					*willKuoZhan = *currentNode;
				}
			}
		}
		allNode_CurrentNode--;
		deleteNum++;
	}
	cout << clock() - timerbegin << endl;
	if (succeed)
	{
		while (currentNode->getParent() != NULL)
		{
			res.push_back(currentNode->map - currentNode->getParent()->map);
			currentNode = currentNode->getParent();
		}
		reverse(res.begin(), res.end());
	}
	delete[] allNode;
	cout << clock() - timerbegin << endl;
	return res;
}

//万能还原方法
vector<MyDirection> Solution::NotSearchSolution(const Map& beginMap,
	const Map& finishMap, bool& succeed)
{
	vector<MyDirection> res;
	Map map_Cur = beginMap;
	int w = beginMap.getWidth();
	int h = beginMap.getHeight();
	//printMap(map_Cur);
	succeed = checkHasAPath(beginMap, finishMap);
	if (!succeed)
	{
		return res;
	}
	succeed = true;
	int X_Cur;
	int Y_Cur;
	int X_0;
	int Y_0;
	//前h-2行
	for (int Y_T = 0; Y_T < h - 2; Y_T++)
	{
		for (int X_T = 0; X_T < w; X_T++)
		{
			//前w-1列
			if (X_T < w - 1)
			{
				while (1)
				{
					X_Cur = map_Cur.getIndex(finishMap.ContentRead(X_T, Y_T)) % w;
					Y_Cur = map_Cur.getIndex(finishMap.ContentRead(X_T, Y_T)) / w;
					X_0 = map_Cur.getIndex(0) % w;
					Y_0 = map_Cur.getIndex(0) / w;

					if (X_Cur == X_T && Y_Cur == Y_T)
					{
						break;
					}

					//先进行左右移动
					//如果需要向右移动
					if (X_Cur < X_T)
					{
						//能直接右移
						if (X_Cur == X_0 - 1 && Y_Cur == Y_0)
						{
							map_Cur.Move(RIGHT);
							res.push_back(RIGHT);
						}
						//不能直接右移
						else
						{
							//先进行上下移动
							if (Y_Cur > Y_0)
							{
								//如果在正上方一个
								if (X_Cur == X_0 && Y_Cur == Y_0 + 1)
								{
									map_Cur.Move(LEFT);
									res.push_back(LEFT);
									map_Cur.Move(UP);
									res.push_back(UP);
									map_Cur.Move(RIGHT);
									res.push_back(RIGHT);
								}
								//如果不在同一列或者是在同一列的很上面的数
								else
								{
									map_Cur.Move(UP);
									res.push_back(UP);
								}
							}
							else if (Y_Cur == Y_0)
							{
								if (X_Cur == X_0 + 1)
								{
									if (Y_Cur == h - 1)
									{
										map_Cur.Move(DOWN);
										res.push_back(DOWN);
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
										//剩下的会交给下一个循环
									}
									else
									{
										map_Cur.Move(UP);
										res.push_back(UP);
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
										//剩下的会交给下一个循环
									}
								}
								else
								{
									if (X_Cur > X_0)
									{
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
									}
									else
									{
										map_Cur.Move(RIGHT);
										res.push_back(RIGHT);
									}
								}
							}
							else if (Y_Cur < Y_0)
							{
								if (X_Cur == X_0 && Y_Cur == Y_0 - 1)
								{
									map_Cur.Move(LEFT);
									map_Cur.Move(DOWN);
									map_Cur.Move(RIGHT);
									res.push_back(LEFT);
									res.push_back(DOWN);
									res.push_back(RIGHT);
								}
								else
								{
									map_Cur.Move(DOWN);
									res.push_back(DOWN);
								}
							}
						}
					}
					//如果需要向左移动
					else if (X_Cur > X_T)
					{
						//能直接左移
						if (X_Cur == X_0 + 1 && Y_Cur == Y_0)
						{
							map_Cur.Move(LEFT);
							res.push_back(LEFT);
						}
						//不能直接左移
						else
						{
							//先进行上下移动
							if (Y_Cur > Y_0)
							{
								//如果在正上方一个
								if (X_Cur == X_0 && Y_Cur == Y_0 + 1)
								{
									map_Cur.Move(RIGHT);
									res.push_back(RIGHT);
									map_Cur.Move(UP);
									res.push_back(UP);
									map_Cur.Move(LEFT);
									res.push_back(LEFT);
								}
								//如果不在同一列或者是在同一列的很上面的数
								else
								{
									map_Cur.Move(UP);
									res.push_back(UP);
								}
							}
							else if (Y_Cur == Y_0)
							{
								if (X_Cur == X_0 - 1)
								{
									if (Y_Cur == h - 1)
									{
										map_Cur.Move(DOWN);
										res.push_back(DOWN);
										map_Cur.Move(RIGHT);
										res.push_back(RIGHT);
										//剩下的会交给下一个循环
									}
									else
									{
										map_Cur.Move(UP);
										res.push_back(UP);
										map_Cur.Move(RIGHT);
										res.push_back(RIGHT);
										//剩下的会交给下一个循环
									}
								}
								else
								{
									if (X_Cur > X_0)
									{
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
									}
									else
									{
										map_Cur.Move(RIGHT);
										res.push_back(RIGHT);
									}
								}
							}
							else if (Y_Cur < Y_0)
							{
								if (Y_Cur != Y_T)
								{
									if (X_Cur == X_0 && Y_Cur == Y_0 - 1)
									{
										map_Cur.Move(RIGHT);
										map_Cur.Move(DOWN);
										map_Cur.Move(LEFT);
										res.push_back(RIGHT);
										res.push_back(DOWN);
										res.push_back(LEFT);
									}
									else
									{
										map_Cur.Move(DOWN);
										res.push_back(DOWN);
									}
								}
								else
								{
									if (X_Cur == X_0 && Y_Cur == Y_0 - 1)
									{
										map_Cur.Move(RIGHT);
										map_Cur.Move(DOWN);
										map_Cur.Move(LEFT);
										res.push_back(RIGHT);
										res.push_back(DOWN);
										res.push_back(LEFT);
									}
									else
									{
										if (X_Cur > X_0)
										{
											map_Cur.Move(LEFT);
											res.push_back(LEFT);
										}
										else if (X_Cur < X_0)
										{
											map_Cur.Move(RIGHT);
											res.push_back(RIGHT);
										}
										else
										{
											map_Cur.Move(DOWN);
											res.push_back(DOWN);
										}
									}
								}
							}
						}
					}
					//如果不需要横向
					else // if(X_Cur == X_T)
					{
						//能直接上移
						if (X_Cur == X_0 && Y_Cur == Y_0 + 1)
						{
							map_Cur.Move(UP);
							res.push_back(UP);
							//map_Cur.Move(LEFT);
							//res.push_back(LEFT);
							//map_Cur.Move(DOWN);
							//map_Cur.Move(DOWN);
							//map_Cur.Move(RIGHT);
							//res.push_back(DOWN);
							//res.push_back(DOWN);
							//res.push_back(RIGHT);
						}
						//不能直接上移
						else
						{
							if (Y_Cur < Y_0)
							{
								//在正下方一个
								if (Y_Cur == Y_0 - 1 && X_Cur == X_0)
								{
								
									map_Cur.Move(LEFT);
									res.push_back(LEFT);
									map_Cur.Move(DOWN);
									map_Cur.Move(DOWN);
									map_Cur.Move(RIGHT);
									res.push_back(DOWN);
									res.push_back(DOWN);
									res.push_back(RIGHT);
								}
								else
								{
									map_Cur.Move(DOWN);
									res.push_back(DOWN);
								}
							}
							else if (Y_Cur > Y_0)
							{
								map_Cur.Move(UP);
								res.push_back(UP);
							}
							else//if(Y_Cur == Y_0)
							{
								if (X_0 > X_Cur)
								{
									if (X_0 == X_Cur + 1)
									{
										map_Cur.Move(DOWN);
										map_Cur.Move(RIGHT);
										res.push_back(DOWN);
										res.push_back(RIGHT);
									}
									else
									{
										map_Cur.Move(RIGHT);
										res.push_back(RIGHT);
									}
								}
								else//if(X_0 < X_Cur)
								{
									if (X_0 == X_Cur - 1)
									{
										if (Y_0 != h - 1)
										{
											map_Cur.Move(UP);
											map_Cur.Move(LEFT);
											map_Cur.Move(LEFT);
											map_Cur.Move(DOWN);
											map_Cur.Move(DOWN);
											map_Cur.Move(RIGHT);

											res.push_back(UP);
											res.push_back(LEFT);
											res.push_back(LEFT);
											res.push_back(DOWN);
											res.push_back(DOWN);
											res.push_back(RIGHT);
										}
										else
										{
											map_Cur.Move(DOWN);
											map_Cur.Move(LEFT);
											map_Cur.Move(LEFT);
											map_Cur.Move(UP);
											map_Cur.Move(RIGHT);

											res.push_back(DOWN);
											res.push_back(LEFT);
											res.push_back(LEFT);
											res.push_back(UP);
											res.push_back(RIGHT);
										}
									}
									else
									{
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
									}
								}
							}
						}
					}
					//printMap(map_Cur);
					//cout << endl;
				}
				
			}
			//最后一列
			else//(if(X_T == w-1)
			{
				while (1)
				{
					X_Cur = map_Cur.getIndex(finishMap.ContentRead(X_T, Y_T)) % w;
					Y_Cur = map_Cur.getIndex(finishMap.ContentRead(X_T, Y_T)) / w;
					X_0 = map_Cur.getIndex(0) % w;
					Y_0 = map_Cur.getIndex(0) / w;

					if (X_Cur == X_T && Y_Cur == Y_T)
					{
						break;
					}
					if (X_Cur == X_T && Y_Cur - 1 == Y_T)
					{
						//******************
						if (X_0 == X_T && Y_0 == Y_T)
						{
							map_Cur.Move(UP);
							res.push_back(UP);
							break;
						}
						else
						{
							while (1)
							{
								X_Cur = map_Cur.getIndex(finishMap.ContentRead(X_T, Y_T)) % w;
								Y_Cur = map_Cur.getIndex(finishMap.ContentRead(X_T, Y_T)) / w;
								X_0 = map_Cur.getIndex(0) % w;
								Y_0 = map_Cur.getIndex(0) / w;
								if (X_0 < X_Cur)
								{
									if (X_0 == X_Cur - 1 && Y_0 == Y_Cur)
									{
										//*******
										map_Cur.Move(DOWN);
										map_Cur.Move(LEFT);
										map_Cur.Move(UP);
										map_Cur.Move(RIGHT);
										map_Cur.Move(UP);
										map_Cur.Move(LEFT);
										map_Cur.Move(DOWN);
										map_Cur.Move(RIGHT);
										map_Cur.Move(DOWN);
										map_Cur.Move(LEFT);
										map_Cur.Move(UP);
										map_Cur.Move(UP);
										map_Cur.Move(RIGHT);
										map_Cur.Move(DOWN);
										map_Cur.Move(LEFT);
										map_Cur.Move(DOWN);
										map_Cur.Move(RIGHT);
										map_Cur.Move(UP);

										res.push_back(DOWN);
										res.push_back(LEFT);
										res.push_back(UP);
										res.push_back(RIGHT);
										res.push_back(UP);
										res.push_back(LEFT);
										res.push_back(DOWN);
										res.push_back(RIGHT);
										res.push_back(DOWN);
										res.push_back(LEFT);
										res.push_back(UP);
										res.push_back(UP);
										res.push_back(RIGHT);
										res.push_back(DOWN);
										res.push_back(LEFT);
										res.push_back(DOWN);
										res.push_back(RIGHT);
										res.push_back(UP);

										break;
									}
									else
									{
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
									}
								}
								else
								{
									if (Y_0 == Y_Cur + 1)
									{
										map_Cur.Move(RIGHT);
										map_Cur.Move(DOWN);
										res.push_back(RIGHT);
										res.push_back(DOWN);
									}
									else
									{
										map_Cur.Move(DOWN);
										res.push_back(DOWN);
									}
								}
							}
						}
						break;
						//******************
					}
					//先进行左右移动
					//如果需要向右移动
					if (X_Cur < X_T)
					{
						//能直接右移
						if (X_Cur == X_0 - 1 && Y_Cur == Y_0)
						{
							map_Cur.Move(RIGHT);
							res.push_back(RIGHT);
						}
						//不能直接右移
						else
						{
							//先进行上下移动
							if (Y_Cur > Y_0)
							{
								//如果在正上方一个
								if (X_Cur == X_0 && Y_Cur == Y_0 + 1)
								{
									map_Cur.Move(LEFT);
									res.push_back(LEFT);
									map_Cur.Move(UP);
									res.push_back(UP);
									map_Cur.Move(RIGHT);
									res.push_back(RIGHT);
								}
								//如果不在同一列或者是在同一列的很上面的数
								else
								{
									map_Cur.Move(UP);
									res.push_back(UP);
								}
							}
							else if (Y_Cur == Y_0)
							{
								if (X_Cur == X_0 + 1)
								{
									if (Y_Cur == h - 1)
									{
										map_Cur.Move(DOWN);
										res.push_back(DOWN);
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
										//剩下的会交给下一个循环
									}
									else
									{
										map_Cur.Move(UP);
										res.push_back(UP);
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
										//剩下的会交给下一个循环
									}
								}
								else
								{
									if (X_Cur > X_0)
									{
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
									}
									else
									{
										map_Cur.Move(RIGHT);
										res.push_back(RIGHT);
									}
								}
							}
							else if (Y_Cur < Y_0)
							{
								if (X_Cur == X_0 && Y_Cur == Y_0 - 1)
								{
									map_Cur.Move(LEFT);
									map_Cur.Move(DOWN);
									map_Cur.Move(RIGHT);
									res.push_back(LEFT);
									res.push_back(DOWN);
									res.push_back(RIGHT);
								}
								else
								{
									map_Cur.Move(DOWN);
									res.push_back(DOWN);
								}
							}
						}
					}
					//如果不需要横向
					else // if(X_Cur == X_T)
					{
						//能直接上移
						if (X_Cur == X_0 && Y_Cur == Y_0 + 1)
						{
							map_Cur.Move(UP);
							res.push_back(UP);
						}
						//不能直接上移
						else
						{
							if (Y_Cur < Y_0)
							{
								//在正下方一个
								if (Y_Cur == Y_0 - 1 && X_Cur == X_0)
								{

									map_Cur.Move(RIGHT);
									res.push_back(RIGHT);
									map_Cur.Move(DOWN);
									map_Cur.Move(DOWN);
									map_Cur.Move(LEFT);
									res.push_back(DOWN);
									res.push_back(DOWN);
									res.push_back(LEFT);
								}
								else
								{
									map_Cur.Move(DOWN);
									res.push_back(DOWN);
								}
							}
							else if (Y_Cur > Y_0)
							{
								map_Cur.Move(UP);
								res.push_back(UP);
								
							}
							else//if(Y_Cur == Y_0)
							{
								if (X_0 > X_Cur)
								{
									if (X_0 == X_Cur + 1)
									{
										map_Cur.Move(DOWN);
										map_Cur.Move(RIGHT);
										res.push_back(DOWN);
										res.push_back(RIGHT);
									}
									else
									{
										map_Cur.Move(RIGHT);
										res.push_back(RIGHT);
									}
								}
								else//if(X_0 < X_Cur)
								{
									if (X_0 == X_Cur - 1)
									{
										map_Cur.Move(DOWN);
										map_Cur.Move(LEFT);
										
										res.push_back(DOWN);
										res.push_back(LEFT);
									}
									else
									{
										map_Cur.Move(LEFT);
										res.push_back(LEFT);
									}
								}
							}
						}
					}
					//printMap(map_Cur);
					//cout << endl;
				}
			}
		}
	}
	//printMap(map_Cur);
	//cout << endl;
	for (int X_T = 0; X_T < w - 2; X_T++)
	{
		int X_b;
		int Y_b;
		int X_a;
		int Y_a;
		while (1)
		{
			X_b = map_Cur.getIndex(finishMap.ContentRead(X_T, h - 1)) % w;
			Y_b = map_Cur.getIndex(finishMap.ContentRead(X_T, h - 1)) / w;
			X_a = map_Cur.getIndex(finishMap.ContentRead(X_T, h - 2)) % w;
			Y_a = map_Cur.getIndex(finishMap.ContentRead(X_T, h - 2)) / w;
			X_0 = map_Cur.getIndex(0) % w;
			Y_0 = map_Cur.getIndex(0) / w;

			if (X_b == X_T && X_a == X_T && Y_a == h - 2 && Y_b == h - 1)
			{
				break;
			}

			if (X_b == X_T && Y_b == h - 2)
			{
				while (1)
				{
					X_b = map_Cur.getIndex(finishMap.ContentRead(X_T, h - 1)) % w;
					Y_b = map_Cur.getIndex(finishMap.ContentRead(X_T, h - 1)) / w;
					X_a = map_Cur.getIndex(finishMap.ContentRead(X_T, h - 2)) % w;
					Y_a = map_Cur.getIndex(finishMap.ContentRead(X_T, h - 2)) / w;
					X_0 = map_Cur.getIndex(0) % w;
					Y_0 = map_Cur.getIndex(0) / w;
					if (X_b == X_T && X_a == X_T && Y_a == h - 2 && Y_b == h - 1)
					{
						break;
					}
					if (X_0 == X_T && Y_0 == h - 1 && X_a == X_T + 1 && Y_a == h - 1)
					{
						//*****
						map_Cur.Move(DOWN);
						map_Cur.Move(LEFT);
						map_Cur.Move(UP);
						map_Cur.Move(LEFT);
						map_Cur.Move(DOWN);
						map_Cur.Move(RIGHT);
						map_Cur.Move(RIGHT);
						map_Cur.Move(UP);
						map_Cur.Move(LEFT);
						map_Cur.Move(DOWN);
						map_Cur.Move(LEFT);
						map_Cur.Move(UP);
						map_Cur.Move(RIGHT);
						map_Cur.Move(RIGHT);
						map_Cur.Move(DOWN);
						map_Cur.Move(LEFT);
					
						res.push_back(DOWN);
						res.push_back(LEFT);
						res.push_back(UP);
						res.push_back(LEFT);
						res.push_back(DOWN);
						res.push_back(RIGHT);
						res.push_back(RIGHT);
						res.push_back(UP);
						res.push_back(LEFT);
						res.push_back(DOWN);
						res.push_back(LEFT);
						res.push_back(UP);
						res.push_back(RIGHT);
						res.push_back(RIGHT);
						res.push_back(DOWN);
						res.push_back(LEFT);
					}
					else if (X_a == X_T && Y_a == h - 1 && X_0 == X_T+1&&Y_0==h-1)
					{
						//******
						map_Cur.Move(RIGHT);
						res.push_back(RIGHT);
					}
					else if (X_a == X_T && Y_a == h - 1 && X_0 == X_T + 1 && Y_0 == h - 2)
					{
						//******
						map_Cur.Move(UP);
						res.push_back(UP);
					}
					else
					{
						if (X_0 > X_a)
						{
							if (X_0 == X_a + 1 && Y_0 == Y_a)
							{
								if (X_a != X_T + 1)
								{
									if (Y_a == h - 1)
									{
										map_Cur.Move(DOWN);
										map_Cur.Move(RIGHT);
										map_Cur.Move(RIGHT);
										map_Cur.Move(UP);
										map_Cur.Move(LEFT);

										res.push_back(DOWN);
										res.push_back(RIGHT);
										res.push_back(RIGHT);
										res.push_back(UP);
										res.push_back(LEFT);

									}
									else
									{
										map_Cur.Move(UP);
										map_Cur.Move(RIGHT);
										map_Cur.Move(RIGHT);
										map_Cur.Move(DOWN);
										map_Cur.Move(LEFT);

										res.push_back(UP);
										res.push_back(RIGHT);
										res.push_back(RIGHT);
										res.push_back(DOWN);
										res.push_back(LEFT);
									}
								}
								else//if(X_a == X_T+1)
								{
									if (Y_a == h - 1)
									{
										map_Cur.Move(DOWN);
										map_Cur.Move(RIGHT);
										map_Cur.Move(UP);
										map_Cur.Move(RIGHT);
										map_Cur.Move(DOWN);
										map_Cur.Move(LEFT);

										res.push_back(DOWN);
										res.push_back(RIGHT);
										res.push_back(UP);
										res.push_back(RIGHT);
										res.push_back(DOWN);
										res.push_back(LEFT);
									}
									else
									{
										map_Cur.Move(UP);
										map_Cur.Move(RIGHT);
										map_Cur.Move(RIGHT);
										map_Cur.Move(DOWN);
										map_Cur.Move(LEFT);

										res.push_back(UP);
										res.push_back(RIGHT);
										res.push_back(RIGHT);
										res.push_back(DOWN);
										res.push_back(LEFT);
									}
								}
							}
							else
							{
								map_Cur.Move(RIGHT);
								res.push_back(RIGHT);
							}
						}
						else if (X_0 < X_a)
						{
							map_Cur.Move(LEFT);
							res.push_back(LEFT);
						}
						else
						{
							if (X_T == X_a - 1)
							{
								if (Y_a == h - 1)
								{
									map_Cur.Move(UP);
									map_Cur.Move(RIGHT);
									map_Cur.Move(DOWN);
									map_Cur.Move(LEFT);

									res.push_back(UP);
									res.push_back(RIGHT);
									res.push_back(DOWN);
									res.push_back(LEFT);
								}
								else
								{
									map_Cur.Move(RIGHT);
									map_Cur.Move(DOWN);
									map_Cur.Move(LEFT);

									res.push_back(RIGHT);
									res.push_back(DOWN);
									res.push_back(LEFT);
								}
							}
							else
							{
								if (Y_a == h - 1)
								{
									map_Cur.Move(RIGHT);
									map_Cur.Move(UP);
									map_Cur.Move(LEFT);

									res.push_back(RIGHT);
									res.push_back(UP);
									res.push_back(LEFT);
								}
								else
								{
									map_Cur.Move(RIGHT);
									map_Cur.Move(DOWN);
									map_Cur.Move(LEFT);

									res.push_back(RIGHT);
									res.push_back(DOWN);
									res.push_back(LEFT);
								}
							}

						}
					}
					printMap(map_Cur);
					//cout << endl;
				}
				break;
			}
			else //if()
			{
				if (X_b == X_T)
				{
					if (X_0 == X_T && Y_0 == h-2)
					{
						map_Cur.Move(UP);
						res.push_back(UP);
					}
					else if (X_0 == X_T + 1)
					{
						if (Y_0 == h - 1)
						{
							map_Cur.Move(DOWN);
							map_Cur.Move(RIGHT);
							map_Cur.Move(UP);

							res.push_back(DOWN);
							res.push_back(RIGHT);
							res.push_back(UP);
						}
						else
						{
							map_Cur.Move(RIGHT);
							map_Cur.Move(UP);

							res.push_back(RIGHT);
							res.push_back(UP);
						}
					}
					else
					{
						map_Cur.Move(RIGHT);
						res.push_back(RIGHT);
					}
				}
				else
				{
					//如果能直接左移
					if (X_0 == X_b - 1 && Y_0 == Y_b)
					{
						res.push_back(LEFT);
						map_Cur.Move(LEFT);
					}
					else
					{
						if (X_0 < X_b)
						{
							res.push_back(LEFT);
							map_Cur.Move(LEFT);
						}
						else if (X_0 == X_b  + 1&& Y_0 == Y_b)
						{
							if (Y_b == h - 1)
							{
								res.push_back(DOWN);
								res.push_back(RIGHT);
								res.push_back(RIGHT);
								res.push_back(UP);
								res.push_back(LEFT);

								map_Cur.Move(DOWN);
								map_Cur.Move(RIGHT);
								map_Cur.Move(RIGHT);
								map_Cur.Move(UP);
								map_Cur.Move(LEFT);
							}
							else
							{
								res.push_back(UP);
								res.push_back(RIGHT);
								res.push_back(RIGHT);
								res.push_back(DOWN);
								res.push_back(LEFT);

								map_Cur.Move(UP);
								map_Cur.Move(RIGHT);
								map_Cur.Move(RIGHT);
								map_Cur.Move(DOWN);
								map_Cur.Move(LEFT);
							}
						}
						else if (X_0 > X_b)
						{
							res.push_back(RIGHT);
							map_Cur.Move(RIGHT);
						}
						else//(if(X_0 == X_b)
						{
							if (Y_0 > Y_b)
							{
								res.push_back(RIGHT);
								res.push_back(DOWN);
								res.push_back(LEFT);

								map_Cur.Move(RIGHT);
								map_Cur.Move(DOWN);
								map_Cur.Move(LEFT);
							}
							else
							{
								res.push_back(RIGHT);
								res.push_back(UP);
								res.push_back(LEFT);

								map_Cur.Move(RIGHT);
								map_Cur.Move(UP);
								map_Cur.Move(LEFT);
							}
							
						}
					}
				}
			}
			printMap(map_Cur);
			//cout << endl;
		}
		printMap(map_Cur);
		//cout << endl;
	}

	X_0 = map_Cur.getIndex(0) % w;
	Y_0 = map_Cur.getIndex(0) / w;
	int X_a = map_Cur.getIndex(finishMap.ContentRead(w - 2, h - 2)) % w;
	int Y_a = map_Cur.getIndex(finishMap.ContentRead(w - 2, h - 2)) / w;
	int X_b = map_Cur.getIndex(finishMap.ContentRead(w - 2, h - 1)) % w;
	int Y_b = map_Cur.getIndex(finishMap.ContentRead(w - 2, h - 1)) / w;
	int X_c = map_Cur.getIndex(finishMap.ContentRead(w - 1, h - 2)) % w;
	int Y_c = map_Cur.getIndex(finishMap.ContentRead(w - 1, h - 2)) / w;
	
	//最后四个格
	int counter = 0;
	while (1)
	{
		if (counter > 100)
		{
			succeed = false;
			cout << "error" << endl;
			
			break;
		}
		counter++;
		X_0 = map_Cur.getIndex(0) % w;
		Y_0 = map_Cur.getIndex(0) / w;
		X_a = map_Cur.getIndex(finishMap.ContentRead(w - 2, h - 2)) % w;
		Y_a = map_Cur.getIndex(finishMap.ContentRead(w - 2, h - 2)) / w;
		X_b = map_Cur.getIndex(finishMap.ContentRead(w - 2, h - 1)) % w;
		Y_b = map_Cur.getIndex(finishMap.ContentRead(w - 2, h - 1)) / w;
		X_c = map_Cur.getIndex(finishMap.ContentRead(w - 1, h - 2)) % w;
		Y_c = map_Cur.getIndex(finishMap.ContentRead(w - 1, h - 2)) / w;

		if (X_a == w - 2 && Y_a == h - 2 && X_b == w - 2 &&
			Y_b == h - 1 && X_c == w - 1 && Y_c == h - 2)
		{
			break;
		}
		if (X_0 == w - 1 && Y_0 == h - 1)
		{
			res.push_back(DOWN);
			map_Cur.Move(DOWN);
		}
		else if (X_0 == w - 1 && Y_0 == h - 2)
		{
			res.push_back(RIGHT);
			map_Cur.Move(RIGHT);
		}
		else if (X_0 == w - 2 && Y_0 == h - 1)
		{
			res.push_back(LEFT);
			map_Cur.Move(LEFT);
		}
		else
		{
			res.push_back(UP);
			map_Cur.Move(UP);
		}
	}
	Map pp = beginMap;
	for (int i = 0; i < res.size(); i++)
	{
		if (pp.Move(res[i]) == false)
		{
			cout << "error search " <<i<<" "<<res.size()<< endl;
			succeed = false;
		}
	}
	if (!(pp == finishMap))
	{
		cout << "can't  search" << endl;
		succeed = false;
	}
	return res;
}


bool Solution::checkHasAPath(const Map& beginMap,
	const Map& finishMap)
{
	bool succeed;
	int w = beginMap.getWidth();
	int h = beginMap.getHeight();
	int num1 = 0;
	int num2 = 0;
	for (int i = 0; i < h * w; i++)
	{
		if ((i == h*w-1)&&(h%2==1) || (i == w * (h - 1) && h % 2 == 0))
		{
			continue;
		}
		for (int j = MapNextSolution(i,w,h); true; j = MapNextSolution(j,w,h))
		{
			if (beginMap.getContent()[i] > beginMap.getContent()[j]
				&& beginMap.getContent()[j] != 0)
			{
				num1++;
			}
			if (j == w * h - 1 && h % 2 == 1)
			{
				break;
			}
			else if (j == w * (h - 1) && h % 2 == 0)
			{
				break;
			}
		}
	}
	for (int i = 0; i < h * w; i++)
	{
		if ((i == h * w - 1) && (h % 2 == 1) || (i == w * (h - 1) && h % 2 == 0))
		{
			continue;
		}
		for (int j = MapNextSolution(i, w, h); true; j = MapNextSolution(j, w, h))
		{
			if (finishMap.getContent()[i] > finishMap.getContent()[j]
				&& finishMap.getContent()[j] != 0)
			{
				num2++;
			}
			if (j == w * h - 1 && h % 2 == 1)
			{
				break;
			}
			else if (j == w * (h - 1) && h % 2 == 0)
			{
				break;
			}
		}
	}
	if (num1 % 2 != num2 % 2)
	{
		succeed = false;
	}
	else
	{
		succeed = true;
	}
	return succeed;
}

int Solution::A_h(const Map& currentMap,
	const Map& finishMap)
{
	int w = currentMap.getWidth();
	int h = currentMap.getHeight();
	int res = 0;
	int res1 = 0;
	int res2 = 0;
	for (int i = 0; i < w*h; i++)
	{
		int j = finishMap.getIndex(currentMap.getContent()[i]);
		res1 = res1 + abs(j / w - i / w) + abs(j%w - i % w);
	}
	int Cur_right;
	int Cur_down;
	int Cur;
	int index_cur;
	int index_right;
	int index_down;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			Cur = currentMap.ContentRead(x, y);
			Cur_right = -1;
			Cur_down = -1;
			
			if (y < h - 1)
			{
				if (x < w - 1)
				{
					Cur_right = currentMap.ContentRead(x + 1, y);
					Cur_down = currentMap.ContentRead(x, y + 1);
				}
				else
				{
					Cur_down = currentMap.ContentRead(x, y + 1);
				}
			}
			else
			{
				if (x < w - 1)
				{
					Cur_right = currentMap.ContentRead(x + 1, y);
				}
				else
				{
					//noting
				}
			}

			index_cur = finishMap.getIndex(Cur);
			if (Cur_down != -1)
			{
				index_down = finishMap.getIndex(Cur_down);
				if (abs(index_cur / w - index_down / w) +
					abs(index_cur%w - index_down % w) != 1)
				{
					res2 = res2 + 2;
				}
			}
			if (Cur_right != -1)
			{
				index_right = finishMap.getIndex(Cur_right);
				if (abs(index_cur / w - index_right / w) +
					abs(index_cur%w - index_right % w) != 1)
				{
					res2 = res2 + 1;
				}
			}
			
		}
	}
	/*for (int i = 0; i < w*h; i++)
	{
		int iValue = currentMap.getContent()[i];
		int nextValue = currentMap.getContent()[MapNextSolution(i,w,h)];
		
		int iIndex = finishMap.getIndex(iValue);
		int nextIndex = finishMap.getIndex(nextValue);
		if (nextIndex != MapNextSolution(iIndex,w,h) && iValue!=0)
		{
			res2 = res2 + 2;
		}
	}
	*/

	//for (int i = 0; i < h * w - 1; i++)
	//{
	//	int iValue = currentMap.getContent()[i];
	//	if (i == w * (h - 1) && h % 2 == 0)
	//	{
	//		continue;
	//	}
	//	for (int j = MapNextSolution(i, w, h); true; j = MapNextSolution(j, w, h))
	//	{
	//		int jValue = currentMap.getContent()[j];
	//		if (CmpIndex(finishMap.getIndex(iValue), 
	//			finishMap.getIndex(jValue),w,h) == 1)
	//		{
	//			res2 = res2 + 2;
	//		}
	//		if (j == w * h - 1 && h % 2 == 1)
	//		{
	//			break;
	//		}
	//		else if (j == w * (h - 1) && h % 2 == 0)
	//		{
	//			break;
	//		}
	//	}
	//}
	res =  5 * res1 +  2 * res2;
	return res;
}
int Solution::CmpIndex(int index1, int index2, int w, int h)
{
	int res = 0;
	int x1 = index1 % w;
	int y1 = index1 / w;
	int x2 = index2 % w;
	int y2 = index2 / w;
	if (y1 < y2)
	{
		res = -1;
	}
	else if (y1 > y2)
	{
		res = 1;
	}
	else
	{
		if (y1 % 2 == 0)
		{
			if (x1 < x2)
			{
				res = -1;
			}
			else if (x1 > x2)
			{
				res = 1;
			}
		}
	}
	return res;
}

int Solution::A_g(Node* node)
{
	return node->getParentNum();
}

int Solution::MapNextSolution(int n, int w, int h)
{
	int res = 0;
	int row = n / w;
	int col = n % w;
	//本行是正向
	if (row % 2 == 0)
	{
		//到了一行的最后一个
		if (col == w - 1)
		{
			res = (n + w) % (w*h);
		}
		else
		{
			res = n + 1;
		}
	}
	//本行为逆向
	else
	{
		if (col == 0)
		{
			res = (n + w) % (w*h);
		}
		else
		{
			res = n - 1;
		}
	}
	return res;
}

Node::Node() 
{
	this->parent = NULL;
	//this->map.initMap(3, 3);
}
Node::Node(const Node& node)
{
	this->parent = node.parent;
	this->map = node.map;
	this->m_ParentsNum = 0;
}
Node::~Node()
{
	this->parent = NULL;
	this->map.~Map();
}
Node& Node::operator=(const Node& node)
{
	this->parent = node.parent;
	this->map = node.map;
	this->m_ParentsNum = node.m_ParentsNum;
	return *this;
}
Node* Node::getParent()
{
	return this->parent;
}
int Node::getParentNum()
{
	return m_ParentsNum;
}
void Node::setParent(Node* parent)
{
	this->parent = parent;
	if (parent == NULL)
	{
		m_ParentsNum = 0;
	}
	else
	{
		m_ParentsNum = 1 + parent->m_ParentsNum;
	}
}

bool Solution::NodeQueueCmp::operator()(Node* a, Node* b)
{
	if (A_h(a->map) + A_g(a) > A_h(b->map)+A_g(b))
	{
		return true;
	}
	return false;
}
bool Solution::NodeMapCmp::operator()(Node* a, Node* b)const
{
	if (a->map<b->map)
	{
		return true;
	}
	return false;
}

void Solution::SwapToSucceed(Map& map)
{
	int tmp;
	vector<int> a = map.getContent();
	int w = map.getWidth();
	int h = map.getHeight();
	int x1 = -1;
	int x2 = -1;
	for (int i = 0; i < w*h; i++)
	{
		if (a[i] == w * h - 1)
		{
			x1 = i;
		}
		if (a[i] == w * h - 2)
		{
			x2 = i;
		}
	}
	tmp = a[x1];
	a[x1] = a[x2];
	a[x2] = tmp;
	map.setContent(a);
	
}
