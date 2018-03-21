#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	string strFirst(""), strSecond("");
	cin >> strFirst >> strSecond;
	int strFirstLen = strFirst.length();
	int strSecondLen = strSecond.length();
	int maxLcs[strFirstLen][strSecondLen];
	maxLcs[0][0] = 0;
	int maxLen = 0;
	for(int i = 0; i < strFirstLen; ++i)
	{
		for(int j = 0; j < strSecondLen; ++j)
		{
			maxLcs[i][j] = 0;
			if(strFirst[i] == strSecond[j])
			{
				if(i > 0 && j > 0)
				{
					maxLcs[i][j] = maxLcs[i - 1][j - 1] + 1;
				}
				else
				{
					maxLcs[i][j] = 1;
				}
			}
			maxLen = maxLen > maxLcs[i][j] ? maxLen : maxLcs[i][j];
		}
	}
	cout << maxLen <<endl;
	return 0;
}
