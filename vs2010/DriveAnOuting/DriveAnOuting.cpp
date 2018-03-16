// DriveAnOuting.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<vector>
#include<set>
#include<cmath>
using namespace std;


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
Node GetMinFatigNode(const vector<Fatigue> smallerFatigueVec, const set<Node>& minNodeSet, const int maxNodeNumber)
{
    Node currNode = NULL_ID;
    int minFatig = INF_FATIG;
    for(Node node = START_NODE + 1; node != maxNodeNumber; ++node)//遍历结点
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
        newFatigue = toSrc.flatFatig + pow(route.type, 2);//先取平坦路的最小疲劳消耗
        vector<HardFatig>::const_iterator itHardRoad = toSrc.hardFatigVec.begin();
        for(; itHardRoad != toSrc.hardFatigVec.end(); ++itHardRoad)//遍历所有从小路到B再到C的场景
        {
            int fatigIncre = pow(route.type + itHardRoad->dis, 2) - pow(route.type, 2);
            newFatigue = min(newFatigue, toSrc.flatFatig + fatigIncre);
        }
    }
    return newFatigue;
}

//使用最短路径算法计算最小疲劳消耗
void GetMinDistanceByDijstra(const vector<Route>& routeVec, const int maxNodeNum)
{
    set<Node> minNodeSet;
    minNodeSet.insert(START_NODE);

    vector<Fatigue> smallerFatigueVec(maxNodeNum + 1);
    Fatigue startNode;
    startNode.minFatigue = 0;
    startNode.flatFatig = 0;
    smallerFatigueVec[START_NODE] = startNode;

    //循环n - 1次,每次算出点1到一个点的最小消耗
    for(int i = START_NODE + 1; i <= maxNodeNum; ++i)
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
                Fatigue& todest = smallerFatigueVec[destNode];
                int newFatigue = GetNewFatig(smallerFatigueVec[currNode], *itRoute);//获取最小疲劳消耗
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
}

int main()
{
	//1.获取输入，保存
	int m, n;
	cin>>m>>n;
	int crossingNumber = m;
	int vectorSize = m + 1;
	vector<Route> routeVec;
	for( int i = 0; i < n; ++i)
	{
		int startCrossing, stopCrossing;
		Route route;
		cin >> route.type >> startCrossing >> stopCrossing >> route.dis;
		routeVec.push_back(route);
	}
	return 0;
}

