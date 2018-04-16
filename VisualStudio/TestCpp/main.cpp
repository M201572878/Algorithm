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

// ��ʱ�¼��ص�����  
void onTime(intptr_t sock, short event, void *arg)
{
	cout << "Game Over!" << endl;

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	// ������Ӷ�ʱ�¼�����ʱ�¼�������Ĭ���Զ�ɾ����  
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

	string inStr("sssssss09765653453457679885674����s"),outStr;
	PythonUtil::Instance().Compress(inStr, outStr);
	cout << outStr.length()<<" "<<outStr << endl;*/
	const char *version = event_get_version();
	printf("%s\n", version);


	// ��ʼ��  
	event_init();

	struct event evTime;
	// ���ö�ʱ�¼�  
	evtimer_set(&evTime, onTime, &evTime);

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	// ��Ӷ�ʱ�¼�  
	event_add(&evTime, &tv);

	// �¼�ѭ��  
	event_dispatch();
	
	getchar();
	return 0;
}