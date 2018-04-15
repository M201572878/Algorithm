#include <iostream>
#include "TestPython.hpp"
#include "TestDiffPatch.hpp"
#include "PythonUtil.hpp"

using namespace std;

int main()
{
	//TestPython::run();

	//TestDiffPatch::RunWstring();
	string str = "1";
	cout << str.length() << " " << str.size() << endl;

	string inStr("sssssss09765653453457679885674ÖÐÎÄs"),outStr;
	PythonUtil::Instance().Compress(inStr, outStr);
	cout << outStr.length()<<" "<<outStr << endl;
	
	getchar();
	return 0;
}