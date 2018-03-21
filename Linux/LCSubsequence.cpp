#include <iostream>
using namespace std;

int main()
{
	string strFir(""), strSec("");
	cin >> strFir >> strSec;
	int strFirLen = strFir.length();
	int strSecLen = strSec.length();
	int maxLCS[strFirLen][strSecLen];
	int maxSquenLen = 0;
	maxLCS[0][0] = 0;
	for(int i = 1; i <= strFirLen; ++i)
	{
		maxLCS[i][0] = 0;
		for(int j = 1; j <= strSecLen; ++j)
		{
			maxLCS[0][j] = 0;
			if(strFir[i - 1] == strSec[j - 1])
			{
				maxLCS[i][j] = maxLCS[i - 1][j - 1] + 1;
				cout << strFir[i - 1] << " " << strSec[j - 1] << endl;
			}
			else
			{
				maxLCS[i][j] = maxLCS[i][j - 1] > maxLCS[i - 1][j] ? maxLCS[i][j - 1] : maxLCS[i - 1][j];
			}
			maxSquenLen = maxSquenLen > maxLCS[i][j] ? maxSquenLen : maxLCS[i][j];
		}
	}
	cout << maxSquenLen << endl;
	return 0;
}
