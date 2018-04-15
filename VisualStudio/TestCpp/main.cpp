#include <iostream>
//#include "TestPython.hpp"
//#include "TestDiffPatch.hpp"
//#include "PythonUtil.hpp"
#include "event2/event.h"
#include "event.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"libevent.lib")
#pragma comment(lib,"libevent_core.lib")
#pragma comment(lib,"libevent_extras.lib")
#pragma comment(lib,"WSock32.lib")
using namespace std;

int main()
{
	//TestPython::run();

	//TestDiffPatch::RunWstring();
	/*string str = "1";
	cout << str.length() << " " << str.size() << endl;

	string inStr("sssssss09765653453457679885674ÖÐÎÄs"),outStr;
	PythonUtil::Instance().Compress(inStr, outStr);
	cout << outStr.length()<<" "<<outStr << endl;*/

	const char *version = event_get_version();
	printf("%s\n", version);
	
	getchar();
	return 0;
}