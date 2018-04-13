#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "Python\Python.h"

using namespace std;

static string g_pythonStr = "import time\n\
def TestList():\n\
	print('TestList1')\n\
";

class TestPython {
public:
	static void run()
	{
		Py_Initialize();   

		PyRun_SimpleString("print('he4llo', 'dd')");
		PyRun_SimpleString(g_pythonStr.c_str());
		PyObject * pModule = NULL;
		PyObject * pFunc = NULL;
		PyObject *pArgs = NULL;
		pModule = PyImport_ImportModule("hello");//Test001:Python�ļ���
		pFunc = PyObject_GetAttrString(pModule, "TestList");//Add:Python�ļ��еĺ�����
		PyObject *pReturn = PyEval_CallObject(pFunc, pArgs); //���ú���

		FILE * tmpfile = NULL;
		tmpfile_s(&tmpfile);

		char name1[L_tmpnam_s];
		tmpnam_s(name1, L_tmpnam_s);
		//open("hello2.py");
		cout << name1 << endl;

		ofstream ofs(name1, ios::out);
		ofs.write(g_pythonStr.c_str(), g_pythonStr.size());

		pModule = PyImport_ImportModule(name1);//Test001:Python�ļ���
		pFunc = PyObject_GetAttrString(pModule, "TestList");//Add:Python�ļ��еĺ�����
		pReturn = PyEval_CallObject(pFunc, pArgs); //���ú���

		Py_Finalize();     
	}
};