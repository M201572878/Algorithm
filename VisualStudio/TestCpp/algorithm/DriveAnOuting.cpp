// DriveAnOuting.cpp : Defines the entry point for the console application.
//

/*
描述：
小明和小芳出去乡村玩，小明负责开车，小芳来导航。小芳将可能的道路分为大道和小道。大道比较好走，每走1公里小明会增加1的疲劳度。小道不好走，如果连续走小道，小明的疲劳值会快速增加，连续走s公里小明会增加s2的疲劳度。例如：有5个路口，1号路口到2号路口为小道，2号路口到3号路口为小道，3号路口到4号路口为大道，4号路口到5号路口为小道，相邻路口之间的距离都是2公里。如果小明从1号路口到5号路口，则总疲劳值为(2 + 2) ^ 2 + 2 + 2 ^ 2 = 16 + 2 + 4 = 22。现在小芳拿到了地图，请帮助她规划一个开车的路线，使得按这个路线开车小明的疲劳度最小。
输入：
输入的第一行包含两个整数n, m，分别表示路口的数量和道路的数量。路口由1至n编号，小明需要开车从1号路口到n号路口。接下来m行描述道路，每行包含四个整数t, a, b, c，表示一条类型为t，连接a与b两个路口，长度为c公里的双向道路。其中t为0表示大道，t为1表示小道。保证1号路口和n号路口是连通的。
输出：
输出一个整数，表示最优路线下小明的疲劳度。
输入样例：
6 7
1 1 2 3
1 2 3 2
0 1 3 30
0 3 4 20
0 4 5 30
1 3 5 6
1 5 6 1
样例输出：
76
*/

#include<iostream>
#include<vector>
#include<set>
#include<cmath>
#include<fstream>
#include <algorithm>
#include <sstream>
using namespace std;

//输入重定向到字符串
static string g_inputStr = "6 7		\n\
1 1 2 3		\n\
1 2 3 2		\n\
0 1 3 30		\n\
0 3 4 20		\n\
0 4 5 30		\n\
1 3 5 6		\n\
1 5 6 1		\n\
";

static const unsigned int INF_FATIG = 1 << 30;//无线大疲劳
static const int NULL_ID = 0;//数值0
static const int FLAT_TYPE = 0;//平坦路类型
static const int HARD_TYPE = 1;//小路类型
static const int START_NODE = 1;//起始结点编号

//道路的结构
class Route{
public:
	int type;//类型
	int dis;//长度
	int src;//起点
	int dst;//终点
};

//到某点的前趋是小路的场景，记录所走小路的信息
class HardFatig{
public:
    int dis;//连续的小路路径
	int fatig;//从起点至此的疲劳消耗
	HardFatig(int fatigue, int dis):fatig(fatigue),dis(dis){}
private:
	HardFatig(){}//不允许默认构造
};

//到某点的疲劳消耗整体信息
class Fatigue{
public:
	int minFatigue;//平坦路和小路中最小的疲劳消耗
	int flatFatig;//前趋的平坦路的最小疲劳消耗
	vector<HardFatig> hardFatigVec;//记录所有前趋是小路的场景
	Fatigue(){minFatigue = INF_FATIG; flatFatig = INF_FATIG;}
};

typedef int Node;

//获取剩余结点中疲劳消耗的最小值
Node GetMinFatigNode(const vector<Fatigue>& smallerFatigueVec, const set<Node>& minNodeSet, const int maxNodeNumber)
{
    Node currNode = NULL_ID;
    int minFatig = INF_FATIG;
    for(Node node = START_NODE; node != maxNodeNumber; ++node)//遍历结点
    {
        if(minNodeSet.end() == minNodeSet.find(node))//不在已知结果集里的结点才处理
        {
            if(smallerFatigueVec[node].minFatigue < minFatig)//更新更少的疲劳消耗
            {
                minFatig = smallerFatigueVec[node].minFatigue;
                currNode = node;
            }
        }
    }

    return currNode;
}

