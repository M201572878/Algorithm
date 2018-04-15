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
		pModule = PyImport_ImportModule("PythonUtil");//Test001:Python文件名
		pFunc = PyObject_GetAttrString(pModule, "TestList");//Add:Python文件中的函数名
		PyObject *pReturn = PyEval_CallObject(pFunc, pArgs); //调用函数

		Py_Finalize();     
	}
};