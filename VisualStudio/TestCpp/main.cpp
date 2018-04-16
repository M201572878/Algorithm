#include <iostream>
//#include "TestPython.hpp"
//#include "TestDiffPatch.hpp"
//#include "PythonUtil.hpp"
//#include "event2/event.h"
#include "event.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"libevent.lib")
#pragma comment(lib,"libevent_core.lib")
#pragma comment(lib,"libevent_extras.lib")
#pragma comment(lib,"WSock32.lib")
using namespace std;

// 定时事件回调函数  
void onTime(intptr_t sock, short event, void *arg)
{
	cout << "Game Over!" << endl;

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	// 重新添加定时事件（定时事件触发后默认自动删除）  
	event_add((struct event*)arg, &tv);
}

int main()
{
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif
	//TestPython::run();

	//TestDiffPatch::RunWstring();
	/*string str = "1";
	cout << str.length() << " " << str.size() << endl;

	string inStr("sssssss09765653453457679885674中文s"),outStr;
	PythonUtil::Instance().Compress(inStr, outStr);
	cout << outStr.length()<<" "<<outStr << endl;*/
	const char *version = event_get_version();
	printf("%s\n", version);


	// 初始化  
	event_init();

	struct event evTime;
	// 设置定时事件  
	evtimer_set(&evTime, onTime, &evTime);

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	// 添加定时事件  
	event_add(&evTime, &tv);

	// 事件循环  
	event_dispatch();
	
	getchar();
	return 0;
}