/*********************************************************************************************************************************
模拟场景：  A***D  A——B  B***C   D***C（到A、B、D的最小疲劳已经计算出）  ****小路   ——大路
参数：
    toSrc:代表B
    route:代表B——C
返回值：
    int
***********************************************************************************************************************************/
int GetNewFatig(const Fatigue& toSrc, const Route& route)
{
    int newFatigue = INF_FATIG;

    if(route.type == FLAT_TYPE)//当前道路是平坦道路
    {
        newFatigue = toSrc.minFatigue + route.dis;//直接加上到B的最小疲劳消耗
    }
    else//当前道路是小路才需要考虑到B的各种场景
    {
        newFatigue = toSrc.flatFatig + pow((double)route.dis, 2);//先取平坦路的最小疲劳消耗
        vector<HardFatig>::const_iterator itHardRoad = toSrc.hardFatigVec.begin();
        for(; itHardRoad != toSrc.hardFatigVec.end(); ++itHardRoad)//遍历所有从小路到B再到C的场景
        {
            int fatigIncre = pow((double)route.dis + itHardRoad->dis, 2) - pow((double)itHardRoad->dis, 2);
            newFatigue = min(newFatigue, itHardRoad->fatig + fatigIncre);
        }
    }
    return newFatigue;
}

//使用最短路径算法计算最小疲劳消耗
int GetMinDistanceByDijstra(const vector<Route>& routeVec, const int maxNodeNum)
{
    set<Node> minNodeSet;
    //minNodeSet.insert(START_NODE);

    vector<Fatigue> smallerFatigueVec(maxNodeNum + 1);
    Fatigue startNode;
    startNode.minFatigue = 0;
    startNode.flatFatig = 0;
    smallerFatigueVec[START_NODE] = startNode;

    //循环n次,每次算出点1到一个点的最小消耗
    for(int i = START_NODE; i <= maxNodeNum; ++i)
    {
        //获取未处理结点中疲劳消耗最小的一个结点，加入已知结点中
        Node currNode = GetMinFatigNode(smallerFatigueVec, minNodeSet, maxNodeNum);
        minNodeSet.insert(currNode);

        //更新从已知结点集出发，经过一条路径到达未知结点集的疲劳消耗
        vector<Route>::const_iterator itRoute = routeVec.begin();
        for(; itRoute != routeVec.end(); ++itRoute)//遍历每条边
        {
            if(itRoute->src == currNode)//当前结点刚加入已知结点集，只用更新从当前结点出发的路径的终点
            {
                Node destNode = itRoute->dst;
				Fatigue& toSrc = smallerFatigueVec[currNode];
                Fatigue& todest = smallerFatigueVec[destNode];
                int newFatigue = GetNewFatig(toSrc, *itRoute);//获取最小疲劳消耗
                if(itRoute->type == FLAT_TYPE)//当前路径是平坦道路，直接更新
                {
                    todest.flatFatig = min(todest.flatFatig, newFatigue);
                }
                else//当前路径是小路，加入到destNode前趋是小路的场景
                {
                    HardFatig tempFatig(newFatigue, itRoute->dis);
                    todest.hardFatigVec.push_back(tempFatig);
                }
                todest.minFatigue = min(todest.minFatigue, newFatigue);//更新到该结点的最小疲劳消耗
            }
        }
    }
    return smallerFatigueVec[maxNodeNum].minFatigue;
}

class DriveAnOuting
{
public:
	static void run() 
	{
		//备份标准输入
		streambuf *backup;
		backup = cin.rdbuf();

		//输入重定向
		istringstream  iss(g_inputStr);
		ifstream fin;
		fin.open("data.in");
		cin.rdbuf(iss.rdbuf());
		//1.获取输入，保存
		int m, n;
		cin >> m >> n;
		int crossingNumber = m;
		int vectorSize = m + 1;
		vector<Route> routeVec;
		for (int i = 0; i < n; ++i)
		{
			int startCrossing, stopCrossing;
			Route route;
			cin >> route.type >> route.src >> route.dst >> route.dis;
			routeVec.push_back(route);
		}
		//恢复标准输入
		cin.rdbuf(backup);
		//计算疲劳消耗
		cout << GetMinDistanceByDijstra(routeVec, m) << endl;
	}
};


