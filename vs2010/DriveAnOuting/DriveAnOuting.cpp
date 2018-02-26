// DriveAnOuting.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<vector>
using namespace std;

typedef struct{
	int routeType;
	int routeDistance;
}Route;

typedef struct{
	int currentFatigue;
	int currentContinuousHardRoad;
}Fatigue;

static const int MAX_FATIGUE = 1 << 6 + 1;
static const int NULL_ID = 0;
static const int FLAT_ROAD_TYPE = 0;
static const int HARD_ROTE_TYPE = 1;

int main()
{
	//1.获取输入，保存
	int m, n;
	cin>>m>>n;
	int crossingNumber = m;
	int vectorSize = m + 1;
	vector<vector<Route>> routeMap(vectorSize, vector<Route>(vectorSize));
	for( int i = 0; i < n; ++i)
	{
		int startCrossing, stopCrossing;
		Route route;
		cin >> route.routeType >> startCrossing >> stopCrossing >> route.routeDistance;
		//用二维矩阵保存两个路口间的距离和道路类型
		routeMap[startCrossing][stopCrossing] = route;
	}

	//2.初始化两个路口间的疲劳消耗数组
	vector<vector<Fatigue>> minFatigue(vectorSize, vector<Fatigue>(vectorSize));
	for (int i = 1; i <= crossingNumber; ++i)
	{
		for(int j = 1; j <= crossingNumber; ++j)
		{
			if(i == j)//无消耗
			{
				minFatigue[i][j].currentFatigue = NULL_ID;
			}
			else//默认消耗无穷大
			{
				minFatigue[i][j].currentFatigue = MAX_FATIGUE;
			}
			//当前连续走得小路数量
			minFatigue[i][j].currentFatigue = NULL_ID;
		}
	}

	for (int destCrossing = 2; dest <= destCrossing; ++destCrossing)
	{
		for(int j = 1; j <= crossingNumber; ++j)
		{
			//路口i、j之间有道路，不处理i、j相等
			if(NULL_ID != routeMap[i][j].routeDistance && i != j)
			{
				if( FLAT_ROAD_TYPE == routeMap[i][j].routeType)
				{

				}
				minFatigue[i][j].currentFatigue = MAX_FATIGUE;
				minFatigue[i][j].currentFatigue = NULL_ID;
			}
		}
	}

	return 0;
}

